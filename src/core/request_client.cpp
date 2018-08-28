//
// Created by gaodong on 2018/8/28.
//

#include "request_client.h"

class MyRequestClient : public CefURLRequestClient {
public:
    MyRequestClient()
            : upload_total_(0),
              download_total_(0) {}

    virtual void OnRequestComplete(CefRefPtr <CefURLRequest> request)

    OVERRIDE {
        CefURLRequest::Status status = request->GetRequestStatus();
        CefURLRequest::ErrorCode error_code = request->GetRequestError();
        CefRefPtr <CefResponse> response = request->GetResponse();

        // Do something with the response...
    }

    virtual void OnUploadProgress(CefRefPtr <CefURLRequest> request,
                                  uint64 current,
                                  uint64 total)

    OVERRIDE {
        upload_total_ = total;
    }

    virtual void OnDownloadProgress(CefRefPtr <CefURLRequest> request,
                                    uint64 current,
                                    uint64 total)

    OVERRIDE {
        download_total_ = total;
    }

    virtual void OnDownloadData(CefRefPtr <CefURLRequest> request,
                                const void *data,
                                size_t data_length)

    OVERRIDE {
        download_data_ += std::string(static_cast<const char *>(data), data_length);
    }

private:
    uint64 upload_total_;
    uint64 download_total_;
    std::string download_data_;

private:
    IMPLEMENT_REFCOUNTING(MyRequestClient);
};
