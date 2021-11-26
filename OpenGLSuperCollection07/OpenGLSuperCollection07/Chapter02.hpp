//
//  Chapter02.h
//  OpenGLSuperCollection07
//
//  Created by anker on 2021/7/27.
//

#ifndef Chapter02_hpp
#define Chapter02_hpp

#include "Chapter.hpp"

class Chapter02: Chapter {
public:
    Chapter02();
    ~Chapter02();
    
    void startup();
    void shutdown();
    void render(double currentTime);
    
    GLuint completeShaders(void);
};

#endif /* Chapter02_hpp */
