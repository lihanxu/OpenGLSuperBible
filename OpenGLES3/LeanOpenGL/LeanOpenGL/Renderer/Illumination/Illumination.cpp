//
//  Illumination.cpp
//  LeanOpenGL
//
//  Created by 李涵旭 on 2022/10/26.
//

#include "Illumination.hpp"
#include "stb_image.h"
#include "Shader.hpp"
#include "Camera.hpp"
#include "TimeTool.hpp"
#include <iostream>

#include "glm.hpp"
#include "matrix_transform1.hpp"
#include "type_ptr.hpp"

extern "C" {
#include "FileWrapper.h"
}

class Illumination::Impl {
public:
    GLint _width;
    GLint _height;
    float _time;
    double _deltaTime;
    double _lastFrame;
private:
    Shader _shader;
    Shader _lightShader;
    Camera _camera;
    float _moveRadian;

    GLuint _VAO, _VBO;
    GLuint _lightVAO;
    glm::vec3 _lightPos;
public:
    Impl(const char *vertextPath, const char *fragmentPath)
    :_shader(Shader(vertextPath, fragmentPath)),
    _lightShader(Shader()),
    _lightPos(glm::vec3(0.5f, 0.0f, 5.0f)),
    _camera(glm::vec3(0.0f, 0.0f, 3.0f)) {
        const char *vPath = GetBundleFileName("light_cube.vs");
        const char *fPath = GetBundleFileName("light_cube.fs");
        _lightShader = Shader(vPath, fPath);
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
        glClearColor(0.0, 0.0, 0.0, 1.0f);
        
        genVAO();
                
        _shader.use();
        _shader.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
        _shader.setVec3("lightColor", 1.0, 1.0, 1.0);
        _shader.setVec3("lightPos", _lightPos.x, _lightPos.y, _lightPos.z);
        _shader.setVec3("viewPos", _camera._position.x, _camera._position.y, _camera._position.z);

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
    
    void rotate(float x, float y) {
        _camera.ProcessMouseMovement(x, y);
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
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        
        
        _shader.use();
        
        // 透视矩阵
        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(_camera._zoom), (float)_width/(float)_height, 0.1f, 100.0f);
        _shader.setMatrix4fv("projection", glm::value_ptr(projection));
        
        // 视图矩阵
        glm::mat4 view = _camera.GetViewMatrix();
        _shader.setMatrix4fv("view", glm::value_ptr(view));

        // 模型矩阵
        glm::mat4 model = glm::mat4(1.0f);
        _time += 1.0/30.0;
        model = glm::rotate(model, _time * glm::radians(55.0f), glm::vec3(1.0f, 0.3f, 0.5f));
        _shader.setMatrix4fv("model", glm::value_ptr(model));
        
        glBindVertexArray(_VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        
        _lightShader.use();
        _shader.setMatrix4fv("projection", glm::value_ptr(projection));
        _shader.setMatrix4fv("view", glm::value_ptr(view));

        model = glm::mat4(1.0f);
        model = glm::translate(model, _lightPos);
        model = glm::scale(model, glm::vec3(0.2f));
        _shader.setMatrix4fv("model", glm::value_ptr(model));
        glBindVertexArray(_lightVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

    }
    
private:
    
    void genVAO() {
        float vertices[] = {
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
             0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
             0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
             0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
             0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

             0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
             0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
             0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
             0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
             0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
             0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
             0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
             0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
             0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
             0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
        };
                
        glGenVertexArrays(1, &_VAO);
        glGenBuffers(1, &_VBO);
        
        
        glBindBuffer(GL_ARRAY_BUFFER, _VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        
        glBindVertexArray(_VAO);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), 0);
        glEnableVertexAttribArray(0);
        
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), (void *)(3 * sizeof(GL_FLOAT)));
        glEnableVertexAttribArray(1);
        
//        glBindBuffer(GL_ARRAY_BUFFER, 0);
//        glBindVertexArray(0);
        
        // _lightVA0
        glGenVertexArrays(1, &_lightVAO);
        glBindVertexArray(_lightVAO);
        
        glBindBuffer(GL_ARRAY_BUFFER, _VBO);
        
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), 0);
        glEnableVertexAttribArray(0);
        
//        glBindBuffer(GL_ARRAY_BUFFER, 0);
//        glBindVertexArray(0);
        
    }
    
};

Illumination::Illumination(const char *vertextPath, const char *fragmentPath)
    :BaseRenderer(vertextPath, fragmentPath),
    m_pImpl(new Impl(vertextPath, fragmentPath)) {
    
}

Illumination::~Illumination() {
    printf("  Illumination::~Illumination() \n");
}

int Illumination::setupGL() {
    return m_pImpl->setupGL();
}

void Illumination::tearDownGL() {
    m_pImpl->tearDownGL();
}

void Illumination::updateWindowSize(int width, int height) {
    m_pImpl->updateWindowSize(width, height);
}

void Illumination::draw() {
    m_pImpl->draw();
}

void Illumination::move(float front, float right) {
    m_pImpl->move(front, right);
}

void Illumination::move(float radian) {
    m_pImpl->move(radian);
}


void Illumination::zoom(float scale) {
    m_pImpl->zoom(scale);
}

void Illumination::rotate(float x, float y) {
    m_pImpl->rotate(x, y);
}
