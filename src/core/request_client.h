//
// Created by gaodong on 2018/8/28.
//

#ifndef WE_MEDIA_REQUEST_CLIENT_H
#define WE_MEDIA_REQUEST_CLIENT_H

#include "include/cef_request.h"
#include "include/internal/cef_ptr.h"
#include "include/cef_urlrequest.h"
#include "include/wrapper/cef_helpers.h"
#include <iostream>


class UrlRequestCompletionCallback {
public:
    virtual ~UrlRequestCompletionCallback() {}

    virtual void OnCompletion(CefURLRequest::ErrorCode errorCode, const std::string &data) = 0;
};

class PrintUrlReqCallback : public UrlRequestCompletionCallback {
public:
    void OnCompletion(CefURLRequest::ErrorCode errorCode, const std::string &data);
};


class RequestClient : public CefURLRequestClient {

/*public:
    RequestClient() : upload_total_(0),
                      download_total_(0) {}*/

public:
    RequestClient() : m_callback(0) {
        upload_total_ = 0;
        download_total_ = 0;

        //CEF_REQUIRE_UI_THREAD();
    }

    RequestClient(UrlRequestCompletionCallback *callback) : m_callback(callback) {
        //CEF_REQUIRE_UI_THREAD();
    }

    void OnRequestComplete(CefRefPtr<CefURLRequest> request) OVERRIDE;

    void OnUploadProgress(CefRefPtr<CefURLRequest> request, int64 current, int64 total) OVERRIDE;

    void OnDownloadProgress(CefRefPtr<CefURLRequest> request, int64 current, int64 total) OVERRIDE;

    void OnDownloadData(CefRefPtr<CefURLRequest> request, const void *data, size_t data_length) OVERRIDE;

    bool GetAuthCredentials(bool isProxy,
                            const CefString &host,
                            int port,
                            const CefString &realm,
                            const CefString &scheme,
                            CefRefPtr<CefAuthCallback> callback) OVERRIDE;


    void Request(CefRefPtr<CefRequest> cef_request);

    void Get(const std::string &url, const CefRequest::HeaderMap &headers = CefRequest::HeaderMap());

    void Post(const std::string &url, const CefRefPtr<CefPostData> data,
              const CefRequest::HeaderMap &headers = CefRequest::HeaderMap());

    void SetCompletionCallback(UrlRequestCompletionCallback *callback) {
        m_callback = callback;
    }


private:
    uint64 upload_total_;
    uint64 download_total_;
    std::string download_data_;

private:
    UrlRequestCompletionCallback *m_callback;
    CefRefPtr<CefURLRequest> m_urlRequest;
    std::string m_data;

private:
    DISALLOW_COPY_AND_ASSIGN(RequestClient);

IMPLEMENT_REFCOUNTING(RequestClient);

};


#endif //WE_MEDIA_REQUEST_CLIENT_H
