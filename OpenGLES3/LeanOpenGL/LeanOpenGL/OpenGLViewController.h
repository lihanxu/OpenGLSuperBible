//
//  OpenGLViewController.h
//  LeanOpenGL
//
//  Created by 李涵旭 on 2022/10/22.
//

#import <GLKit/GLKit.h>

@interface OpenGLViewController : GLKViewController

@property (nonatomic, strong) EAGLContext *context;

/// 配置OpenGL 环境
- (void)setupGL;

/// 释放OpenGL环境
- (void)tearDownGL;

@end
