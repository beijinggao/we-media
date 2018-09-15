//
// Created by gaodong on 2018/9/15.
//

#import "AppDelegate.h"
#import "WMWindow.h"



#define USE_BLURRY_BACKGROUND 0

static NSString* kDefaultWindowTitle = @"WeMedia";






@interface AppDelegate ()

/*@property (nonatomic, readonly) BOOL canMakeTextLarger;
- (IBAction)makeTextLarger:(id)sender;
@property (nonatomic, readonly) BOOL canMakeTextSmaller;
- (IBAction)makeTextSmaller:(id)sender;
@property (nonatomic, readonly) BOOL canMakeTextStandardSize;
- (IBAction)makeTextStandardSize:(id)sender;
- (void)updateNetReach:(SCNetworkConnectionFlags)flags;*/

@end

@implementation AppDelegate{
    WMWindow*           _window;
}

const CGFloat kTitlebarHeightAtDefaultScale = 50;

- (void)applicationDidFinishLaunching:(NSNotification*)notification {
    [NSUserNotificationCenter defaultUserNotificationCenter].delegate = self;
    // Create main window
    _window = [[WMWindow alloc] initWithTitlebarHeight:kTitlebarHeightAtDefaultScale];


}

- (NSWindow*)mainWindow {
    return _window;
}

@end

