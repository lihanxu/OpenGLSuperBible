//
//  OpenGLViewController.h
//  LeanOpenGL
//
//  Created by 李涵旭 on 2022/10/22.
//

#import <GLKit/GLKit.h>

@interface OpenGLViewController : GLKViewController

@property (nonatomic, strong) EAGLContext *context;

/// 根据名字配置不同的 OpenGL 环境
- (instancetype)initWithType:(NSString *)type;

@end
