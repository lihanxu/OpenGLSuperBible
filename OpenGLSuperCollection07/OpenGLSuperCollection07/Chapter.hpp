//
//  Chapter.hpp
//  OpenGLSuperCollection07
//
//  Created by anker on 2021/7/27.
//

#ifndef Chapter_hpp
#define Chapter_hpp

#include <stdio.h>
#include <assert.h>
#include "sb7.h"

class Chapter {
public:
    Chapter(){};
    ~Chapter(){};
    
    virtual void startup() {};
    virtual void shutdown() {};
    virtual void render(double currentTime) {};
    
    GLuint completeShaders(void) {
        GLuint vertex_shader;
        GLuint fragment_shader;
        GLuint program;
        
        static const GLchar *vertex_shader_source[] =
        {
            "#version 410 core                              \n"
            "void main(void)                                \n"
            "{                                              \n"
            "   gl_Position = vec4(0.0, 0.0, 0.5, 1.0);     \n"
            "}                                              \n"
        };
        
        static const GLchar *fragment_shader_source[] =
        {
            "#version 410 core                          \n"
            "                                           \n"
            "out vec4 color;                            \n"
            "                                           \n"
            "void main(void)                            \n"
            "{                                          \n"
            "   color = vec4(0.0, 0.8, 1.0, 1.0);       \n"
            "}                                          \n"
        };
        
        vertex_shader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex_shader, 1, vertex_shader_source, NULL);
        glCompileShader(vertex_shader);
        
        fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment_shader, 1, fragment_shader_source, NULL);
        glCompileShader(fragment_shader);
        
        program = glCreateProgram();
        glAttachShader(program, vertex_shader);
        glAttachShader(program, fragment_shader);
        glLinkProgram(program);
        
        glDeleteShader(vertex_shader);
        glDeleteShader(fragment_shader);

        return program;
    }
    
public:
    GLuint rending_program;
    GLuint vertex_array_object;
};


#endif /* Chapter_hpp */
