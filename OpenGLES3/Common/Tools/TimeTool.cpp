//
//  TimeTool.cpp
//  LeanOpenGL
//
//  Created by 李涵旭 on 2022/10/26.
//

#include "TimeTool.hpp"

extern "C" {
#include <sys/time.h>
}

long getCurrentTime() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}
