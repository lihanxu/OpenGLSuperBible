//
//  Primitives.cpp
//  Primitives
//
//  Created by anker on 2021/7/25.
//

#include <GLTools.h>    // OpenGL toolkit
#include <GLMatrixStack.h>
#include <GLFrustum.h>
#include <GLGeometryTransform.h>

#include <GLUT/GLUT.h>

GLShaderManager        shaderManager;
GLMatrixStack        modelViewMatrix;
GLFrustum            viewFrustum;

GLBatch                pointBatch;
GLBatch                lineBatch;
GLBatch                lineStripBatch;
GLBatch                lineLoopBatch;
GLBatch                triangleBatch;
GLBatch             triangleStripBatch;
GLBatch             triangleFanBatch;
GLBatch    squareBatch;


GLfloat vGreen[] = { 0.0f, 1.0f, 0.0f, 1.0f };
GLfloat vBlack[] = { 0.0f, 0.0f, 0.0f, 1.0f };

GLfloat blockSize = 1.0f;
GLfloat vVerts[] = { -blockSize, -blockSize, 0.0f,
                      blockSize, -blockSize, 0.0f,
                      blockSize,  blockSize, 0.0f,
                     -blockSize,  blockSize, 0.0f};


// Keep track of effects step
int nStep = 0;

void SetupRC()
    {
    // Black background
    glClearColor(0.7f, 0.7f, 0.7f, 1.0f );
    glEnable(GL_DEPTH_TEST);

    shaderManager.InitializeStockShaders();

    GLfloat vCoast[24][3] = {
        {2.80, 1.20, 0.0 }, {2.0,  1.20, 0.0 },
        {2.0,  1.08, 0.0 },  {2.0,  1.08, 0.0 },
        {0.0,  0.80, 0.0 },  {-0.32, 0.40, 0.0 },
        {-0.48, 0.2, 0.0 },   {-0.40, 0.0, 0.0 },
        {-0.60, -0.40, 0.0 },  {-0.80, -0.80, 0.0 },
        {-0.80, -1.4, 0.0 },  {-0.40, -1.60, 0.0 },
        {0.0, -1.20, 0.0 },  { 0.2, -0.80, 0.0 },
        {0.48, -0.40, 0.0 },   {0.52, -0.20, 0.0 },
        {0.48,  0.20, 0.0 },   {0.80, 0.40, 0.0 },
        {1.20, 0.80, 0.0 },   {1.60, 0.60, 0.0 },
        {2.0, 0.60, 0.0 },    {2.2, 0.80, 0.0 },
        {2.40, 1.0, 0.0 },   {2.80, 1.0, 0.0 }
    };
    pointBatch.Begin(GL_POINTS, 24);
    pointBatch.CopyVertexData3f(vCoast);
    pointBatch.End();
    
    GLfloat vPyramid[12][3] = {
        -2.0f, 0.0f, -2.0f,
        2.0f, 0.0f, -2.0f,
        0.0f, 4.0f, 0.0f,
        
        2.0f, 0.0f, -2.0f,
        2.0f, 0.0f, 2.0f,
        0.0f, 4.0f, 0.0f,
        
        2.0f, 0.0f, 2.0f,
        -2.0f, 0.0f, 2.0f,
        0.0f, 4.0f, 0.0f,
        
        -2.0f, 0.0f, 2.0f,
        -2.0f, 0.0f, -2.0f,
         0.0f, 4.0f, 0.0f
    };
    triangleBatch.Begin(GL_TRIANGLES, 12);
    triangleBatch.CopyVertexData3f(vPyramid);
    triangleBatch.End();
    
    // Load up a triangle
    squareBatch.Begin(GL_TRIANGLE_FAN, 4);
    squareBatch.CopyVertexData3f(vVerts);
    squareBatch.End();
}

void RenderScene(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    M3DMatrix44f mFinalTransform, mTranslationMatrix, mRotationMatrix;
    
    // Just Translate
    m3dTranslationMatrix44(mTranslationMatrix, 0.0f, 0.0f, 0.0f);

    static float yRot = 0.0f;
    yRot += 5.0f;
//    m3dRotationMatrix44(mRotationMatrix, m3dDegToRad(yRot), 0.0f, 0.0f, 1.0f);
    m3dRotationMatrix44(mRotationMatrix, 0.0f, 0.0f, 0.0f, 1.0f);

    m3dMatrixMultiply44(mFinalTransform, mTranslationMatrix, mRotationMatrix);
    m3dMatrixMultiply44(mFinalTransform, viewFrustum.GetProjectionMatrix(), mFinalTransform);

    shaderManager.UseStockShader(GLT_SHADER_FLAT, mFinalTransform, vGreen);
    
    glPointSize(5.0);
    
//    pointBatch.Draw();
    squareBatch.Draw();
//    triangleBatch.Draw();
    
    glutSwapBuffers();
    glutPostRedisplay();
}


void SpecialKeys(int key, int x, int y) {
//    glutPostRedisplay();
}

void ChangeSize(int w, int h) {
    printf("chage size: %d, %d\n", w, h);
    glViewport(0, 0, w, h);
//    viewFrustum.SetOrthographic(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);
    viewFrustum.SetPerspective(90.0f, float(w)/float(h), 2.0f, 100.0f);
}

///////////////////////////////////////////////////////////////////////////////
// Main entry point for GLUT based programs
int main(int argc, char* argv[]) {
    gltSetWorkingDirectory(argv[0]);
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);
    glutInitWindowSize(600, 600);
    glutCreateWindow("GL_POINTS");
    glutReshapeFunc(ChangeSize);
    glutSpecialFunc(SpecialKeys);
    glutDisplayFunc(RenderScene);
        
    GLenum err = glewInit();
    if (GLEW_OK != err) {
        fprintf(stderr, "GLEW Error: %s\n", glewGetErrorString(err));
        return 1;
        }
    

    SetupRC();

    glutMainLoop();
    return 0;
}
