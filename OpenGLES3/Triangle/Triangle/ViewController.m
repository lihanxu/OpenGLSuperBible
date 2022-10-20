//
//  ViewController.m
//  Triangle
//
//  Created by hansen on 2022/10/17.
//

#import "ViewController.h"
#include "esUtil.h"

extern void esMain( ESContext *esContext );

@interface ViewController () {
    ESContext _esContext;
}

@property (nonatomic, strong) EAGLContext *context;

@end

@implementation ViewController

- (void)dealloc {
    [self tearDownGL];
    [self clearContext];
}

- (void)viewDidLoad {
    [super viewDidLoad];

    [self initGL];
    [self setupGL];
}

/// 初始化OpenGL
- (void)initGL {
    self.context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES3];
    if (self.context == nil) {
        NSLog(@"Failed to create ES context!!");
    }
    GLKView *view = (GLKView *)self.view;
    view.context = self.context;
    view.drawableDepthFormat = GLKViewDrawableDepthFormat24;
}

/// 配置OpenGL 环境
- (void)setupGL {
    [EAGLContext setCurrentContext:self.context];
    memset(&_esContext, 0, sizeof(_esContext));
    esMain(&_esContext);
}

/// 释放OpenGL环境
- (void)tearDownGL {
    [EAGLContext setCurrentContext:self.context];
    if (_esContext.shutdownFunc) {
        _esContext.shutdownFunc(&_esContext);
    }
}

/// 清除context
- (void)clearContext {
    if ([EAGLContext currentContext] == self.context) {
        [EAGLContext setCurrentContext:nil];
    }
    self.context = nil;
}

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect {
    _esContext.width = (GLint)view.drawableWidth;
    _esContext.height = (GLint)view.drawableHeight;
    if (_esContext.drawFunc) {
        _esContext.drawFunc(&_esContext);
    }
}

@end
