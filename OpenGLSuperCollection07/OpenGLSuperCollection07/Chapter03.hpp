//
//  Chapter03.hpp
//  OpenGLSuperCollection07
//
//  Created by anker on 2021/7/28.
//

#ifndef Chapter03_hpp
#define Chapter03_hpp

#include "Chapter.hpp"

class Chapter03: Chapter {
public:
    Chapter03();
    ~Chapter03();
    
    void startup();
    void shutdown();
    void render(double currentTime);
    
    GLuint completeShaders(void);
};
#endif /* Chapter03_hpp */
