#ifndef XALIBBASE_H
#define XALIBBASE_H

#include <string>
#include <cstring>
#include <map>
#include <vector>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <fstream>
#include <stdexcept>
#include <new>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <time.h>
#include <assert.h>
#include <thread>
#include <future>
#include <unistd.h>
#include <memory>
#include <random>
#include <iomanip>

#ifdef _WIN32
	#include <winsock2.h>
    #include <windows.h>
#endif

#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>

#include <libxslt/xsltInternals.h>
#include <libxslt/transform.h>
#include <libxslt/xsltutils.h>
#include <libexslt/exslt.h>

#include <openssl/sha.h>
#include <openssl/aes.h>
#include <openssl/evp.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <openssl/rand.h>
#include <openssl/conf.h>

using namespace std;

struct XaRequest {

	/*LEGACY*/
	
	string WsXml="";
	string WsXmlData="";
	string WsXmlDataEncoding="";
	string WsXmlDataKey="";
	string WsXmlDataIV="";

	string WsCallerName="";
	string WsCallerKey="";

	string ResponseType="";
	string RedirectLocation="";
	string WsXmlUsername="";
	string WsXmlPassword="";
	string XaSession_ID="";
	string XaSession_KEY="";
	string XaSession_COOKIE="";

	string CalledLayout="";

	string Brand="";
	string Device="";

	bool FlowCheck=true;
	/*LEGACY END*/
	
	//CARATTERISTICHE DEL WebService
	//string WsReqType="";
	//string WsData="";
	//string WsEncoding="";
	//string WsEncryption="";
	//string WsResType="";

	//CARATTERISTICHE DELLA CHIAMATA
	//string WsXmlUsername="";
	//string WsXmlPassword="";
	//string WsConsumerId="";
	//string WsConsumerName="";
	//string WsConsumerKey="";
	
	//string WsTokenId="";
	string Token="";
	int XaUser_ID=0;
	int XaWsSession_ID;

	//string CalledAction="";
	string CalledObject="";
	string CalledEvent="";

	string HeadersString="";
	string HeadersStringCustom="";


	string Language="";

	string ClientIpAddress="";
	string ServerIpAddress="";

	//STATO DELLA CHIAMATA
	//int RequestStatus=1;
	//string RequestErrorCode="";
	//string RequestErrorMessage="";
};

struct XaResponse {

	/*LEGACY*/
	string Object;
	string Event;
	string Headers;
	/*LEGACY END*/
	
	string Content;
	string ResponseType;
};

typedef map<string, string> XaSettings;
	
#ifdef _WIN32
    template < typename T > std::string to_string( const T& n ) {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
#else
#endif

class XaLibBase {

    private:

    protected:

		typedef map<int, map<string,string> > DbResMap;

		string FromIntToString(int IntValue);
		int FromStringToInt(const string& StringValue);
		unsigned int FromHexStringToUnsignedInt(string StringValue);

		string FromFloatToString(float FloatValue);
		float FromStringToFloat(string StringValue);

		string FromDoubleToString(double DoubleValue);
		double FromStringToDouble(string StringValue);

		string FromCharToString(char CharValue);
		string FromCharArrayToString(char CharValue[]);
		char* FromStringToCharArray(string StringValue);
		string FromStringToHex(const string& StringValue,int CapitalCase);
		int FromCharToInt(char CharValue);

		void SendHtmlHeaders();

    public:

		XaLibBase();
		virtual ~XaLibBase();
};
#endif
