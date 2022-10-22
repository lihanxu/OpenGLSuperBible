//
//  ContainerRenderer.hpp
//  LeanOpenGL
//
//  Created by 李涵旭 on 2022/10/20.
//

#ifndef ContainerRender_hpp
#define ContainerRender_hpp

#include <stdio.h>
#include <memory>

class ContainerRenderer {
public:
    ContainerRenderer(const char *vertextPath, const char *fragmentPath);
    ~ContainerRenderer();

    int setupGL();
    void tearDownGL();
    void updateWindowSize(int width, int height);
    void draw();

private:
    class Impl;
    std::unique_ptr<Impl> m_pImpl;
};
#endif /* ContainerRender_hpp */
