//
// Created by gaodong on 2018/8/28.
//

#include <iostream>
#include "include/cef_urlrequest.h"
#include "request_client.h"


void RequestClient::OnRequestComplete(CefRefPtr<CefURLRequest> request) {

    CefURLRequest::Status status = request->GetRequestStatus();
    CefURLRequest::ErrorCode error_code = request->GetRequestError();
    CefRefPtr<CefResponse> response = request->GetResponse();

    std::cout << status << std::endl;
    std::cout << error_code << std::endl;

    std::cout << response << std::endl;
    std::cout << upload_total_ << std::endl;
    std::cout << download_total_ << std::endl;


}

void RequestClient::OnUploadProgress(CefRefPtr<CefURLRequest> request, int64 current, int64 total) {
    upload_total_ = total;
}

void RequestClient::OnDownloadProgress(CefRefPtr<CefURLRequest> request, int64 current, int64 total) {
    CefRefPtr<CefResponse> response_ = request->GetResponse();

    //EXPECT_TRUE(response_.get());
    //EXPECT_TRUE(response_->IsReadOnly());

    download_total_ = total;
}

void RequestClient::OnDownloadData(CefRefPtr<CefURLRequest> request, const void *data, size_t data_length) {
    download_data_ += std::string(static_cast<const char *>(data), data_length);
}

bool RequestClient::GetAuthCredentials(bool isProxy,
                                       const CefString &host,
                                       int port,
                                       const CefString &realm,
                                       const CefString &scheme,
                                       CefRefPtr<CefAuthCallback> callback) {
    return false;
};

