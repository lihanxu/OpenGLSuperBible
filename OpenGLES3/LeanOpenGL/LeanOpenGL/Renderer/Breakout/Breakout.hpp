//
//  Breakout.hpp
//  LeanOpenGL
//
//  Created by 李涵旭 on 2022/12/20.
//

#ifndef Breakout_hpp
#define Breakout_hpp

#include "BaseRenderer.hpp"

class Breakout: public BaseRenderer {
public:
    Breakout();
    ~Breakout();

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

#endif /* Breakout_hpp */
