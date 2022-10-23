//
//  RendererPresenter.h
//  LeanOpenGL
//
//  Created by 李涵旭 on 2022/10/23.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface RendererPresenter : NSObject

- (void)setupGL:(NSString *)name;
- (void)tearDownGL;
- (void)drawInWidth:(NSInteger)width height:(NSInteger)height;

@end

NS_ASSUME_NONNULL_END
