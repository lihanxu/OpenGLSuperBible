//
//  ContainerRender.hpp
//  LeanOpenGL
//
//  Created by 李涵旭 on 2022/10/20.
//

#ifndef ContainerRender_hpp
#define ContainerRender_hpp

#include <stdio.h>
#include <memory>

class ContainerRender {
public:
    ContainerRender(const char *vertextPath, const char *fragmentPath);
    ~ContainerRender();

    int setupGL();
    void tearDownGL();
    void updateWindowSize(int width, int height);
    void draw();

private:
    class Impl;
    std::unique_ptr<Impl> m_pImpl;
};
#endif /* ContainerRender_hpp */
