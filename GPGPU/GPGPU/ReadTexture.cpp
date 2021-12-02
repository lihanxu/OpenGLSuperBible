//
//  ReadTexture.cpp
//  GPGPU
//
//  Created by anker on 2021/12/2.
//

#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLUT/glut.h>

#define WIDTH 2
#define HEIGHT 3

// 删除后面的01就可以运行
int main01(int argc, char **argv) {
    int nWidth = (int)WIDTH;
    int nHeight = (int)HEIGHT;
    int nSize = nWidth * nHeight;
    
    //创建输入数据
    float *pfInput = new float[4*nSize];
    float *pfOutput = new float[4*nSize];
    
    for (int i = 0; i < nSize * 4; i++) {
        pfInput[i] = i + 1.2345;
    }
    
    // 设定GLUT、创建新窗口，以便有一个有效的OpenGL环境。然后取得OpenGL扩展的入口
    glutInit(&argc, argv);
    glutCreateWindow("GPGPU Tutorial");
    glewInit();
    
    //创建FBO并绑定
    GLuint fb;
    glGenFramebuffers(1, &fb);
    glBindFramebuffer(GL_FRAMEBUFFER, fb);
    
    // 创建纹理对象并绑定
    GLuint tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    
    // 将纹理关联到FBO
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, tex, 0);
    
    // 将纹理数据类型定义为单精度浮点数
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA_FLOAT32_ATI, nWidth, nHeight, 0, GL_RGBA, GL_FLOAT, NULL);
    // 将数据传至纹理缓存
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, nWidth, nHeight, GL_RGBA, GL_FLOAT, pfInput);
    
    // 读回
    glReadBuffer(GL_COLOR_ATTACHMENT0);
    glReadPixels(0, 0, nWidth, nHeight, GL_RGBA, GL_FLOAT, pfOutput);
    
    // 打印并检查结果
    bool bCmp = true;
    for (int i = 0; i < nSize * 4; i++) {
        printf("%d:\t%f\t%f\n", i, pfInput[i], pfOutput[i]);
        if (pfInput[i] != pfOutput[i]) {
            bCmp = false;
        }
    }
    if (bCmp) {
        printf("Round trip complete!\n");
    } else {
        printf("Round trip failed!\n");
    }
    delete[] pfInput;
    delete[] pfOutput;
    glDeleteFramebuffers(1, &fb);
    glDeleteTextures(1, &tex);

    return 0;
}
