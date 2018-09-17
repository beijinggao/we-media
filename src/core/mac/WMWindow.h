//
// Created by gaodong on 2018/9/15.
//

//#ifndef WE_MEDIA_WMWINDOW_H
//#define WE_MEDIA_WMWINDOW_H
#import <Cocoa/Cocoa.h>
#import <AppKit/AppKit.h>



@interface WMWindow : NSWindow <NSWindowDelegate>


@property (nonatomic) CGFloat titlebarHeight;

- (instancetype)initWithTitlebarHeight:(CGFloat)titlebarHeight;

- (void)setMainView:(NSView*)mainView;

- (void)showTitlebarAnimate:(BOOL)animate;
- (void)hideTitlebarAnimate:(BOOL)animate;

- (void)updateWindowTitlebar;


@end

//#endif //WE_MEDIA_WMWINDOW_H
