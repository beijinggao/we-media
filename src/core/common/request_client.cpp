//
// Created by gaodong on 2018/8/28.
//

#include "request_client.h"

void RequestClient::OnRequestComplete(CefRefPtr<CefURLRequest> request) {
    CEF_REQUIRE_UI_THREAD();

    request_complete_ct_++;

    request_ = request->GetRequest();
    //EXPECT_TRUE(request_->IsReadOnly());
    status_ = request->GetRequestStatus();
    error_code_ = request->GetRequestError();
    response_was_cached_ = request->ResponseWasCached();
    response_ = request->GetResponse();

    std::cout << "*********************" << std::endl;
    if (response_) {
        //EXPECT_TRUE(response_->IsReadOnly());
        std::cout << response_->IsReadOnly() << std::endl;
    }

    complete_callback_.Run(this);
    CefPostTask(TID_UI, base::Bind(&RequestClient::CompleteOnUIThread, this));


}

void RequestClient::OnUploadProgress(CefRefPtr<CefURLRequest> request, int64 current, int64 total) {
    upload_progress_ct_++;
    upload_total_ = total;
}

void RequestClient::OnDownloadProgress(CefRefPtr<CefURLRequest> request, int64 current, int64 total) {
    response_ = request->GetResponse();
    //EXPECT_TRUE(response_.get());
    //EXPECT_TRUE(response_->IsReadOnly());
    std::cout << response_->IsReadOnly() << std::endl;
    std::cout << response_.get() << std::endl;
    download_progress_ct_++;
    download_total_ = total;

}

void RequestClient::OnDownloadData(CefRefPtr<CefURLRequest> request, const void *data, size_t data_length) {
    response_ = request->GetResponse();
    //EXPECT_TRUE(response_.get());
    //EXPECT_TRUE(response_->IsReadOnly());
    std::cout << response_->IsReadOnly() << std::endl;
    std::cout << response_.get() << std::endl;
    download_data_ct_++;
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

void RequestClient::Get(const std::string &url, const CefRequest::HeaderMap &headers /*= CefRequest::HeaderMap()*/) {
    CefRefPtr<CefRequest> req = CefRequest::Create();
    req->SetURL(url);
    req->SetMethod("GET");
    req->SetHeaderMap(headers);

    //Request(req);
}

void RequestClient::Post(const std::string &url, const CefRefPtr<CefPostData> data,
                         const CefRequest::HeaderMap &headers /*= CefRequest::HeaderMap()*/) {
    CefRefPtr<CefRequest> req = CefRequest::Create();
    req->SetURL(url);
    req->SetMethod("POST");
    req->SetHeaderMap(headers);
    req->SetPostData(data);

    //Request(req);
}

