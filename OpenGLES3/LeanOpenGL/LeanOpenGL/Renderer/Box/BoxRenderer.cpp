//
//  BoxRenderer.cpp
//  LeanOpenGL
//
//  Created by 李涵旭 on 2022/10/23.
//

#include "BoxRenderer.hpp"
#include "stb_image.h"
#include "TimeTool.hpp"
#include "Shader.hpp"
#include "Camera.hpp"
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform1.hpp>
#include <glm/gtc/type_ptr.hpp>


extern "C" {
#include "FileWrapper.h"
}

typedef struct {
    GLuint programObject;
} UserData;

class BoxRenderer::Impl {
public:
    GLint _width;
    GLint _height;
    long _time;
    long _deltaTime;
    long _lastFrame;
private:
    Shader _shader;
    Camera _camera;
    float _moveRadian;
    
    GLuint _VAO, _VBO;
    GLuint _texture1;
    GLuint _texture2;
    glm::vec3 _cubePositions[10] = {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
      };
public:
    Impl(const char *vertextPath, const char *fragmentPath)
    :_shader(Shader(vertextPath, fragmentPath)),
    _camera(glm::vec3(0.0f, 0.0f, 3.0f)) {
        _time = 0.0;
        _deltaTime = 0.0;
        _lastFrame = 0.0;
        _moveRadian = 0.0;
    }
    
    ~Impl() {
        glDeleteVertexArrays(1, &_VAO);
        glDeleteBuffers(1, &_VBO);
    }
    
    int setupGL() {
        
        glEnable(GL_DEPTH_TEST);
        glClearColor(1.0, 1.0, 1.0, 0.0f);
        
        genVAO();
        
        _texture1 = loadTexture("container.jpeg", false, GL_RGB);
        _texture2 = loadTexture("awesomeface.png", true, GL_RGBA);
        
        _shader.use();
        _shader.setInt("texture1", 0);
        _shader.setInt("texture2", 1);

        return GL_TRUE;
    }
    
    void tearDownGL() {
        glDeleteProgram(_shader.ID);
    }
    
    void updateWindowSize(GLint width, GLint height) {
        if (_width == width || _height == height) {
            return;
        }
        _width = width;
        _height = height;
        glViewport(0, 0, _width, _height);
    }
    
    void move(float front, float right) {
        _camera.ProcessKeyboard(Camera::FORWARD, -front / 100.0);
        _camera.ProcessKeyboard(Camera::RIGHT, -right / 100.0);
    }
    
    void move(float radian) {
        _moveRadian = radian;
        if (_moveRadian == 0) {
            _deltaTime = 0;
            _lastFrame = 0;
        }
    }
    
    void zoom(float scale) {
        
    }
    
    void draw() {
        if (_moveRadian != 0) {
            long currentFrame = static_cast<long>(getCurrentTime());
            if (_lastFrame == 0) {
                _deltaTime = currentFrame - _lastFrame;
                _lastFrame = currentFrame;
            } else {
                _deltaTime = currentFrame - _lastFrame;
                _lastFrame = currentFrame;
                
                _camera.ProcessKeyboard2(Camera::FORWARD, _deltaTime / 1000.0 * cos(_moveRadian) );
                _camera.ProcessKeyboard2(Camera::RIGHT, -_deltaTime / 1000.0 * sin(_moveRadian) );
            }
            
        }
//        std::cout<< _deltaTime << std::endl;
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, _texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, _texture2);
        
        glBindVertexArray(_VAO);
        
        _shader.use();
        _time += 1.0/30.0;
        
        // 视图矩阵:lookAt(相机位置，目标位置，上向量)
//        float radius = 10.0f;
//        float camX = sin(_time) * radius;
//        float camZ = cos(_time) * radius;
//        glm::mat4 view = glm::lookAt(glm::vec3(camX, 0.0f, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0f, 1.0f, 0.0f));
//        _shader.setMatrix4fv("view", glm::value_ptr(view));
        
