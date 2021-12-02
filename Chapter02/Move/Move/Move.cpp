//
//  Move.cpp
//  Move
//
//  Created by anker on 2021/7/25.
//

#include <GLTools.h>
#include <GLShaderManager.h>
#include <GLUT/GLUT.h>

GLBatch squareBatch;
GLShaderManager shaderManager;

GLfloat blockSize = 0.1f;
GLfloat vVerts[] = {-blockSize, -blockSize, 0.0,
    blockSize, -blockSize, 0.0,
    blockSize, blockSize, 0.0,
    -blockSize, blockSize, 0.0};

void ChangeSize(int w, int h) {
    printf("chage size: %d, %d\n", w, h);
    glViewport(0, 0, w, h);
}

void SetupRC() {
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
    shaderManager.InitializeStockShaders();
    
    squareBatch.Begin(GL_TRIANGLE_FAN, 4);
    squareBatch.CopyVertexData3f(vVerts);
    squareBatch.End();
}

void RenderScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    GLfloat vRed[] = {1.0, 0.0, 0.0, 1.0};
    shaderManager.UseStockShader(GLT_SHADER_IDENTITY, vRed);
    squareBatch.Draw();
    glutSwapBuffers();
}

void SpecialKeys(int key, int x, int y) {
    GLfloat stepSize = 0.025f;
    
    GLfloat blockX = vVerts[0];
    GLfloat blockY = vVerts[7];
    
    if (key == GLUT_KEY_UP) {
        blockY += stepSize;
    }
    if (key == GLUT_KEY_DOWN) {
        blockY -= stepSize;
    }
    if (key == GLUT_KEY_LEFT) {
        blockX -= stepSize;
    }
    if (key == GLUT_KEY_RIGHT) {
        blockX += stepSize;
    }
    
    if (blockX < -1.0) blockX = -1.0;
    if(blockX > (1.0f - blockSize * 2)) blockX = 1.0f - blockSize * 2;
    if(blockY < -1.0f + blockSize * 2)  blockY = -1.0f + blockSize * 2;
    if(blockY > 1.0f) blockY = 1.0f;
    
    vVerts[0] = blockX;
    vVerts[1] = blockY - blockSize * 2.0;

    vVerts[3] = blockX + blockSize * 2.0;
    vVerts[4] = blockY - blockSize * 2.0;
    
    vVerts[6] = blockX + blockSize * 2.0;
    vVerts[7] = blockY;
    
    vVerts[9] = blockX;
    vVerts[10] = blockY;

    squareBatch.CopyVertexData3f(vVerts);
    glutPostRedisplay();
}

int main(int argc, char *argv[]) {
    printf("hello opengl\n");
    
    gltSetWorkingDirectory(argv[0]);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Move Block with Arrow Keys");
    glutReshapeFunc(ChangeSize);
    glutDisplayFunc(RenderScene);
    glutSpecialFunc(SpecialKeys);
    
    GLenum err = glewInit();
    if (GLEW_OK != err) {
        fprintf(stderr, "glew error: %s\n", glewGetErrorString(err));
        return 1;
    }
    
    SetupRC();
    
    glutMainLoop();
    return 0;
}
