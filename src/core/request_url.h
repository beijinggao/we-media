//
// Created by gaodong on 2018/8/28.
//

#ifndef WE_MEDIA_REQUEST_URL_H
#define WE_MEDIA_REQUEST_URL_H

#include <string>
#include <iostream>
#include "request_url.h"
#include "include/cef_request.h"
#include "request_client.h"

class RequestUrl : CefTask {

public:
    void parseUrl(std::string url);

public:
    void Execute() OVERRIDE;

    virtual void AddRef() const OVERRIDE {};

    virtual bool Release() const OVERRIDE { return false; };

    virtual bool HasOneRef() const OVERRIDE { return false; };

};


#endif //WE_MEDIA_REQUEST_URL_H
