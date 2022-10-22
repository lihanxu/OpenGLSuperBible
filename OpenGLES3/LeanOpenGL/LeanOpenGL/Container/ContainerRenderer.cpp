//
//  ContainerRenderer.cpp
//  LeanOpenGL
//
//  Created by 李涵旭 on 2022/10/20.
//

#include "ContainerRenderer.hpp"
#include "Shader.hpp"
#include "stb_image.h"
#include <iostream>
//#include "glm.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform1.hpp>
#include <glm/gtc/type_ptr.hpp>

extern "C" {
#include "FileWrapper.h"
}

typedef struct {
    GLuint programObject;
} UserData;

class ContainerRenderer::Impl {
public:
    GLint _width;
    GLint _height;
    int _time = 0;
private:
    Shader _shader;
    GLuint _VAO;
    GLuint _texture1;
    GLuint _texture2;
public:
    Impl(const char *vertextPath, const char *fragmentPath)
        :_shader(Shader(vertextPath, fragmentPath)) {
    }
    
    ~Impl() {}
    
    int setupGL() {
        
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
    }
    
    void draw() {
        glViewport(0, 0, _width, _height);
        glClear(GL_COLOR_BUFFER_BIT);
        _time++;
        glm::mat4 trans = glm::mat4(1.0f);
        trans = glm::translate(trans, glm::vec3(0.5, -0.5, 0.0));
        trans = glm::rotate(trans, glm::radians((float)_time), glm::vec3(0.0, 0.0, 1.0));
        
        _shader.use();
        
        GLuint loc = glGetUniformLocation(_shader.ID, "transform");
        glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(trans));
        
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, _texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, _texture2);
        
        glBindVertexArray(_VAO);
/*
 void glDrawElements(GLenum mode, GLsizei count, GLenum type, const GLvoid *indices);

    mode: 第一个参数指定了我们绘制的模式。
    count: 第二个参数是我们打算绘制顶点的个数，这里填6，也就是说我们一共需要绘制6个顶点。
    type: 第三个参数是索引的类型，这里是GL_UNSIGNED_INT。
    indices: 最后一个参数里我们可以指定 EBO 中的偏移量（ 或者传递一个索引数组，但是这是当你不在使用索引缓冲对象的时候 ），但是我们会在这里填写0。
 */
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
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
            std::cout << "ContainerRenderer.cpp: Failed to load texture" << std::endl;
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
        //     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
             0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
             0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
            -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
            -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
        };
        unsigned int indices[] = {
            0, 1, 3, // first triangle
            1, 2, 3  // second triangle
        };
        
        GLuint VBO, VEO;
        
        glGenVertexArrays(1, &_VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(2, &VEO);
        
        glBindVertexArray(_VAO);
        
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VEO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
        
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), 0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (void *)(3 * sizeof(GL_FLOAT)));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (void *)(6 * sizeof(GL_FLOAT)));
        glEnableVertexAttribArray(2);
        
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
    
};

ContainerRenderer::ContainerRenderer(const char *vertextPath, const char *fragmentPath)
    :m_pImpl(new Impl(vertextPath, fragmentPath)) {
    
}

ContainerRenderer::~ContainerRenderer() {}

int ContainerRenderer::setupGL() {
    return m_pImpl->setupGL();
}

void ContainerRenderer::tearDownGL() {
    m_pImpl->tearDownGL();
}

void ContainerRenderer::updateWindowSize(int width, int height) {
    m_pImpl->updateWindowSize(width, height);
}

void ContainerRenderer::draw() {
    m_pImpl->draw();
}

