//
//  MainViewPresenter.h
//  LeanOpenGL
//
//  Created by 李涵旭 on 2022/10/21.
//

#import <UIKit/UIKit.h>
#import "OpenGLViewController.h"

NS_ASSUME_NONNULL_BEGIN

@interface MainViewPresenter : NSObject

- (NSArray *)getItems;

- (OpenGLViewController *)getViewController:(NSString *)itemName;

@end

NS_ASSUME_NONNULL_END
