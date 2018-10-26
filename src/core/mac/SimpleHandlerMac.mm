// Copyright (c) 2013 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.

#include "SimpleHandler.h"

#import <Cocoa/Cocoa.h>

#include "include/cef_browser.h"

void SimpleHandler::PlatformTitleChange(CefRefPtr<CefBrowser> browser,
                                        const CefString& title) {
  NSView* view = (NSView*)browser->GetHost()->GetWindowHandle();
  NSWindow* window = [view window];
  std::string titleStr(title);
  NSString* str = [NSString stringWithUTF8String:titleStr.c_str()];
  /*NSLog(@"cccccccccccccccccccc%@",str);

  if([str rangeOfString:@"login"].location == NSNotFound){
    CefWindowInfo window_info;
    CefBrowserSettings browser_settings;
    std::string url;
    url="http://www.baidu.com";
    browser->GetHost()->CreateBrowser(window_info,browser->GetHost()->GetClient(),url,browser_settings,NULL);
  }*/

  NSUInteger windowStyle = NSTitledWindowMask | NSClosableWindowMask | NSMiniaturizableWindowMask | NSResizableWindowMask | NSFullSizeContentViewWindowMask;
  [window setTitle:str];
  [window center];
  [window setStyleMask:windowStyle];
  [window setAppearance:[NSAppearance appearanceNamed:NSAppearanceNameVibrantLight]];
  [window setTitlebarAppearsTransparent:YES];
  [window setTitleVisibility:NSWindowTitleHidden];

}
