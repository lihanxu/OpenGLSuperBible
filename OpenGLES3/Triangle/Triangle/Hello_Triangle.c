//
//  Hello_Triangle.c
//  Triangle
//
//  Created by hansen on 2022/10/18.
//

#include "esUtil.h"

typedef struct {
    GLuint programObject;
} UserData;

int Init(ESContext *esContext) {
    char vShaderStr[] =
       "#version 300 es                          \n"
       "layout(location = 0) in vec4 vPosition;  \n"
       "void main()                              \n"
       "{                                        \n"
       "   gl_Position = vPosition;              \n"
       "}                                        \n";

    char fShaderStr[] =
       "#version 300 es                              \n"
       "precision mediump float;                     \n"
       "out vec4 fragColor;                          \n"
       "void main()                                  \n"
       "{                                            \n"
       "   fragColor = vec4 ( 1.0, 0.0, 0.0, 1.0 );  \n"
       "}                                            \n";
    
    UserData *userData = esContext->userData;
    userData->programObject = esLoadProgram(vShaderStr, fShaderStr);
    
    glClearColor(1.0, 1.0, 1.0, 0.0f);
    return GL_TRUE;
}

GLuint VAO, VBO, VEO;

// VAO,VBO,VEO 画正方形
void InitVAO(ESContext *esContext) {
    
    float vertices[] = {
        0.5f, 0.5f, 0.0f,   // 右上角
        0.5f, -0.5f, 0.0f,  // 右下角
        -0.5f, -0.5f, 0.0f, // 左下角
        -0.5f, 0.5f, 0.0f   // 左上角
    };

    unsigned int indices[] = {
        // 注意索引从0开始!
        // 此例的索引(0,1,2,3)就是顶点数组vertices的下标，
        // 这样可以由下标代表顶点组合成矩形

        0, 1, 3, // 第一个三角形
        1, 2, 3  // 第二个三角形
    };
    
    // 创建 VAO,VBO
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &VEO);
    // 绑定VAO,VBO
    glBindVertexArray(VAO);
    // 缓冲数据到VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // 缓冲数据到VEO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VEO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    // 配置顶点属性指针
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), 0);
    glEnableVertexAttribArray(0);
    
    // 取消绑定,不能取消VEO的绑定
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
}

void Shutdown(ESContext *esContext) {
    UserData *userData = esContext->userData;
    glDeleteProgram(userData->programObject);
}

void Draw(ESContext *esContext) {
    UserData *data = esContext->userData;
    
    glViewport(0, 0, esContext->width, esContext->height);
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(data->programObject);

    glBindVertexArray(VAO);
    
//    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

int esMain(ESContext *esContext) {
    esContext->userData = malloc(sizeof(UserData));
    if (Init(esContext) != GL_TRUE) {
        return GL_FALSE;
    }
    InitVAO(esContext);
    
    esRegisterShutdownFunc(esContext, Shutdown);
    esRegisterDrawFunc(esContext, Draw);
    
    return GL_TRUE;
}
