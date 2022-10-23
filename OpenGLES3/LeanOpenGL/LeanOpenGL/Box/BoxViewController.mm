//
//  BoxViewController.m
//  LeanOpenGL
//
//  Created by 李涵旭 on 2022/10/23.
//

#import "BoxViewController.h"
#include "BoxRenderer.hpp"

@interface BoxViewController () {
    BoxRenderer *_render;
}

@end

@implementation BoxViewController

/// 配置OpenGL 环境
- (void)setupGL {
    [super setupGL];
    NSString *vPath = [[NSBundle mainBundle] pathForResource:@"Box" ofType:@"vs"];
    NSString *fPath = [[NSBundle mainBundle] pathForResource:@"Box" ofType:@"fs"];
    _render = new BoxRenderer([vPath cStringUsingEncoding:NSUTF8StringEncoding], [fPath cStringUsingEncoding:NSUTF8StringEncoding]);
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
