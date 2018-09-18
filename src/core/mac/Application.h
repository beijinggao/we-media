//
// Created by gaodong on 2018/9/18.
//

#ifndef WE_MEDIA_APPLICATION_H
#define WE_MEDIA_APPLICATION_H
#import "AppDelegate.h"
#include "include/cef_application_mac.h"
#include "include/wrapper/cef_helpers.h"


// Provide the CefAppProtocol implementation required by CEF.
@interface Application : NSApplication<CefAppProtocol> {
@private
BOOL handlingSendEvent_;
}
@end


#endif //WE_MEDIA_APPLICATION_H
