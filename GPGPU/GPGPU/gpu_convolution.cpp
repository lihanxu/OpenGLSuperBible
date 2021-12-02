//
//  gpu_convolution.cpp
//  GPGPU
//
//  Created by anker on 2021/12/2.
//

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <GL/glew.h>
#include <GLUT/glut.h>

#define WIDTH           1024 //数据块的宽度
#define HEIGHT          1024 //数据块的长度
#define MASK_RADIUS     2    //掩膜半径

using namespace std;

void initGLSL(void);
void initFBO(unsigned unWidth, unsigned unHeight);
void initGLUT(int argc, char **argv);
void createTextures(void);
void setupTexture(const GLuint texID);
void performComputation(void);
void transferFromTexture(float *data);
void transferToTexture(float *data, GLuint texID);

// 纹理标识符
GLuint yTextID;
GLuint xTextID;

// GLSL变量
GLuint glslProgram;
GLuint fragmentShader;
GLint outParam, inParam, radiusParam;

GLuint fb;

GLuint glutWindowHandle;

struct structTextureParameters {
    GLenum texTarget;
    GLenum texInternalFormat;
    GLenum texFormat;
    const GLchar *shader_source;
}textureParameters;

float *pfInput;
float fRadius = (float)MASK_RADIUS;
unsigned unWidth = (unsigned)WIDTH;
unsigned unHeight = (unsigned)HEIGHT;
unsigned unSize = unWidth * unHeight;

const GLchar *clearFS =
"void main(void) {\n"
"   gl_FragColor = vec4(0.0, 0.0, 0.0, 0.0);\n"
"}\n";

//const GLchar *convolutionFS =
//"uniform sampler2D texture;\n"
//"void main(void) {\n"
//"   vec4 color = texture2D(texture, gl_TexCoord[0].st);\n"
//"   gl_FragColor = color;\n"
//"}\n";

const GLchar *convolutionFrag =
"#extension GL_ARB_texture_rectangle : enable\n"
"uniform sampler2DRect texture;\n"
"uniform float fRadius;\n"
"float nWidth = 3.0;\n"
"float nHeight = 3.0;\n"
"void main(void) {\n"
"   vec2 pos = gl_TexCoord[0].st;\n"
"   vec4 fSum = vec4(0.0, 0.0, 0.0, 0.0);\n"
"   vec4 fTotal = vec4(0.0, 0.0, 0.0, 0.0);\n"
"   vec4 vec4Result = vec4(0.0, 0.0, 0.0, 0.0);\n"
"   for (float ii = pos.x - fRadius; ii < pos.x + fRadius + 0.5; ii += 1.0) {\n"
"       for (float jj = pos.y - fRadius; jj < pos.y + fRadius + 0.5; jj += 1.0) {\n"
"           if (ii >= 0.0 && jj >= 0.0 && ii < nWidth && jj < nHeight) {\n"
"               fSum += texture2DRect(texture, vec2(ii, jj));\n"
"               fTotal += vec4(1.0, 1.0, 1.0, 1.0);\n"
"           }\n"
"       }\n"
"   }\n"
"   vec4Result = fSum / fTotal;"
"   gl_FragColor =  vec4Result;"
"}\n";

int main(int argc, char **argv) {
    unsigned unNoData = 4 * unSize;
    pfInput = new float[unNoData];
    float *pfOutput = new float[unNoData];
    for (unsigned i = 0; i < unNoData; i++) {
        pfInput[i] = i;
    }
    
    textureParameters.texTarget = GL_TEXTURE_RECTANGLE_ARB;
    textureParameters.texInternalFormat = GL_RGBA32F_ARB;
    textureParameters.texFormat = GL_RGBA;
    
    initGLUT(argc, argv);
    glewInit();
    // 初始化FBO
    initFBO(unWidth, unHeight);
    // 为输入、输出数据创建纹理缓存
    createTextures();
    
    // 安全起见，先清除输入纹理缓存
    textureParameters.shader_source = clearFS;
    initGLSL();
    performComputation();
    
    // 计算二维离散卷积
    textureParameters.shader_source = convolutionFrag;
    initGLSL();
    performComputation();
    
    // 读回计算结果
    transferFromTexture(pfOutput);
    
    // 清理工作
    glDetachShader(glslProgram, fragmentShader);
    glDeleteShader(fragmentShader);
    glDeleteProgram(glslProgram);
    glDeleteFramebuffersEXT(1, &fb);
    glDeleteTextures(1, &yTextID);
    glDeleteTextures(1, &xTextID);
    glutDestroyWindow(glutWindowHandle);
    
    delete[] pfInput;
    delete[] pfOutput;
    return  EXIT_SUCCESS;
}

