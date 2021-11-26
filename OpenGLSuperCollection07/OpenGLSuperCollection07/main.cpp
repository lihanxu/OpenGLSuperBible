//
//  main.cpp
//  OpenGLSuperCollection07
//
//  Created by anker on 2021/7/27.
//

#define _DEBUG

#include "sb7.h"
#include "Chapter02.hpp"
#include "Chapter03.hpp"

enum ChapterNum {
    ChapterNum02,
    ChapterNum03,
    ChapterNum04,
    ChapterNum05
};

#define CHAPTER_NUM     ChapterNum03

class my_application: public sb7::application
{
public:
    ChapterNum chapterNum;
    Chapter *chapter;
    
public:
    my_application() {
        chapterNum = CHAPTER_NUM;
        
        switch (chapterNum) {
            case ChapterNum02:
                chapter = (Chapter *)new Chapter02();
                break;
            case ChapterNum03:
                chapter = (Chapter *)new Chapter03();
                break;
                
            default:
                break;
        }
    }
    
    ~my_application() {
        
    }
    
    void startup() {
        chapter->startup();
    }
    
    void shutdown() {
        chapter->shutdown();
    }
    
    void render(double currentTime)
    {
        chapter->render(currentTime);
    }
    
};

DECLARE_MAIN(my_application)
