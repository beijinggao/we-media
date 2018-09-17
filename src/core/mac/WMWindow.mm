//
// Created by gaodong on 2018/9/15.
//

#include "WMWindow.h"
#import "AppDelegate.h"

@implementation WMWindow {
    NSView*        _titlebarView; // NSTitlebarView
    CGFloat        _titlebarHeight;
}


- (instancetype)initWithTitlebarHeight:(CGFloat)titlebarHeight {
    NSUInteger windowStyle = NSTitledWindowMask | NSClosableWindowMask | NSMiniaturizableWindowMask | NSResizableWindowMask;
    if (FBMOSX1010OrNewer()) {
        windowStyle |= NSFullSizeContentViewWindowMask;
    }
    NSSize frameSize = {800,600};
    self = [[WMWindow alloc] initWithContentRect:{{0,0},frameSize} styleMask:windowStyle backing:NSBackingStoreBuffered defer:YES];
    if (FBMOSX1010OrNewer()) {
        self.appearance = [NSAppearance appearanceNamed:NSAppearanceNameVibrantLight];
        self.titleVisibility = NSWindowTitleHidden;
        self.titlebarAppearsTransparent = YES;
    }
    /*self.contentView = [[ContentView alloc] initWithFrame:{{0,0},frameSize}];
    self.collectionBehavior = NSWindowCollectionBehaviorFullScreenPrimary;
    
    auto ud = [NSUserDefaults standardUserDefaults];
    if ([ud boolForKey:@"moves-with-active-space"]) {
        self.collectionBehavior |= NSWindowCollectionBehaviorMoveToActiveSpace;
    }
    self.minSize = {320,300};
    self.releasedWhenClosed = NO;
    self.delegate = self;
    [self center];
    self.frameAutosaveName = @"main";
    self.movableByWindowBackground = YES;
    _titlebarView = [self standardWindowButton:NSWindowCloseButton].superview;
    
    _draggableView = [[DraggableView alloc] init];
    _draggableView.draggingWindow = self;
    
    _titlebarHeight = titlebarHeight;
    [self updateWindowTitlebar];*/
    
    return self;
}


@end
