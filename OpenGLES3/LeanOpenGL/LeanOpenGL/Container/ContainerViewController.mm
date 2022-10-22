//
//  ContainerViewController.m
//  LeanOpenGL
//
//  Created by 李涵旭 on 2022/10/22.
//

#import "ContainerViewController.h"
#include "ContainerRenderer.hpp"

@interface ContainerViewController () {
    ContainerRenderer *_render;
}

@end

@implementation ContainerViewController

/// 配置OpenGL 环境
- (void)setupGL {
    [super setupGL];
    NSString *vPath = [[NSBundle mainBundle] pathForResource:@"Container" ofType:@"vs"];
    NSString *fPath = [[NSBundle mainBundle] pathForResource:@"Container" ofType:@"fs"];
    _render = new ContainerRenderer([vPath cStringUsingEncoding:NSUTF8StringEncoding], [fPath cStringUsingEncoding:NSUTF8StringEncoding]);
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
