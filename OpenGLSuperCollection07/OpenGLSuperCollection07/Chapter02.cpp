//
//  Chapter02.cpp
//  OpenGLSuperCollection07
//
//  Created by anker on 2021/7/27.
//

#include "Chapter02.hpp"

Chapter02::Chapter02() {
    
}

Chapter02::~Chapter02() {
    
}

GLuint Chapter02::completeShaders() {
    GLuint vertex_shader;
    GLuint fragment_shader;
    GLuint program;
    
    static const GLchar *vertex_shader_source[] =
    {
        "#version 410 core                              \n"
        "void main(void)                                \n"
        "{                                              \n"
        "   const vec4 vertices[3] = vec4[3](vec4(0.25, -0.25, 0.5, 1.0), vec4(-0.25, -0.25, 0.5, 1.0), vec4(0.25, 0.25, 0.5, 1.0));\n"
        "   gl_Position = vertices[gl_VertexID];        \n"
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
        "   color = vec4(1.0, 1.0, 1.0, 1.0);       \n"
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

void Chapter02::startup() {
    rending_program = completeShaders();
    glGenVertexArrays(1, &vertex_array_object);
    glBindVertexArray(vertex_array_object);
}

void Chapter02::shutdown() {
    glDeleteVertexArrays(1, &vertex_array_object);
    glDeleteProgram(rending_program);
}

void Chapter02::render(double currentTime) {
    const GLfloat color[] = {(float)sin(currentTime) * 0.5f + 0.5f, (float)cos(currentTime) * 0.5f + 0.5f, 0.0, 1.0};
    glClearBufferfv(GL_COLOR, 0, color);
    
//    glPointSize(50.0);
    glUseProgram(rending_program);
//    glDrawArrays(GL_POINTS, 0 , 1);
    glDrawArrays(GL_TRIANGLES, 0 , 3);
}
