#include <cstring>
#include <string>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <new>
#include <map>

#include <curl/curl.h>

#include <XaLibCurl.h>

using namespace std;

XaLibCurl::XaLibCurl() {

};

size_t XaLibCurl::handle(char * data, size_t size, size_t nmemb, void * p) {

    return static_cast<XaLibCurl*>(p)->handle_impl(data, size, nmemb);
}

size_t XaLibCurl::handle_impl(char* data, size_t size, size_t nmemb) {

	content.append(data, size * nmemb);

    return size * nmemb;
}

string XaLibCurl::GetCurlResponse(){
	return content;
}

XaLibCurl::~XaLibCurl() {
};
