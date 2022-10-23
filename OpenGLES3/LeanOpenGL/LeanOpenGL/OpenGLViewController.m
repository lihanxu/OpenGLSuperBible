//
//  OpenGLViewController.m
//  LeanOpenGL
//
//  Created by 李涵旭 on 2022/10/22.
//

#import "OpenGLViewController.h"
#import "RendererPresenter.h"

@interface OpenGLViewController ()

@property (strong, nonatomic) NSString *glType;
@property (strong, nonatomic) RendererPresenter *presenter;

@end

@implementation OpenGLViewController

- (void)dealloc {
    [self tearDownGL];
    [self clearContext];
}

- (instancetype)initWithType:(NSString *)type {
    self = [super initWithNibName:nil bundle:nil];
    if (self) {
        self.glType = type;
    }
    return self;
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
    
    self.presenter = [[RendererPresenter alloc] init];
    [self setupGL];
}

/// 清除context
- (void)clearContext {
    if ([EAGLContext currentContext] == self.context) {
        [EAGLContext setCurrentContext:nil];
    }
    self.context = nil;
}

/// 配置OpenGL 环境
- (void)setupGL {
    [EAGLContext setCurrentContext:self.context];
    [self.presenter setupGL:self.glType];
}

/// 释放OpenGL环境
- (void)tearDownGL {
    [EAGLContext setCurrentContext:self.context];
    [self.presenter tearDownGL];
}

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect {
    [self.presenter drawInWidth:view.drawableWidth height:view.drawableHeight];
}

@end
