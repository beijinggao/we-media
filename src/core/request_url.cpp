//
// Created by gaodong on 2018/8/28.
//

#include "request_url.h"
#include "include/cef_request.h"
#include "request_client.h"

void RequestUrl::parseUrl(std::string url) {

    printf("%s", url.c_str());


    // Set up the CefRequest object.
    CefRefPtr<CefRequest> request = CefRequest::Create();
    // Populate |request| as shown above...
    request->SetURL(url);
    request->SetMethod("GET");

    // Create the client instance.
    CefRefPtr<RequestClient> client = new RequestClient();

    // Start the request. MyRequestClient callbacks will be executed asynchronously.
    CefRefPtr<CefURLRequest> url_request = CefURLRequest::Create(request, client.get(), NULL);
    // To cancel the request: url_request->Cancel();


/*
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
    request->SetPostData(postData);*/

}
