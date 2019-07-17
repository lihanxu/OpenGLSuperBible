//
//  main.cpp
//  Bounce
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

void bounceFunction()
{
    static GLfloat speed = 0.5;
    static GLfloat xDir = (rand() % 30 * speed);
    static GLfloat yDir = (rand() % 30 * speed);
    GLfloat stepSize = 0.005;
    
    GLfloat xBlock = vVerts[0];
    GLfloat yBlock = vVerts[7];
    
    xBlock += xDir * stepSize;
    yBlock += yDir * stepSize;
    

    xBlock = xBlock < -1.0 ? -1.0 : xBlock;
    xBlock = xBlock > 1.0 - blockSize * 2.0 ? 1.0 - blockSize * 2.0 : xBlock;
    yBlock = yBlock < -1.0 + blockSize * 2.0 ? -1.0 + blockSize * 2.0 : yBlock;
    yBlock = yBlock > 1.0 ? 1.0 : yBlock;
    
    if (xBlock <= -1.0 || xBlock >= 1.0 - blockSize * 2.0 || yBlock >= 1.0 || yBlock <= -1.0 + blockSize * 2.0) {
        xDir = (rand() % 30 - 15) * speed;
        yDir = (rand() % 30 - 15) * speed;
    }
    vVerts[0] = xBlock;
    vVerts[1] = yBlock - blockSize * 2.0;
    
    vVerts[3] = xBlock + blockSize * 2.0;
    vVerts[4] = yBlock - blockSize * 2.0;
    
    vVerts[6] = xBlock + blockSize * 2.0;
    vVerts[7] = yBlock;
    
    vVerts[9] = xBlock;
    vVerts[10] = yBlock;
    squareBatch.CopyVertexData3f(vVerts);

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
    
    bounceFunction();
    glutPostRedisplay();
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

