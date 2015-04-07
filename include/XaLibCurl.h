#ifndef XALIBCURL_H
#define XALIBCURL_H

#include <cstring>
#include <string>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <new>
#include <vector>
#include <map>

#include <curl/curl.h>

using namespace std;

class XaLibCurl {

	private:

	
	protected:


	public:

		XaLibCurl();
		~XaLibCurl();

		string content;

		typedef size_t(*CURL_WRITEFUNCTION_PTR)(void*, size_t, size_t, void*);

		static size_t handle(char * data, size_t size, size_t nmemb, void * p);
    	size_t handle_impl(char * data, size_t size, size_t nmemb);

    	string GetCurlResponse();

};

#endif
