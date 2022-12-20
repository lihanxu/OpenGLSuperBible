//
//  Nanosuit.hpp
//  LeanOpenGL
//
//  Created by 李涵旭 on 2022/12/18.
//

#ifndef Nanosuit_hpp
#define Nanosuit_hpp

#include "BaseRenderer.hpp"

class Nanosuit: public BaseRenderer {
public:
    Nanosuit(const char *vertextPath, const char *fragmentPath);
    ~Nanosuit();

    int setupGL();
    void tearDownGL();
    void updateWindowSize(int width, int height);
    void draw();
    
    void move(float radian);
    void move(float front, float right);
    void zoom(float scale);
    void rotate(float x, float y);

private:
    class Impl;
    std::unique_ptr<Impl> m_pImpl;
};

#endif /* Nanosuit_hpp */
