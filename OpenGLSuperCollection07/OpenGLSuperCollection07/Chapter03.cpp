//
//  Chapter03.cpp
//  OpenGLSuperCollection07
//
//  Created by anker on 2021/7/28.
//

#include "Chapter03.hpp"

Chapter03::Chapter03() {
    
}

Chapter03::~Chapter03() {
    
}

GLuint Chapter03::completeShaders() {
    GLuint vertex_shader;
    GLuint tcs_shader;
    GLuint tes_shader;
    GLuint fragment_shader;
    GLuint program;
    
    static const GLchar *vertex_shader_source[] =
    {
        "#version 410 core                              \n"
        "                                               \n"
        "layout (location = 0) in vec4 offset;          \n"
//        "layout (location = 1) in vec4 color;           \n"
//        "                                               \n"
//        "out VS_OUT {                                   \n"
//        "    vec4 color;                                \n"
//        "} vs_out;                                      \n"
//        "                                               \n"
//        "out vec4 vs_color;                             \n"
        "                                               \n"
        "void main(void)                                \n"
        "{                                              \n"
        "   const vec4 vertices[3] = vec4[3](vec4(0.25, -0.25, 0.5, 1.0), vec4(-0.25, -0.25, 0.5, 1.0), vec4(0.25, 0.25, 0.5, 1.0));\n"
        "   gl_Position = vertices[gl_VertexID] + offset;        \n"
//        "   vs_out.color = color;                                \n"
        "}                                                       \n"
    };
    
    static const GLchar *tcs_shader_source[] =
    {
        "#version 410 core                              \n"
        "                                               \n"
        "layout (vertices = 3) out;                     \n"
        "                                               \n"
        "void main(void) {                                \n"
        "   if (gl_InvocationID == 0)\n"
        "   {                       \n"
        "       gl_TessLevelInner[0] = 5.0;                   \n"
        "       gl_TessLevelOuter[0] = 5.0;                   \n"
        "       gl_TessLevelOuter[1] = 5.0;                   \n"
        "       gl_TessLevelOuter[2] = 5.0;                   \n"
        "   }                                                 \n"
        "   gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;        \n"
        "}                                                       \n"
    };
    
    static const GLchar *tes_shader_source[] =
    {
        "#version 410 core                              \n"
        "                                               \n"
        "layout (triangles, equal_spacing, cw) in;      \n"
        "                                               \n"
        "void main(void) {                                \n"
        "   gl_Position = (gl_TessCoord.x * gl_in[0].gl_Position + \n"
        "                  gl_TessCoord.y * gl_in[1].gl_Position +\n"
        "                  gl_TessCoord.z * gl_in[2].gl_Position);       \n"
        "}                                                       \n"
    };

    static const GLchar *fragment_shader_source[] =
    {
        "#version 410 core                          \n"
        "                                           \n"
//        "in vec4 vs_color;                          \n"
//        "                                           \n"
//        "in VS_OUT {                                \n"
//        "    vec4 color;                            \n"
//        "} fs_in;                                   \n"
        "                                           \n"
        "out vec4 color;                            \n"
        "                                           \n"
        "void main(void)                            \n"
        "{                                          \n"
//        "   color = fs_in.color;                    \n"
        "   color = vec4(1.0, 0.0, 0.0, 1.0);                    \n"
        "}                                          \n"
    };
    
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, vertex_shader_source, NULL);
    glCompileShader(vertex_shader);
    assert(vertex_shader != 0);

    tcs_shader = glCreateShader(GL_TESS_CONTROL_SHADER);
    glShaderSource(tcs_shader, 1, tcs_shader_source, NULL);
    glCompileShader(tcs_shader);
    assert(tcs_shader != 0);

    tes_shader = glCreateShader(GL_TESS_EVALUATION_SHADER);
    glShaderSource(tes_shader, 1, tes_shader_source, NULL);
    glCompileShader(tes_shader);
    assert(tes_shader != 0);

    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, fragment_shader_source, NULL);
    glCompileShader(fragment_shader);
    assert(fragment_shader != 0);

    program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, tcs_shader);
    glAttachShader(program, tes_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);
    
    GLint Success = 0;
    GLchar ErrorLog[1024] = { 0 };
    glGetProgramiv(program, GL_LINK_STATUS, &Success);
    if (Success == 0) {
        glGetProgramInfoLog(program, sizeof(ErrorLog), NULL, ErrorLog);
        fprintf(stderr, "Error linking shader program: '%s'\n", ErrorLog);
        exit(1);
    }

//    glValidateProgram(program);
//    glGetProgramiv(program, GL_VALIDATE_STATUS, &Success);
//    if (!Success) {
//        glGetProgramInfoLog(program, sizeof(ErrorLog), NULL, ErrorLog);
//        fprintf(stderr, "Invalid shader program: '%s'\n", ErrorLog);
//        exit(1);
//    }
    
    glDeleteShader(vertex_shader);
    glDeleteShader(tcs_shader);
    glDeleteShader(tes_shader);
    glDeleteShader(fragment_shader);

    return program;
}

void Chapter03::startup() {
    rending_program = completeShaders();
    glGenVertexArrays(1, &vertex_array_object);
    glBindVertexArray(vertex_array_object);
}

void Chapter03::shutdown() {
    glDeleteVertexArrays(1, &vertex_array_object);
    glDeleteProgram(rending_program);
}

void Chapter03::render(double currentTime) {
    const GLfloat black[] = {0.0, 0.0, 0.0, 1.0};
    glClearBufferfv(GL_COLOR, 0, black);
    
    glPatchParameteri(GL_PATCH_VERTICES, 3);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glUseProgram(rending_program);
    
    GLfloat attrib[] = {(float)sin(currentTime) * 0.5f, (float)cos(currentTime) * 0.6f, 0.0, 0.0};
    glVertexAttrib4fv(0, attrib);
    GLfloat color[] = {(float)sin(currentTime) * 0.5f + 0.5f, (float)cos(currentTime) * 0.5f + 0.5f, 0.0, 1.0};
    glVertexAttrib4fv(1, color);
    glDrawArrays(GL_PATCHES, 0, 3);

//    glDrawArrays(GL_TRIANGLES, 0 , 3);
}
