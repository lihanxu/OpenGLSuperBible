//
//  OpenGLViewController.m
//  LeanOpenGL
//
//  Created by 李涵旭 on 2022/10/22.
//

#import "OpenGLViewController.h"
#import "RendererPresenter.h"

@interface OpenGLViewController ()

typedef NS_ENUM(NSInteger, GRAction) {
    GRActionNone = 0,
    GRActionMoving = 1,
    GRActionRotate = 2
};

@property (strong, nonatomic) UIView *grView;

@property (strong, nonatomic) NSString *glType;
@property (strong, nonatomic) RendererPresenter *presenter;

@property (assign, nonatomic) GRAction grAction;
@property (assign, nonatomic) CGPoint startPoint;

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
    self.grView = [[UIView alloc] init];
    [self.view addSubview:self.grView];
    
    [self setupGestureRecognizer];
    [self setupViewContext];
    
    self.presenter = [[RendererPresenter alloc] init];
    [self setupGL];
}

/// 添加手势响应

- (void)setupGestureRecognizer {
    self.grView.translatesAutoresizingMaskIntoConstraints=NO;

    UIView *view = self.grView;
    NSArray *constraints = [NSLayoutConstraint constraintsWithVisualFormat:@"H:|-0-[view]-0-|" options:0 metrics:nil views:NSDictionaryOfVariableBindings(view)];
    NSArray *constraints2 = [NSLayoutConstraint constraintsWithVisualFormat:@"V:|-0-[view]-0-|" options:0 metrics:nil views:NSDictionaryOfVariableBindings(view)];
    [self.view addConstraints:constraints];
    [self.view addConstraints:constraints2];
    
    UIPanGestureRecognizer *panGestureRecognizer = [[UIPanGestureRecognizer alloc] initWithTarget:self action:@selector(handlePan:)];
    [self.grView addGestureRecognizer:panGestureRecognizer];
}

/// 初始化context
- (void)setupViewContext {
    self.context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES3];
    if (self.context == nil) {
        NSLog(@"Failed to create ES context!!");
    }
    GLKView *view = (GLKView *)self.view;
    view.context = self.context;
    view.drawableDepthFormat = GLKViewDrawableDepthFormat24;
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

#pragma mark - GestureRecognizer
- (void)handlePan:(UIPanGestureRecognizer*) recognizer {
    NSLog(@"%s", __func__);
    switch (recognizer.state) {
        case UIGestureRecognizerStateBegan:
        {
            CGPoint locPoint = [recognizer locationInView:self.grView];
            if (locPoint.x < self.view.bounds.size.width / 2) {
                self.startPoint = locPoint;
                self.grAction = GRActionMoving;
            } else {
                self.grAction = GRActionRotate;
            }
            break;
        }
        case UIGestureRecognizerStateChanged:
        {
//            if (self.grAction == GRActionMoving) {
//                float radian = 0.0;
//                CGPoint locPoint = [recognizer locationInView:self.grView];
//                float offsetX = locPoint.x - self.startPoint.x;
//                float offsetY = self.startPoint.y - locPoint.y;
//                if (offsetX > 0.0) {
//                    if (offsetY > 0.0) {
//                        radian = atan2f(offsetX, offsetY);
//                    } else {
//                        radian = M_PI - atan2f(offsetX, -offsetY);
//                    }
//                } else {
//                    if (offsetY > 0.0) {
//                        radian = 2 * M_PI - atan2f(-offsetX, offsetY);
//                    } else {
//                        radian = M_PI + atan2f(-offsetX, -offsetY);
//                    }
//                }
//                NSLog(@"radian: %f", radian);
//                [self.presenter moveRadian:radian];
//            }
                
            CGPoint transLation = [recognizer translationInView:self.grView];
            NSLog(@"translation: %@", NSStringFromCGPoint(transLation));
            if (self.grAction == GRActionMoving) {
                [self.presenter moveX:transLation.x Y:transLation.y];
            } else if (self.grAction == GRActionRotate) {
                [self.presenter rotateX:transLation.x Y:-transLation.y];
            }
            break;;
        }
        default:
            self.grAction = GRActionNone;
            break;
    }
    [recognizer setTranslation:CGPointZero inView:self.view];
}

@end
