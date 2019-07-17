//
//  main.cpp
//  Primitives
//
//  Created by 李涵旭 on 2019/7/17.
//  Copyright © 2019 李涵旭. All rights reserved.
//

#include <iostream>
#include <GLTools.h>
#include <GLUT/GLUT.h>

GLBatch squareBatch;
GLShaderManager shaderManager;

GLfloat blockSize = 0.1f;
GLfloat vVerts[] = { -blockSize, -blockSize, 0.0f,
    blockSize, -blockSize, 0.0f,
    blockSize,  blockSize, 0.0f,
    -blockSize,  blockSize, 0.0f};

void changeSize(int w, int h)
{
    glViewport(0.0, 0.0, w, h);
}

void renderSence()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    GLfloat color[] = { 1.0, 0.0, 0.0, 1.0 };
    shaderManager.UseStockShader(GLT_SHADER_IDENTITY, color);
    squareBatch.Draw();
    glutSwapBuffers();
}

void setupGL()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    shaderManager.InitializeStockShaders();
    squareBatch.Begin(GL_TRIANGLE_FAN, 4);
    squareBatch.CopyVertexData3f(vVerts);
    squareBatch.End();
}

int main(int argc, const char * argv[]) {

    gltSetWorkingDirectory(argv[0]);
    glutInit(&argc, (char **)argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_STENCIL);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Primitives");
    glutReshapeFunc(changeSize);
    glutDisplayFunc(renderSence);
//    gltSetWorkingDirectory(argv[0]);
//    glutInit(&argc, (char **)argv);
//    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_STENCIL);
//    glutInitWindowSize(800, 600);
//    glutCreateWindow("Triangle");
//    glutDisplayFunc(renderSence);
//    glutReshapeFunc(changeSize);
    
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        fprintf(stderr, "glew init error:%s\n", glewGetErrorString(err));
    }
    
    setupGL();
    glutMainLoop();
    
    return 0;
}
