#include <XaLibCurl.h>

#include <curl/curl.h>


size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream) {
    string data((const char*) ptr, (size_t) size * nmemb);
    *((stringstream*) stream) << data << endl;
    return size * nmemb;
};

XaLibCurl::XaLibCurl() {
curl = curl_easy_init();
	
	
	/*
	 char* curl_call_string=(char *)curl_call_string1.c_str();
    string PostString;
    XaLibCurl* LibCurl=new XaLibCurl();
    CURL *curl;
    CURLcode res;
    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, curl_call_string);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, XaLibCurl::handle);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, LibCurl);
        //curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");
        curl_easy_setopt(curl, CURLOPT_POST, 1);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, PostString.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, PostString.length());

        struct curl_slist *slist = curl_slist_append(NULL, "Content-Type: text/xml; charset=utf-8");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, slist);

        res=curl_easy_perform(curl);

        curl_slist_free_all(slist);
        curl_easy_cleanup(curl);

        FrimmResponse=LibCurl->GetCurlResponse();
        LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Response Frimm Description -> OK");
    } else {
        FrimmResponse="ERRORE CONNESSIONE";
        LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Response Frimm Description -> ERROR");
    }

    return FrimmResponse;
	
	*/
	
	
};


string XaLibCurl::Call(const std::string& url) {
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    /* example.com is redirected, so we tell libcurl to follow redirection */
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1); //Prevent "longjmp causes uninitialized stack frame" bug
    curl_easy_setopt(curl, CURLOPT_ACCEPT_ENCODING, "deflate");
    std::stringstream out;
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &out);
    /* Perform the request, res will get the return code */
    CURLcode res = curl_easy_perform(curl);
    /* Check for errors */
    if (res != CURLE_OK) {
        fprintf(stderr, "curl_easy_perform() failed: %s\n",
                curl_easy_strerror(res));
    }
    return out.str();
}

XaLibCurl::~XaLibCurl() {
 curl_easy_cleanup(curl);
}; 



  //code = curl_easy_setopt(conn, CURLOPT_ERRORBUFFER, errorBuffer);
 
//  code = curl_easy_setopt(conn, CURLOPT_URL, url);
 
  //code = curl_easy_setopt(conn, CURLOPT_FOLLOWLOCATION, 1L);
 
  //code = curl_easy_setopt(conn, CURLOPT_WRITEFUNCTION, writer);
 
  //code = curl_easy_setopt(conn, CURLOPT_WRITEDATA, &buffer);


/*


string XaLibCurl::MakeCall(const string& Url,const int& Ssl) {

		static string content;

	char* curl_call_string=(char *)Url.c_str();
    
	string Response="";
	string PostString;
    //XaLibCurl* LibCurl=new XaLibCurl();
  
	CURL *curl=NULL;
    CURLcode res;

	curl_global_init(CURL_GLOBAL_DEFAULT);
	
    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, curl_call_string);
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writer);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &content);
		
        //curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");
        curl_easy_setopt(curl, CURLOPT_POST, 1);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, PostString.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, PostString.length());

        struct curl_slist *slist = curl_slist_append(NULL, "Content-Type: text/xml; charset=utf-8");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, slist);

        res=curl_easy_perform(curl);
        curl_easy_cleanup(curl);
		
		
		//code = curl_easy_perform(conn);
		//curl_easy_cleanup(conn);
		
        //curl_slist_free_all(slis

        Response=GetCurlResponse();
        LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Response  -> OK");
    } else {
        Response="ERRORE CONNESSIONE";
        LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Response -> ERROR");
    }

    return Response;
};

string XaLibCurl::MakeCall1(const string& Url,const int& Ssl) {

	CURL *curl;
	CURLcode res;

	curl_global_init(CURL_GLOBAL_ALL);
	curl = curl_easy_init();

	if(curl) {
  
    curl_easy_setopt(curl, CURLOPT_URL, "WWW.google.com");
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "name=daniel&project=curl");
 
    res = curl_easy_perform(curl);


    if(res != CURLE_OK)
		fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
 
   
    curl_easy_cleanup(curl);
  }
  curl_global_cleanup();
  return 0;
};

int XaLibCurl::writer(char *data, size_t size, size_t nmemb,std::string *writerData) {
  if (writerData == NULL)
    return 0;
  cout<<data<<endl;
  writerData->append(data, size*nmemb);
 
  return size * nmemb;
}

/*
size_t XaLibCurl::handle(char * data, size_t size, size_t nmemb, string * writerData) {

    //return static_cast<XaLibCurl*>(p)->handle_impl(data, size, nmemb);
	
	//static int writer(char *data, size_t size, size_t nmemb, string *writerData)
//{
  if (writerData == NULL)
    return 0;
 
  writerData->append(data, size*nmemb);
 
  return size * nmemb;
//}
	
}


size_t XaLibCurl::handle_impl(char* data, size_t size, size_t nmemb) {

//	content.append(data, size * nmemb);

  //  return size * nmemb;
}

string XaLibCurl::GetCurlResponse(){

	 LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Response"+content);
	
	return content;
}


XaLibCurl::~XaLibCurl() {
};
*/