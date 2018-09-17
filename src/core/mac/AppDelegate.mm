//
// Created by gaodong on 2018/9/15.
//

#import "AppDelegate.h"


@implementation AppDelegate

// Create the application on the UI thread.
- (void)createApplication:(id)object {
    [NSApplication sharedApplication];
    [[NSBundle mainBundle] loadNibNamed:@"MainMenu"
                                  owner:NSApp
                        topLevelObjects:nil];

    // Set the delegate for application events.
    [[NSApplication sharedApplication] setDelegate:self];
}

- (void)tryToTerminateApplication:(NSApplication*)app {
    SimpleHandler* handler = SimpleHandler::GetInstance();
    if (handler && !handler->IsClosing())
        handler->CloseAllBrowsers(false);
}

- (NSApplicationTerminateReply)applicationShouldTerminate:
        (NSApplication*)sender {
    return NSTerminateNow;
}
@end

