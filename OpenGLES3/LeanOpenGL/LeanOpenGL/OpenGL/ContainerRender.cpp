//
//  ContainerRender.cpp
//  LeanOpenGL
//
//  Created by 李涵旭 on 2022/10/20.
//

#include "ContainerRender.hpp"
#include "Shader.hpp"

typedef struct {
    GLuint programObject;
} UserData;

class ContainerRender::Impl {
public:
    GLint _width;
    GLint _height;
    
private:
    Shader _shader;
    GLuint _VAO;
public:
    Impl(const char *vertextPath, const char *fragmentPath)
        :_shader(Shader(vertextPath, fragmentPath)) {
    }
    
    ~Impl() {}
    
    int setupGL() {
        glClearColor(1.0, 1.0, 1.0, 0.0f);
        genVAO();
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
        
        _shader.use();
        _shader.setFloat3("ourColor", 1.0, 0.0, 1.0);
        glBindVertexArray(_VAO);
        
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }
    
private:
    void genVAO() {
        float vertices[] = {
            // 位置              // 颜色
             0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // 右下
            -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // 左下
             0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // 顶部
        };
        
        GLuint VBO;
        
        glGenVertexArrays(1, &_VAO);
        glGenBuffers(1, &VBO);
        
        glBindVertexArray(_VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), 0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), (void *)(3 * sizeof(GL_FLOAT)));
        glEnableVertexAttribArray(0);
        
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
    
};

ContainerRender::ContainerRender(const char *vertextPath, const char *fragmentPath)
    :m_pImpl(new Impl(vertextPath, fragmentPath)) {
    
}

ContainerRender::~ContainerRender() {}

int ContainerRender::setupGL() {
    return m_pImpl->setupGL();
}

void ContainerRender::tearDownGL() {
    m_pImpl->tearDownGL();
}

void ContainerRender::updateWindowSize(int width, int height) {
    m_pImpl->updateWindowSize(width, height);
}

void ContainerRender::draw() {
    m_pImpl->draw();
}

