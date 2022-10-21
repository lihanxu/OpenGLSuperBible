//
//  ContainerViewController.m
//  LeanOpenGL
//
//  Created by 李涵旭 on 2022/10/22.
//

#import "ContainerViewController.h"
#include "ContainerRender.hpp""

@interface ContainerViewController () {
    ContainerRender *_render;
}

@end

@implementation ContainerViewController

/// 配置OpenGL 环境
- (void)setupGL {
    [super setupGL];
    NSString *vPath = [[NSBundle mainBundle] pathForResource:@"Triangle" ofType:@"vs"];
    NSString *fPath = [[NSBundle mainBundle] pathForResource:@"Triangle" ofType:@"fs"];
    _render = new ContainerRender([vPath cStringUsingEncoding:NSUTF8StringEncoding], [fPath cStringUsingEncoding:NSUTF8StringEncoding]);
    _render->setupGL();
}

- (void)tearDownGL {
    [super tearDownGL];
    _render->tearDownGL();
    delete _render;
}

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect {
    _render->updateWindowSize((int)view.drawableWidth, (int)view.drawableHeight);
    _render->draw();
}

@end