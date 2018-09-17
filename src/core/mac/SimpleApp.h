//
// Created by gaodong on 2018/9/18.
//

#ifndef WE_MEDIA_SIMPLEAPP_H
#define WE_MEDIA_SIMPLEAPP_H


#include "include/cef_app.h"

// Implement application-level callbacks for the browser process.
class SimpleApp : public CefApp, public CefBrowserProcessHandler {
public:
    SimpleApp();

    // CefApp methods:
    virtual CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler()
    OVERRIDE {
        return this;
    }

    // CefBrowserProcessHandler methods:
    virtual void OnContextInitialized() OVERRIDE;

private:
    // Include the default reference counting implementation.
IMPLEMENT_REFCOUNTING(SimpleApp);
};

#endif //WE_MEDIA_SIMPLEAPP_H
