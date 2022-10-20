//
//  ViewController.m
//  LeanOpenGL
//
//  Created by hansen on 2022/10/20.
//

#import "ViewController.h"
#include "ESRender.hpp"

@interface ViewController () {
    ESRender *_render;
}

@property (nonatomic, strong) EAGLContext *context;

@end

@implementation ViewController

- (void)dealloc {
    delete _render;
    [self tearDownGL];
    [self clearContext];
}

- (void)viewDidLoad {
    [super viewDidLoad];

    self.context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES3];
    if (self.context == nil) {
        NSLog(@"Failed to create ES context!!");
    }
    GLKView *view = (GLKView *)self.view;
    view.context = self.context;
    view.drawableDepthFormat = GLKViewDrawableDepthFormat24;
    
    [self setupGL];
}

/// 配置OpenGL 环境
- (void)setupGL {
    [EAGLContext setCurrentContext:self.context];
    NSString *vPath = [[NSBundle mainBundle] pathForResource:@"Triangle" ofType:@"vs"];
    NSString *fPath = [[NSBundle mainBundle] pathForResource:@"Triangle" ofType:@"fs"];
    _render = new ESRender([vPath cStringUsingEncoding:NSUTF8StringEncoding], [fPath cStringUsingEncoding:NSUTF8StringEncoding]);
    _render->setupGL();
}

/// 释放OpenGL环境
- (void)tearDownGL {
    [EAGLContext setCurrentContext:self.context];
    _render->tearDownGL();
}

/// 清除context
- (void)clearContext {
    if ([EAGLContext currentContext] == self.context) {
        [EAGLContext setCurrentContext:nil];
    }
    self.context = nil;
}

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect {
    _render->updateWindowSize((int)view.drawableWidth, (int)view.drawableHeight);
    _render->draw();
}

@end
