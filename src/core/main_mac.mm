//
// Created by gaodong on 2018/9/15.
//

#import <Cocoa/Cocoa.h>
#import "mac/Application.h"
#import "mac/AppDelegate.h"
#include "include/internal/cef_mac.h"
#include "include/internal/cef_ptr.h"


int main(int argc, const char * argv[]) {
    // Provide CEF with command-line arguments.
    CefMainArgs main_args(argc, argv);

    // Initialize the AutoRelease pool.
    NSAutoreleasePool* autopool = [[NSAutoreleasePool alloc] init];

    // Initialize the SimpleApplication instance.
    [Application sharedApplication];

    // Specify CEF global settings here.
    CefSettings settings;

    // SimpleApp implements application-level callbacks for the browser process.
    // It will create the first browser instance in OnContextInitialized() after
    // CEF has initialized.
    CefRefPtr<SimpleApp> app(new SimpleApp);

    // Initialize CEF for the browser process.
    CefInitialize(main_args, settings, app.get(), NULL);

    // Create the application delegate.
    NSObject* delegate = [[AppDelegate alloc] init];
    [delegate performSelectorOnMainThread:@selector(createApplication:)
                               withObject:nil
                            waitUntilDone:NO];

    // Run the CEF message loop. This will block until CefQuitMessageLoop() is
    // called.
    CefRunMessageLoop();

    // Shut down CEF.
    CefShutdown();

    // Release the delegate.
    [delegate release];

    // Release the AutoRelease pool.
    [autopool release];


    return NSApplicationMain(argc, argv);
}
