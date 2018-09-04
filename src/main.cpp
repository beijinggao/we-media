//
// Created by gaodong on 2018/8/28.
//

#include <iostream>
#include <src/core/request_url.h>

int main(int argc, char *argv[]) {
    std::cout << "Hello, World!" << std::endl;
    RequestUrl requestUrl;
    //requestUrl.parseUrl("wwww.baidu.com");
    requestUrl.Execute();

    return 0;
}
