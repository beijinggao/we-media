//
// Created by gaodong on 2018/8/28.
//

#ifndef WE_MEDIA_REQUEST_CLIENT_H
#define WE_MEDIA_REQUEST_CLIENT_H

#include "include/cef_request.h"
#include "include/internal/cef_ptr.h"
#include "include/cef_urlrequest.h"
#include "include/wrapper/cef_helpers.h"
#include "include/cef_waitable_event.h"
#include "include/wrapper/cef_closure_task.h"
#include "include/base/cef_bind.h"
//#include "tests/gtest/include/gtest/gtest.h"
#include <iostream>


// Assert that execution is occuring on the named thread.
#define EXPECT_UI_THREAD() EXPECT_TRUE(CefCurrentlyOn(TID_UI));
#define EXPECT_IO_THREAD() EXPECT_TRUE(CefCurrentlyOn(TID_IO));
#define EXPECT_FILE_THREAD() EXPECT_TRUE(CefCurrentlyOn(TID_FILE));
#define EXPECT_RENDERER_THREAD() EXPECT_TRUE(CefCurrentlyOn(TID_RENDERER));

class RequestClient : public CefURLRequestClient {

public:
    typedef base::Callback<void(CefRefPtr<RequestClient>)> RequestCompleteCallback;

    explicit RequestClient(const RequestCompleteCallback &complete_callback)
            : complete_callback_(complete_callback),
              request_complete_ct_(0),
              upload_progress_ct_(0),
              download_progress_ct_(0),
              download_data_ct_(0),
              upload_total_(0),
              download_total_(0),
              status_(UR_UNKNOWN),
              error_code_(ERR_NONE),
              response_was_cached_(false) {
        CEF_REQUIRE_UI_THREAD();
        event_ = CefWaitableEvent::CreateWaitableEvent(true, false);

        std::cout << complete_callback_.is_null() << std::endl;
        //EXPECT_FALSE(complete_callback_.is_null());
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

    void Get(const std::string &url, const CefRequest::HeaderMap &headers = CefRequest::HeaderMap());

    void Post(const std::string &url, const CefRefPtr<CefPostData> data,
              const CefRequest::HeaderMap &headers = CefRequest::HeaderMap());


public:
    void RunOnUIThread() {
        CefCurrentlyOn(TID_UI);
        std::cout << "eeeeeeeeee" << CefCurrentlyOn(TID_UI) << std::endl;
        CefRefPtr<CefRequest> request = CefRequest::Create();
        request->SetMethod("GET");
        request->SetURL("http://www.baidu.com");

        std::cout << "*********************" << std::endl;
        CefURLRequest::Create(request, this, NULL);
        std::cout << "*********************" << std::endl;

    }

    void CompleteOnUIThread() {
        CefCurrentlyOn(TID_UI);
        //EXPECT_UI_THREAD();
        // Signal that the test is complete.
        event_->Signal();
    }

    void RunTest() {
        std::cout << "*********************" << std::endl;

        CefPostTask(TID_UI, base::Bind(&RequestClient::RunOnUIThread, this));
        std::cout << "*********aaa************" << std::endl;

        // Wait for the test to complete.
        event_->Wait();
        //event_->TimedWait(500);
    }


private:
    RequestCompleteCallback complete_callback_;
    CefRefPtr<CefWaitableEvent> event_;

public:
    int request_complete_ct_;
    int upload_progress_ct_;
    int download_progress_ct_;
    int download_data_ct_;

    uint64 upload_total_;
    uint64 download_total_;
    std::string download_data_;
    CefRefPtr<CefRequest> request_;
    CefURLRequest::Status status_;
    CefURLRequest::ErrorCode error_code_;
    CefRefPtr<CefResponse> response_;
    bool response_was_cached_;

private:
IMPLEMENT_REFCOUNTING(RequestClient);

};


#endif //WE_MEDIA_REQUEST_CLIENT_H
