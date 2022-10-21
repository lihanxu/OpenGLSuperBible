//
//  TriangleViewController.m
//  LeanOpenGL
//
//  Created by 李涵旭 on 2022/10/21.
//

#import "TriangleViewController.h"
#include "TriangleRender.hpp"

@interface TriangleViewController () {
    TriangleRender *_render;
}

@end

@implementation TriangleViewController

/// 配置OpenGL 环境
- (void)setupGL {
    [super setupGL];
    NSString *vPath = [[NSBundle mainBundle] pathForResource:@"Triangle" ofType:@"vs"];
    NSString *fPath = [[NSBundle mainBundle] pathForResource:@"Triangle" ofType:@"fs"];
    _render = new TriangleRender([vPath cStringUsingEncoding:NSUTF8StringEncoding], [fPath cStringUsingEncoding:NSUTF8StringEncoding]);
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
