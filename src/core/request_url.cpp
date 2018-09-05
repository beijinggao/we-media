//
// Created by gaodong on 2018/8/28.
//

#include "request_url.h"

void RequestUrl::parseUrl(std::string url) {
    RequestClient::RequestCompleteCallback callback;

    CefRefPtr<RequestClient> client = new RequestClient(callback);
    client->RunTest();

    // Set up the CefRequest object.
    /*CefRefPtr<CefRequest> request = CefRequest::Create();
    // Populate |request| as shown above...
    request->SetURL("http://www.baidu.com");
    request->SetMethod("GET");

    // Optionally specify custom headers.
    CefRequest::HeaderMap headerMap;
    headerMap.insert({"User-Agent","Mozilla/5.0 (Macintosh; Intel Mac OS X 10_13_6) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/68.0.3440.106 Safari/537.36"});
    request->SetHeaderMap(headerMap);

    std::cout << "************************" << std::endl;
    std::cout << url << std::endl;
    CefString requestUrl = request->GetURL();
    std::cout << requestUrl.ToString() << std::endl;
    std::cout << requestUrl.ToString().length() << std::endl;
    std::cout << request->GetMethod().ToString() << std::endl;
    std::string aa = !request.get() ? "aaaa" : "bbbb";


    CefRefPtr<CefURLRequest> url_request = CefURLRequest::Create(request, client, NULL);
    std::cout << url_request->GetResponse()->GetStatus() << std::endl;
    std::cout << "************************" << std::endl;*/


    /*RequestClient *client = new RequestClient(new PrintUrlReqCallback);
    std::string host("http://www.baidu.com");
    client->Get(host);*/

    // Post() test
    /*CefRefPtr<CefPostData> data = CefPostData::Create();
    CefRefPtr<CefPostDataElement> element = CefPostDataElement::Create();
    const char szData[] = "Hello World!";
    element->SetToBytes(sizeof(szData) - 1, (const void*)szData);
    data->AddElement(element);
    CefRequest::HeaderMap headers;
    headers.insert({"Content-Type", "text/plain"});
    headers.insert({"Accept", "text/plain"});
    (new RequestClient(new PrintUrlReqCallback))->Post("http://www.baidu.com", data, headers);*/


    /*std::cout << aa << std::endl;
    std::cout << !client.get() << std::endl;

    // Start the request. MyRequestClient callbacks will be executed asynchronously.
    CefRefPtr<CefURLRequest> url_request = CefURLRequest::Create(request, client, NULL);
    std::cout << url_request->GetRequest()->GetURL().ToString().length() << std::endl;*/

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
