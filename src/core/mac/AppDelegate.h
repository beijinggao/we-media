//
// Created by gaodong on 2018/9/15.
//

#ifndef WE_MEDIA_APPDELEGATE_H
#define WE_MEDIA_APPDELEGATE_H
#import <Cocoa/Cocoa.h>


@interface AppDelegate : NSObject <NSApplicationDelegate>

- (void)createApplication:(id)object;
- (void)tryToTerminateApplication:(NSApplication*)app;

@end


#endif //WE_MEDIA_APPDELEGATE_H
