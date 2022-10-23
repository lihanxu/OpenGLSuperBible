//
//  RendererPresenter.m
//  LeanOpenGL
//
//  Created by 李涵旭 on 2022/10/23.
//

#import "RendererPresenter.h"
#import "BaseRenderer.hpp"
#include "Triangle/TriangleRenderer.hpp"
#include "Container/ContainerRenderer.hpp"
#include "Box/BoxRenderer.hpp"

@interface RendererPresenter () {
    BaseRenderer *_renderer;
}

@property (strong, nonatomic) NSString *name;

@end

@implementation RendererPresenter

/// 配置OpenGL 环境
- (void)setupGL:(NSString *)name {
    self.name = name;
    if ([name isEqualToString:@"Triangle"]) {
        NSString *vPath = [[NSBundle mainBundle] pathForResource:@"Triangle" ofType:@"vs"];
        NSString *fPath = [[NSBundle mainBundle] pathForResource:@"Triangle" ofType:@"fs"];
        _renderer = new TriangleRenderer([vPath cStringUsingEncoding:NSUTF8StringEncoding], [fPath cStringUsingEncoding:NSUTF8StringEncoding]);
        
    } else if ([name isEqualToString:@"Container"]) {
        NSString *vPath = [[NSBundle mainBundle] pathForResource:@"Container" ofType:@"vs"];
        NSString *fPath = [[NSBundle mainBundle] pathForResource:@"Container" ofType:@"fs"];
        _renderer = new ContainerRenderer([vPath cStringUsingEncoding:NSUTF8StringEncoding], [fPath cStringUsingEncoding:NSUTF8StringEncoding]);
        
    } else if ([name isEqualToString:@"Box"]) {
        NSString *vPath = [[NSBundle mainBundle] pathForResource:@"Box" ofType:@"vs"];
        NSString *fPath = [[NSBundle mainBundle] pathForResource:@"Box" ofType:@"fs"];
        _renderer = new BoxRenderer([vPath cStringUsingEncoding:NSUTF8StringEncoding], [fPath cStringUsingEncoding:NSUTF8StringEncoding]);
        
    } else {
        return;
    }
    _renderer->setupGL();
}

/// 释放OpenGL环境
- (void)tearDownGL {
    if (!_renderer) {
        return;
    }
    _renderer->tearDownGL();
    if ([self.name isEqualToString:@"Triangle"]) {
        delete (TriangleRenderer*)_renderer;
    } else if ([self.name isEqualToString:@"Container"]) {
        delete (ContainerRenderer*)_renderer;
    } else if ([self.name isEqualToString:@"Box"]) {
        delete (BoxRenderer*)_renderer;
    }
}

/// 清除context
- (void)drawInWidth:(NSInteger)width height:(NSInteger)height {
    if (!_renderer) {
        return;
    }
    _renderer->updateWindowSize((int)width, (int)height);
    _renderer->draw();
}

@end
