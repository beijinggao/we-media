//
// Created by gaodong on 2018/8/28.
//

#ifndef WE_MEDIA_REQUEST_CLIENT_H
#define WE_MEDIA_REQUEST_CLIENT_H

#include "include/cef_request.h"
#include "include/internal/cef_ptr.h"
#include "include/cef_urlrequest.h"


class RequestClient : public CefURLRequestClient {

public:
    RequestClient() : upload_total_(0),
                      download_total_(0) {}

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


private:
    uint64 upload_total_;
    uint64 download_total_;
    std::string download_data_;

private:
IMPLEMENT_REFCOUNTING(RequestClient);

};


#endif //WE_MEDIA_REQUEST_CLIENT_H