/// 初始化 GLSL 运行时组件，并创建着色器
void initGLSL(void) {
    glslProgram = glCreateProgram();
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER_ARB);
    // 为着色器设置着色器程序文件
    const GLchar *source = textureParameters.shader_source;
    glShaderSource(fragmentShader, 1, &source, NULL);
    // 编译着色器
    glCompileShader(fragmentShader);
    // 把着色器与程序关联
    glAttachShader(glslProgram, fragmentShader);
    // 链接到完整的程序，这里使用了默认功能的顶点着色器
    glLinkProgram(glslProgram);
    //获取 uniform 变量的位置
    radiusParam = glGetUniformLocation(glslProgram, "fRadius");
}


/// 屏外渲染
void initFBO(unsigned unWidth, unsigned unHeight) {
    // 创建FBO, 准备屏幕外帧缓存
    glGenFramebuffersEXT(1, &fb);
    // 绑定屏幕外帧缓存，即避开了窗口系统默认的渲染目标
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fb);
    // 设置一个1:1等大的纹理元-像素映射
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, unWidth, 0.0, unHeight);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glViewport(0, 0, unWidth, unHeight);
}

void initGLUT(int argc, char **argv) {
    glutInit(&argc, argv);
    glutWindowHandle = glutCreateWindow("GPGPU Tutorial");
}

/// 创建纹理
void createTextures(void) {
    // 创建纹理，y保存输出数据，x保存输入数据
    glGenTextures(1, &yTextID);
    glGenTextures(1, &xTextID);
    // 配置纹理
    setupTexture(yTextID);
    setupTexture(xTextID);
    transferToTexture(pfInput, xTextID);
    
    // 设定映射参数，使写入目标缓存的数据覆盖原来的数据
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
}

void setupTexture(const GLuint texID) {
    glBindTexture(textureParameters.texTarget, texID);
    // 关闭滤波算法和边界以外的重复算法
    glTexParameteri(textureParameters.texTarget, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(textureParameters.texTarget, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(textureParameters.texTarget, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(textureParameters.texTarget, GL_TEXTURE_WRAP_T, GL_CLAMP);
    
    // 定义纹理的数据类型为float
    glTexImage2D(textureParameters.texTarget, 0, textureParameters.texInternalFormat, unWidth, unHeight, 0, textureParameters.texFormat, GL_FLOAT, 0);
}

void performComputation(void) {
    // 将纹理关联到FBO
    glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, textureParameters.texTarget, yTextID, 0);
    // 将 glslProgram 设为当前程序对象
    glUseProgram(glslProgram);
    // 将 GL_TEXTURE0 设为当前纹理单元
    glActiveTexture(GL_TEXTURE0);
    // 更新uniform变量，将应用程序的fRadiuo的值传递至着色器内部
    glUniform1f(radiusParam, fRadius);
    // 同步线程，以便计时
    glFinish();
    
    // 计时开始
//    CTimer timer;
//    long lTime = 0.0;
//    timer.reset();
    
    //设置写入纹理缓存的类型
    glDrawBuffer(GL_COLOR_ATTACHMENT0_EXT);
    // 将计算范围定义为同样包括矩形的内部
    glPolygonMode(GL_FRONT, GL_FILL);
    
    // 用未归一化的纹理坐标设定计算范围
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0);
    glVertex2f(0.0, 0.0);
    glTexCoord2f(unWidth, 0.0);
    glVertex2f(unWidth, 0.0);
    glTexCoord2f(unWidth, unHeight);
    glVertex2f(unWidth, unHeight);
    glTexCoord2f(0.0, unHeight);
    glVertex2f(0.0, unHeight);
    glEnd();
    
    // 同步线程，终止计时
    glFinish();
//    lTime = timer.getTime();
//    cout<<"Time elapsed: "<<lTime<<" ms."<<endl;
}

// 将数据从当前纹理缓存传至主存储器
void transferFromTexture(float *data) {
    glReadBuffer(GL_COLOR_ATTACHMENT0_EXT);
    glReadPixels(0.0, 0.0, unWidth, unHeight, textureParameters.texFormat, GL_FLOAT, data);
}

// 将数据传送值纹理缓存
void transferToTexture(float *data, GLuint texID) {
    glBindTexture(textureParameters.texTarget, texID);
    glTexSubImage2D(textureParameters.texTarget, 0, 0, 0, unWidth, unHeight, textureParameters.texFormat, GL_FLOAT, data);
}
