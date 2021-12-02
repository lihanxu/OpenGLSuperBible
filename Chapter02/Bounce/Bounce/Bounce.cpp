//
//  Bounce.cpp
//  Bounce
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

void BounceFunction() {
    static GLfloat xDir = 1.0f;
    static GLfloat yDir = 1.0f;
    
    GLfloat stepSize = 0.0005f;
    
    GLfloat blockX = vVerts[0];
    GLfloat blockY = vVerts[7];
    
    blockY += stepSize * yDir;
    blockX += stepSize * xDir;
    
    if (blockX < -1.0) {
        blockX = -1.0;
        xDir *= -1;
    }
    if(blockX > (1.0f - blockSize * 2)) {
        blockX = 1.0f - blockSize * 2;
        xDir *= -1.0;
    }
    if(blockY < -1.0f + blockSize * 2) {
        blockY = -1.0f + blockSize * 2;
        yDir *= -1;
    }
    if(blockY > 1.0f) {
        blockY = 1.0f;
        yDir *= -1.0;
    }
    
    vVerts[0] = blockX;
    vVerts[1] = blockY - blockSize * 2.0;

    vVerts[3] = blockX + blockSize * 2.0;
    vVerts[4] = blockY - blockSize * 2.0;
    
    vVerts[6] = blockX + blockSize * 2.0;
    vVerts[7] = blockY;
    
    vVerts[9] = blockX;
    vVerts[10] = blockY;

    squareBatch.CopyVertexData3f(vVerts);
}

void RenderScene() {
    printf("render scene\n");
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    GLfloat vRed[] = {1.0, 0.0, 0.0, 1.0};
    shaderManager.UseStockShader(GLT_SHADER_IDENTITY, vRed);
    squareBatch.Draw();
    glutSwapBuffers();
    
    BounceFunction();
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
    
    GLenum err = glewInit();
    if (GLEW_OK != err) {
        fprintf(stderr, "glew error: %s\n", glewGetErrorString(err));
        return 1;
    }
    
    SetupRC();
    
    glutMainLoop();
    return 0;
}

