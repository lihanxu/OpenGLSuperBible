//
//  MainViewPresenter.m
//  LeanOpenGL
//
//  Created by 李涵旭 on 2022/10/21.
//

#import "MainViewPresenter.h"
#import "Triangle/TriangleViewController.h"
#import "Container/ContainerViewController.h"
#import "Box/BoxViewController.h"

@interface MainViewPresenter ()

@property (strong, nonatomic) NSArray *items;

@end

@implementation MainViewPresenter

- (instancetype)init {
    self = [super init];
    self.items = [[NSArray alloc] initWithObjects:
                  @"Triangle",
                  @"Container",
                  @"Box",
                  nil];
    return self;
}

- (NSArray *)getItems {
    return self.items;
}

- (OpenGLViewController *)getViewController:(NSString *)itemName {
    OpenGLViewController *vc = nil;
    if ([itemName isEqualToString:@"Triangle"]) {
        vc = [[TriangleViewController alloc] init];
    } else if ([itemName isEqualToString:@"Container"]) {
        vc = [[ContainerViewController alloc] init];
    } else if ([itemName isEqualToString:@"Box"]) {
        vc = [[BoxViewController alloc] init];
    }
    return vc;
}

@end
