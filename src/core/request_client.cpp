//
// Created by gaodong on 2018/8/28.
//

#include "request_client.h"


void RequestClient::OnRequestComplete(CefRefPtr<CefURLRequest> request) {

    CEF_REQUIRE_UI_THREAD();
    if (m_callback) {
        m_callback->OnCompletion(request->GetRequestError(), m_data);
    }

    /*CefURLRequest::Status status = request->GetRequestStatus();
    CefURLRequest::ErrorCode error_code = request->GetRequestError();
    CefRefPtr<CefResponse> response = request->GetResponse();

    std::cout << status << std::endl;
    std::cout << error_code << std::endl;

    std::cout << response << std::endl;
    std::cout << upload_total_ << std::endl;
    std::cout << download_total_ << std::endl;*/


}

void RequestClient::OnUploadProgress(CefRefPtr<CefURLRequest> request, int64 current, int64 total) {
    upload_total_ = total;
}

void RequestClient::OnDownloadProgress(CefRefPtr<CefURLRequest> request, int64 current, int64 total) {
    CefRefPtr<CefResponse> response_ = request->GetResponse();

    //EXPECT_TRUE(response_.get());
    //EXPECT_TRUE(response_->IsReadOnly());

    download_total_ = total;

    char szLog[128] = {0};
    printf(szLog, 128, "RequestClient::OnDownloadProgress, current-%lld, total-%lld\r\n", current, total);
    printf("%s",szLog);

}

void RequestClient::OnDownloadData(CefRefPtr<CefURLRequest> request, const void *data, size_t data_length) {
    download_data_ += std::string(static_cast<const char *>(data), data_length);
    m_data += std::string(static_cast<const char *>(data), data_length);
}

bool RequestClient::GetAuthCredentials(bool isProxy,
                                       const CefString &host,
                                       int port,
                                       const CefString &realm,
                                       const CefString &scheme,
                                       CefRefPtr<CefAuthCallback> callback) {
    return false;
};

void RequestClient::Request(CefRefPtr<CefRequest> cef_request) {
    m_urlRequest = CefURLRequest::Create(cef_request, this, NULL);
}

void RequestClient::Get(const std::string &url, const CefRequest::HeaderMap &headers /*= CefRequest::HeaderMap()*/) {
    CefRefPtr<CefRequest> req = CefRequest::Create();
    req->SetURL(url);
    req->SetMethod("GET");
    req->SetHeaderMap(headers);

    Request(req);
}

void RequestClient::Post(const std::string &url, const CefRefPtr<CefPostData> data,
                         const CefRequest::HeaderMap &headers /*= CefRequest::HeaderMap()*/) {
    CefRefPtr<CefRequest> req = CefRequest::Create();
    req->SetURL(url);
    req->SetMethod("POST");
    req->SetHeaderMap(headers);
    req->SetPostData(data);

    Request(req);
}

//
// for test
//
void PrintUrlReqCallback::OnCompletion(CefURLRequest::ErrorCode errorCode, const std::string &data) {
    char szLog[128] = {0};
    printf(szLog, 128, "PrintUrlReqCallback::OnCompletion, errorCode = %d, data.len = %d, data:\r\n",
           errorCode, data.length());
    printf("%s",szLog);
    delete this;
}

