//
// Created by gaodong on 2018/8/28.
//

#include "request_url.h"
#include "include/cef_request.h"
#include "include/internal/cef_ptr.h"

void RequestUrl::parseUrl(std::string url) {
    // Create a CefRequest object.
    CefRefPtr<CefRequest> request = CefRequest::Create();

    // Set the request URL.
    request->SetURL(url);

    // Set the request method. Supported methods include GET, POST, HEAD, DELETE and PUT.
    request->SetMethod("POST");

    // Optionally specify custom headers.
    CefRequest::HeaderMap headerMap;
    headerMap.insert(std::make_pair("X-My-Header","My Header Value"));
    request->SetHeaderMap(headerMap);

    // Optionally specify upload content.
    // The default “Content-Type” header value is "application/x-www-form-urlencoded".
    // Set “Content-Type” via the HeaderMap if a different value is desired.
    const std::string &upload_data = "arg1 = val1 & arg2 = val2";
    CefRefPtr<CefPostData> postData = CefPostData::Create();
    CefRefPtr<CefPostDataElement> element = CefPostDataElement::Create();
    element->SetToBytes(upload_data.size(), upload_data.c_str());
    postData->AddElement(element);
    request->SetPostData(postData);

}
