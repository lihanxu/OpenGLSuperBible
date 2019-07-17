//
//  main.cpp
//  Triangle
//
//  Created by 李涵旭 on 2019/7/16.
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
    glViewport(0.0f, 0.0f, w, h);
}

void specialKey(int key, int x, int y)
{
    GLfloat step = 0.025;
    GLfloat batchX = vVerts[0];
    GLfloat batchY = vVerts[7];
    if (key == GLUT_KEY_UP) {
        batchY = batchY + step;
    } else if (key == GLUT_KEY_DOWN) {
        batchY = batchY - step;
    } else if (key == GLUT_KEY_LEFT) {
        batchX = batchX - step;
    } else if (key == GLUT_KEY_RIGHT) {
        batchX = batchX + step;
    }
    batchX = batchX < -1.0 ? -1.0 : batchX;
    batchX = batchX > 1.0 - blockSize * 2.0 ? 1.0 - blockSize * 2.0 : batchX;
    batchY = batchY < -1.0 + blockSize * 2.0 ? -1.0 + blockSize * 2.0 : batchY;
    batchY = batchY > 1.0 ? 1.0 : batchY;
    
    vVerts[0] = batchX;
    vVerts[1] = batchY - blockSize * 2.0;
    
    vVerts[3] = batchX + blockSize * 2.0;
    vVerts[4] = batchY - blockSize * 2.0;
    
    vVerts[6] = batchX + blockSize * 2.0;
    vVerts[7] = batchY;
    
    vVerts[9] = batchX;
    vVerts[10] = batchY;
    
    squareBatch.CopyVertexData3f(vVerts);
    glutPostRedisplay();
}

void setupGL()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    shaderManager.InitializeStockShaders();
    squareBatch.Begin(GL_TRIANGLE_FAN, 4);
    squareBatch.CopyVertexData3f(vVerts);
    squareBatch.End();
}

void render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    GLfloat red[] = { 1.0, 0.0, 0.0, 1.0 };
    shaderManager.UseStockShader(GLT_SHADER_IDENTITY, red);
    squareBatch.Draw();
    glutSwapBuffers();
}

int main(int argc, const char * argv[]) {
    gltSetWorkingDirectory(argv[0]);
    glutInit(&argc, (char **)argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_STENCIL);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Triangle");
    glutDisplayFunc(render);
    glutReshapeFunc(changeSize);
    glutSpecialFunc(specialKey);
    
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        fprintf(stderr, "glew error: %s/n", glewGetErrorString(err));
    }
    
    setupGL();
    
    glutMainLoop();
    
    return 0;
}
