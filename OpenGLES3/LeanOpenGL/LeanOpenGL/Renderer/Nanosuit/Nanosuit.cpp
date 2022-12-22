//
//  Nanosuit.cpp
//  LeanOpenGL
//
//  Created by 李涵旭 on 2022/12/18.
//

#include "Nanosuit.hpp"
#include "Shader.hpp"
#include "Camera.hpp"
#include "Model.hpp"
#include "type_ptr.hpp"

extern "C" {
#include "FileWrapper.h"
}

class Nanosuit::Impl {
public:
    GLint _width;
    GLint _height;
    
private:
    Shader _shader;
    Camera _camera;
    Model _model;
    GLuint _VAO;
public:
    Impl(const char *vertextPath, const char *fragmentPath)
    :_shader(Shader(vertextPath, fragmentPath)),
    _camera(glm::vec3(0.0f, 0.0f, 13.0f)),
    _model((char *)GetBundleFileName("cyborg.obj")) {
        
    }
    
    ~Impl() {}
    
    int setupGL() {
        glEnable(GL_DEPTH_TEST);
//        const char *name = GetBundleFileName("nanosuit.obj");
//        _model = Model((char *)name);
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
    
    void draw() {
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        _shader.use();
        
        glm::mat4 projection = glm::perspective(glm::radians(_camera._zoom), (float)_width / (float)_height, 0.1f, 100.0f);
        glm::mat4 view = _camera.GetViewMatrix();
        _shader.setMatrix4fv("projection", glm::value_ptr(projection));
        _shader.setMatrix4fv("view", glm::value_ptr(view));

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
        _shader.setMatrix4fv("model", glm::value_ptr(model));
        _model.Draw(_shader);
    }
    
private:
    
    
};

Nanosuit::Nanosuit(const char *vertextPath, const char *fragmentPath)
    :BaseRenderer(vertextPath, fragmentPath),
    m_pImpl(new Impl(vertextPath, fragmentPath)) {
}

Nanosuit::~Nanosuit() {
    printf("  Nanosuit::~Nanosuit() \n");
}

int Nanosuit::setupGL() {
    return m_pImpl->setupGL();
}

void Nanosuit::tearDownGL() {
    m_pImpl->tearDownGL();
}

void Nanosuit::updateWindowSize(int width, int height) {
    m_pImpl->updateWindowSize(width, height);
}

void Nanosuit::draw() {
    m_pImpl->draw();
}