        // 透视矩阵
        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(_camera._zoom), (float)_width/(float)_height, 0.1f, 100.0f);
        _shader.setMatrix4fv("projection", glm::value_ptr(projection));
        
        // 视图矩阵
        glm::mat4 view = _camera.GetViewMatrix();
        _shader.setMatrix4fv("view", glm::value_ptr(view));

        for (unsigned int i = 0; i < 10; i++) {
            // 模型矩阵
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, _cubePositions[i]);
            model = glm::rotate(model, _time * glm::radians(55.0f), glm::vec3(1.0f, 0.3f, 0.5f));
            _shader.setMatrix4fv("model", glm::value_ptr(model));
            
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
    }
    
private:
    GLuint loadTexture(const char *fileName, bool flip_vertically, GLint internalFormat) {
        int width, height, nrChannels;
        const char *filePath = GetBundleFileName(fileName);
        if (flip_vertically) {
            // 上下反正图片
            stbi_set_flip_vertically_on_load(true);
        }
        unsigned char *data = stbi_load(filePath, &width, &height, &nrChannels, 0);
        if (!data) {
            std::cout << "BoxRenderer.cpp: Failed to load texture" << std::endl;
            return 0;
        }
        
        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);

        // 为当前绑定的纹理对象设置环绕、过滤方式
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        
/*
 void glTexImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid *pixels);

    target: 第一个参数指定了纹理目标(Target)。 设置为 GL_TEXTURE_2D 意味着会生成与当前绑定的纹理对象在同一个目标上的纹理（任何绑定到 GL_TEXTURE_1D 和 GL_TEXTURE_3D 的纹理不会受到影响）。
    level: 第二个参数为纹理指定多级渐远纹理的级别，如果你希望单独手动设置每个多级渐远纹理的级别的话。这里我们填0，也就是基本级别。
    internalformat: 第三个参数告诉OpenGL我们希望把纹理储存为何种格式。我们的图像只有RGB值，因此我们也把纹理储存为RGB值。
    width:
    height: 第四个和第五个参数设置最终的纹理的宽度和高度。我们之前加载图像的时候储存了它们，所以我们使用对应的变量。
    border: 这个参数应该总是被设为0（历史遗留的问题）。
    format: 第七个参数定义了源图的格式。我们使用RGB值加载这个图像。
    type: 第八个参数定义了源图的数据类型。我们使用RGB值加载这个图像，并把它们储存为char(byte)数组。
    pixels: 最后一个参数是真正的图像数据。
 */
        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, internalFormat, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(data);
        return texture;
    }
    
    void genVAO() {
        float vertices[] = {
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
             0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
             0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

             0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
             0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
             0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
             0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
             0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
             0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
             0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
        };
                
        glGenVertexArrays(1, &_VAO);
        glGenBuffers(1, &_VBO);
        
        glBindVertexArray(_VAO);
        
        glBindBuffer(GL_ARRAY_BUFFER, _VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), 0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), (void *)(3 * sizeof(GL_FLOAT)));
        glEnableVertexAttribArray(1);
        
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
    
};

BoxRenderer::BoxRenderer(const char *vertextPath, const char *fragmentPath)
    :BaseRenderer(vertextPath, fragmentPath),
    m_pImpl(new Impl(vertextPath, fragmentPath)) {
    
}

BoxRenderer::~BoxRenderer() {
    printf("  BoxRenderer::~BoxRenderer() \n");
}

int BoxRenderer::setupGL() {
    return m_pImpl->setupGL();
}

void BoxRenderer::tearDownGL() {
    m_pImpl->tearDownGL();
}

void BoxRenderer::updateWindowSize(int width, int height) {
    m_pImpl->updateWindowSize(width, height);
}

void BoxRenderer::draw() {
    m_pImpl->draw();
}

void BoxRenderer::move(float front, float right) {
    m_pImpl->move(front, right);
}

void BoxRenderer::move(float radian) {
    m_pImpl->move(radian);
}


void BoxRenderer::zoom(float scale) {
    m_pImpl->zoom(scale);
}
