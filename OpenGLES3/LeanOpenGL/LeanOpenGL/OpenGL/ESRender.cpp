//
//  ESRender.cpp
//  LeanOpenGL
//
//  Created by hansen on 2022/10/20.
//

#include "ESRender.hpp"
#include "esUtil.h"
#include "Shader.hpp"

typedef struct {
    GLuint programObject;
} UserData;

class ESRender::Impl {
public:
    GLint _width;
    GLint _height;
    
private:
    Shader _shader;
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
    }
    
private:
    void genVAO() {
        
    }
    
};

ESRender::ESRender(const char *vertextPath, const char *fragmentPath)
    :m_pImpl(new Impl(vertextPath, fragmentPath)) {
    
}

ESRender::~ESRender() {}

int ESRender::setupGL() {
    return m_pImpl->setupGL();
}

void ESRender::tearDownGL() {
    m_pImpl->tearDownGL();
}

void ESRender::updateWindowSize(int width, int height) {
    m_pImpl->updateWindowSize(width, height);
}

void ESRender::draw() {
    m_pImpl->draw();
}

