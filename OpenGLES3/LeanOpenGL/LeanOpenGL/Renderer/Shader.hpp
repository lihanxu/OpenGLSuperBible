//
//  Shader.hpp
//  Triangle
//
//  Created by hansen on 2022/10/20.
//

#ifndef Shader_hpp
#define Shader_hpp

#include <stdio.h>
#include <string>

#ifdef __APPLE__
#include <OpenGLES/ES3/gl.h>
#else
#include <GLES3/gl3.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>
#endif
#include "glm/glm.hpp"

class Shader {
    
public:
    Shader();
    /// 构造器读取并构造着色器
    Shader(const char *vertextPath, const char *fragmentPath);

    /// program id
    unsigned int ID;
    /// 激活程序
    Shader &use();

    /// uniform 工具
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void setFloat3(const std::string &name, float value1, float value2, float value3) const;
    void setFloat4(const std::string &name, float value1, float value2, float value3, float value4) const;
    void setVec3(const std::string &name, float value1, float value2, float value3) const;
    void setMatrix4fv(const std::string &name, float *value) const;
    
    void SetFloat    (const GLchar *name, GLfloat value, GLboolean useShader = false);
    void SetInteger  (const GLchar *name, GLint value, GLboolean useShader = false);
    void SetVector2f (const GLchar *name, GLfloat x, GLfloat y, GLboolean useShader = false);
    void SetVector2f (const GLchar *name, const glm::vec2 &value, GLboolean useShader = false);
    void SetVector3f (const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLboolean useShader = false);
    void SetVector3f (const GLchar *name, const glm::vec3 &value, GLboolean useShader = false);
    void SetVector4f (const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLboolean useShader = false);
    void SetVector4f (const GLchar *name, const glm::vec4 &value, GLboolean useShader = false);
    void SetMatrix4  (const GLchar *name, const glm::mat4 &matrix, GLboolean useShader = false);
    
private:
    GLuint loadShader (GLenum type, const char *shaderSrc);
    GLuint loadProgram (const char *vertShaderSrc, const char *fragShaderSrc);
    void logMessage (const char *formatStr, ...);

};

#endif /* Shader_hpp */
