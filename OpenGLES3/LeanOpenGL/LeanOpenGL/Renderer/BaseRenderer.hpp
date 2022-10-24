//
//  BaseRenderer.hpp
//  LeanOpenGL
//
//  Created by 李涵旭 on 2022/10/23.
//

#ifndef BaseRenderer_hpp
#define BaseRenderer_hpp

#include <stdio.h>
#include <memory>

class BaseRenderer {
public:
    BaseRenderer(const char *vertextPath, const char *fragmentPath) {};
    ~BaseRenderer() {};

    virtual int setupGL() = 0;
    virtual void tearDownGL() = 0;
    virtual void updateWindowSize(int width, int height) = 0;
    virtual void draw() = 0;
    
    void move(float front, float right) {};
    void zoom(float scale) {};
    void move(float radian) {};
};

#endif /* BaseRenderer_hpp */
