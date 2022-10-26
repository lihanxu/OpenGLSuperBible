//
//  Illumination.hpp
//  LeanOpenGL
//
//  Created by 李涵旭 on 2022/10/26.
//

#ifndef Illumination_hpp
#define Illumination_hpp

#include "BaseRenderer.hpp"

class Illumination: public BaseRenderer {
public:
    Illumination(const char *vertextPath, const char *fragmentPath);
    ~Illumination();

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

#endif /* Illumination_hpp */
