//
//  OpenGLViewController.m
//  LeanOpenGL
//
//  Created by 李涵旭 on 2022/10/22.
//

#import "OpenGLViewController.h"

@implementation OpenGLViewController

- (void)dealloc {
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
}

/// 释放OpenGL环境
- (void)tearDownGL {
    [EAGLContext setCurrentContext:self.context];
}

/// 清除context
- (void)clearContext {
    if ([EAGLContext currentContext] == self.context) {
        [EAGLContext setCurrentContext:nil];
    }
    self.context = nil;
}

@end
