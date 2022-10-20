//
//  ESRender.hpp
//  LeanOpenGL
//
//  Created by hansen on 2022/10/20.
//

#ifndef ESRender_hpp
#define ESRender_hpp

#include <stdio.h>
#include <string>

class ESRender {
public:
    ESRender(const char *vertextPath, const char *fragmentPath);
    ~ESRender();

    int setupGL();
    void tearDownGL();
    void updateWindowSize(int width, int height);
    void draw();

private:
    class Impl;
    std::unique_ptr<Impl> m_pImpl;
};

#endif /* ESRender_hpp */
