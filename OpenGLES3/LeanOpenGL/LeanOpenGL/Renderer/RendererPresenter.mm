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
#include "Illumination/Illumination.hpp"

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
        
    } else if ([name isEqualToString:@"Illumination"]) {
        NSString *vPath = [[NSBundle mainBundle] pathForResource:@"Illumination" ofType:@"vs"];
        NSString *fPath = [[NSBundle mainBundle] pathForResource:@"Illumination" ofType:@"fs"];
        _renderer = new Illumination([vPath cStringUsingEncoding:NSUTF8StringEncoding], [fPath cStringUsingEncoding:NSUTF8StringEncoding]);
        
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
        delete (TriangleRenderer *)_renderer;
    } else if ([self.name isEqualToString:@"Container"]) {
        delete (ContainerRenderer *)_renderer;
    } else if ([self.name isEqualToString:@"Box"]) {
        delete (BoxRenderer *)_renderer;
    } else if ([self.name isEqualToString:@"Illumination"]) {
        delete (Illumination *)_renderer;
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

#pragma mark - Move
- (void)moveX:(float)x Y:(float)y {
    if ([self.name isEqualToString:@"Box"]) {
        BoxRenderer *renderer = (BoxRenderer *)_renderer;
        renderer->move(y, x);
    } else if ([self.name isEqualToString:@"Illumination"]) {
        Illumination *renderer = (Illumination *)_renderer;
        renderer->move(y, x);
    }
}

- (void)moveRadian:(float)radian {
    if ([self.name isEqualToString:@"Box"]) {
        BoxRenderer *renderer = (BoxRenderer *)_renderer;
        renderer->move(radian);
    } else if ([self.name isEqualToString:@"Illumination"]) {
        Illumination *renderer = (Illumination *)_renderer;
        renderer->move(radian);
    }
}

- (void)zoom:(float)scale {
    if ([self.name isEqualToString:@"Box"]) {
        BoxRenderer *renderer = (BoxRenderer *)_renderer;
        renderer->zoom(scale);
    } else if ([self.name isEqualToString:@"Illumination"]) {
        Illumination *renderer = (Illumination *)_renderer;
        renderer->zoom(scale);
    }
}
    
- (void)rotateX:(float)x Y:(float)y {
    if ([self.name isEqualToString:@"Box"]) {
        BoxRenderer *renderer = (BoxRenderer *)_renderer;
        renderer->rotate(x, y);
    } else if ([self.name isEqualToString:@"Illumination"]) {
        Illumination *renderer = (Illumination *)_renderer;
        renderer->rotate(x, y);
    }
}

@end
