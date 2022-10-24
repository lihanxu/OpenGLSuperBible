//
//  BoxRenderer.hpp
//  LeanOpenGL
//
//  Created by 李涵旭 on 2022/10/23.
//

#ifndef BoxRenderer_hpp
#define BoxRenderer_hpp

#include "BaseRenderer.hpp"

class BoxRenderer: public BaseRenderer {
public:
    BoxRenderer(const char *vertextPath, const char *fragmentPath);
    ~BoxRenderer();

    int setupGL();
    void tearDownGL();
    void updateWindowSize(int width, int height);
    void draw();
    
    void move(float radian);
    void move(float front, float right);
    void zoom(float scale);

private:
    class Impl;
    std::unique_ptr<Impl> m_pImpl;
};

#endif /* BoxRenderer_hpp */
