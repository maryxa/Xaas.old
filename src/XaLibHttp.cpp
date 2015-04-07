#include <XaLibHttp.h>

#include <XaLibBase.h>
#include <XaLibLog.h>

#include <XaLibCrypto.h>
#include <XaLibChar.h>

extern XaRequest REQUEST;

XaLibHttp::XaLibHttp(){
};

void XaLibHttp::GetHttpHeaders(){

	if (getenv("HTTP_COOKIE")){
		this->HTTP_COOKIE = getenv("HTTP_COOKIE");
	}

	if (getenv("COMSPEC")){
		this->HTTP_COMSPEC = getenv("COMSPEC");
	}

	if (getenv("REQUEST_METHOD")){
		this->HTTP_REQUEST_METHOD = getenv("REQUEST_METHOD");
	}

	if (getenv("DOCUMENT_ROOT")){
		this->HTTP_DOCUMENT_ROOT = getenv("DOCUMENT_ROOT");
	}

	if (getenv("GATEWAY_INTERFACE")){
		this->HTTP_GATEWAY_INTERFACE = getenv("GATEWAY_INTERFACE");
	}

	if (getenv("HTTP_ACCEPT")){
		this->HTTP_ACCEPT = getenv("HTTP_ACCEPT");
	}

	if (getenv("HTTP_ACCEPT_ENCODING")){
		this->HTTP_ACCEPT_ENCODING = getenv("HTTP_ACCEPT_ENCODING");
	}

	if (getenv("HTTP_ACCEPT_LANGUAGE")){

	this->HTTP_ACCEPT_LANGUAGE = getenv("HTTP_ACCEPT_LANGUAGE");
	}

	if (getenv("HTTP_CONNECTION")){
		this->HTTP_CONNECTION = getenv("HTTP_CONNECTION");
	}

	if (getenv("HTTP_HOST")){
		this->HTTP_HOST = getenv("HTTP_HOST");
	}

	if (getenv("HTTP_USER_AGENT")){
		this->HTTP_USER_AGENT = getenv("HTTP_USER_AGENT");
	}

	if (getenv("PATH")){
		this->HTTP_PATH = getenv("PATH");
	}

	if (getenv("QUERY_STRING")){
		this->HTTP_QUERY_STRING = getenv("QUERY_STRING");
	}

	if (getenv("HTTP_CONTENT_LENGTH")){
		this->HTTP_CONTENT_LENGTH=getenv("HTTP_CONTENT_LENGTH");
	}

    if (getenv("REMOTE_ADDR")){
    	this->HTTP_REMOTE_ADDR = getenv("REMOTE_ADDR");
	}

	if (getenv("REMOTE_PORT")){
		this->HTTP_REMOTE_PORT = getenv("REMOTE_PORT");
	}

	if (getenv("REQUEST_METHOD")){
			this->HTTP_REQUEST_METHOD = getenv("REQUEST_METHOD");
	}

	if (getenv("REQUEST_URI")){
			this->HTTP_REQUEST_URI = getenv("REQUEST_URI");
	}

	if (getenv("SCRIPT_FILENAME")){
		this->HTTP_SCRIPT_FILENAME = getenv("SCRIPT_FILENAME");
	}

	if (getenv("SCRIPT_NAME")){
		this->HTTP_SCRIPT_NAME = getenv("SCRIPT_NAME");
	}

	if (getenv("SERVER_ADDR")){
		this->HTTP_SERVER_ADDR = getenv("SERVER_ADDR");
	}

	if (getenv("SERVER_ADMIN")){
		this->HTTP_SERVER_ADMIN = getenv("SERVER_ADMIN");
	}

	if (getenv("SERVER_NAME")){
		this->HTTP_SERVER_NAME = getenv("SERVER_NAME");
	}

	if (getenv("SERVER_PORT")){
		this->HTTP_SERVER_PORT = getenv("SERVER_PORT");
	}

	if (getenv("SERVER_PROTOCOL")){
		this->HTTP_SERVER_PROTOCOL = getenv("SERVER_PROTOCOL");
	}

	if (getenv("SERVER_SIGNATURE")){
		this->HTTP_SERVER_SIGNATURE = getenv("SERVER_SIGNATURE");
	}

	if (getenv("SERVER_SOFTWARE")){
		this->HTTP_SERVER_SOFTWARE = getenv("SERVER_SOFTWARE");
	}
	
	if (getenv("HTTP_X_FORWARDED_FOR")){
		this->HTTP_X_FORWARDED_FOR = getenv("HTTP_X_FORWARDED_FOR");
	}
};
/*
string XaLibHttp::__getHeaders(string HttpHeaderName){

	string HttpHeader="NoHttpHeader";

	if(HttpHeaderName=="HTTP_COOKIE"){
		HttpHeader=this->HTTP_COOKIE;
	}
	if(HttpHeaderName=="HTTP_COMSPEC"){
		HttpHeader=this->HTTP_COMSPEC;
	} else if (HttpHeaderName=="HTTP_DOCUMENT_ROOT"){
		HttpHeader=this->HTTP_DOCUMENT_ROOT;
	} else if (HttpHeaderName=="HTTP_GATEWAY_INTERFACE"){
		HttpHeader= this->HTTP_GATEWAY_INTERFACE;
	} else if (HttpHeaderName=="HTTP_ACCEPT"){
		HttpHeader= this->HTTP_ACCEPT;
	} else if (HttpHeaderName=="HTTP_ACCEPT_ENCODING"){
		HttpHeader= this->HTTP_ACCEPT_ENCODING;
	} else if (HttpHeaderName=="HTTP_ACCEPT_LANGUAGE"){
		HttpHeader= this->HTTP_ACCEPT_LANGUAGE;
	} else if (HttpHeaderName=="HTTP_CONNECTION"){
		HttpHeader= this->HTTP_CONNECTION;
	} else if (HttpHeaderName=="HTTP_HOST"){
		HttpHeader= this->HTTP_HOST;
	} else if (HttpHeaderName=="HTTP_USER_AGENT"){
		HttpHeader= this->HTTP_USER_AGENT;
	} else if (HttpHeaderName=="HTTP_PATH"){
		HttpHeader= this->HTTP_PATH;
	} else if (HttpHeaderName=="HTTP_QUERY_STRING"){
		HttpHeader= this->HTTP_QUERY_STRING;
	} else if (HttpHeaderName=="HTTP_CONTENT_LENGTH"){
		return this->HTTP_CONTENT_LENGTH;
	} else if (HttpHeaderName=="HTTP_REMOTE_ADDR"){
		HttpHeader= this->HTTP_REMOTE_ADDR;
	} else if (HttpHeaderName=="HTTP_REMOTE_PORT"){
		HttpHeader= this->HTTP_REMOTE_PORT;
	} else if (HttpHeaderName=="HTTP_REQUEST_METHOD"){
		return this->HTTP_REQUEST_METHOD;
	} else if (HttpHeaderName=="HTTP_REQUEST_URI"){
		HttpHeader= this->HTTP_REQUEST_URI;
	} else if (HttpHeaderName=="HTTP_SCRIPT_FILENAME"){
		HttpHeader= this->HTTP_SCRIPT_FILENAME;
	} else if (HttpHeaderName=="HTTP_SCRIPT_NAME"){
		HttpHeader= this->HTTP_SCRIPT_NAME;
	} else if (HttpHeaderName=="HTTP_SERVER_ADDR"){
		HttpHeader= this->HTTP_SERVER_ADDR;
	} else if (HttpHeaderName=="HTTP_SERVER_ADMIN"){
		HttpHeader= this->HTTP_SERVER_ADMIN;
	} else if (HttpHeaderName=="HTTP_SERVER_NAME"){
		HttpHeader= this->HTTP_SERVER_NAME;
	} else if (HttpHeaderName=="HTTP_SERVER_PORT"){
		HttpHeader= this->HTTP_SERVER_PORT;
	} else if (HttpHeaderName=="HTTP_SERVER_PROTOCOL"){
		HttpHeader= this->HTTP_SERVER_PROTOCOL;
	} else if (HttpHeaderName=="HTTP_SERVER_SIGNATURE"){
		HttpHeader= this->HTTP_SERVER_SIGNATURE;
	} else if (HttpHeaderName=="HTTP_SERVER_SOFTWARE"){
		HttpHeader= this->HTTP_SERVER_SOFTWARE;
	}

	return HttpHeader;
};
*/
string XaLibHttp::GetHttpHeadersString(){

	this->GetHttpHeaders();

	string HttpParamValue;

    //READING GET
	string HttpQueryString=this->HTTP_QUERY_STRING;

	//READING POST
	string HttpPostString;

	//cin >> HttpPostString;
	getline(cin, HttpPostString);

	while (true) {
		string HttpPostStringTemp;

		getline(cin, HttpPostStringTemp);

		if (HttpPostStringTemp.empty()) {
			break;

        } else {
			HttpPostString.append(HttpPostStringTemp);
		}
    }

	string HttpString;

	if (HttpPostString!=""){

		HttpString.append("&");
		HttpString.append(HttpPostString);

	}

	if (HttpQueryString!=""){
		
		HttpString.append("&");
		HttpString.append(HttpQueryString);
	}

	//cout<<HttpString<<endl;
	//HttpString.append("&");

	LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Read HttpString -> " +HttpString);

	HttpString.erase(remove(HttpString.begin(), HttpString.end(), ' '), HttpString.end());
	HttpString.erase(remove(HttpString.begin(), HttpString.end(), '\n'), HttpString.end());
	HttpString.erase(remove(HttpString.begin(), HttpString.end(), '\r'), HttpString.end());
	HttpString.erase(remove(HttpString.begin(), HttpString.end(), '\0'), HttpString.end());
	
	return HttpString;
};

string XaLibHttp::GetHttpParam(string HttpParamName){

	string HttpParamValue;
	//string HttpQueryString=REQUEST.HeadersString;

	//CALCOLO LA LUNGHEZZA DELLA QUERY STRING
	unsigned HttpQueryStringSize=REQUEST.HeadersString.size();

	//CALCOLO LA POSIZIONE DEL PARAMETRO NELLA STRINGA
	unsigned HttpParamNamePosition =REQUEST.HeadersString.find("&"+HttpParamName+"=");

		//IL PARAMETRO NON ESISTE
		if (HttpParamNamePosition>HttpQueryStringSize){

				HttpParamValue="NoHttpParam";

				LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"NoHttpParam -> " +HttpParamName);

				return HttpParamValue;

		} else {

			//CALCOLO LA LUNGHEZZA DEL NOME DEL PARAMETRO
			unsigned HttpParamNameSize=HttpParamName.size();

			//CALCOLO LA POSIZIONE FINALE DEL PARAMETRO NELLA STRINGA SOMMANDO  per il segno = e il segno &
			unsigned HttpParamNamePositionEnd=HttpParamNamePosition+HttpParamNameSize+2;

			//CERCO IL SUCCESSICO &
			unsigned NextAnd=REQUEST.HeadersString.find("&",HttpParamNamePositionEnd);

				//SE NON CI SONO ALTRI &
				if (NextAnd>HttpQueryStringSize){

					//NextAnd==HttpQueryString.size();
					HttpParamValue = REQUEST.HeadersString.substr(HttpParamNamePositionEnd);

				} else {

					HttpParamValue = REQUEST.HeadersString.substr(HttpParamNamePositionEnd,NextAnd-HttpParamNamePositionEnd);
				}

				//unsigned a=HttpParamValue.size();

				string HttpParamValueDecoded;
				
					if (HttpParamValue.size()==0){
					
						HttpParamValueDecoded=HttpParamValue;

					} else {

						XaLibChar* LibChar=new XaLibChar();
						HttpParamValueDecoded=LibChar->UrlDecode(HttpParamValue);
						delete (LibChar);
					}

				if (HttpParamName!="password"){

					LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"HttpParam -> " +HttpParamName+" := "+HttpParamValueDecoded);
				}

				return HttpParamValueDecoded;
		}
};

vector<string> XaLibHttp::GetHttpParamArray(string HttpParamName){

	vector<string> HttpParamValueArray;

	string HttpParamValue;
	//string HttpQueryString=REQUEST.HeadersString;

	//CALCOLO LA LUNGHEZZA DELLA QUERY STRING
	unsigned HttpQueryStringSize=REQUEST.HeadersString.size();

	//CALCOLO LA PRIMA POSIZIONE DEL PARAMETRO NELLA STRINGA
	unsigned HttpParamNamePosition =REQUEST.HeadersString.find("&"+HttpParamName+"=");

		//IL PARAMETRO NON ESISTE
		if (HttpParamNamePosition>HttpQueryStringSize){

				HttpParamValue="NoHttpParam";

				LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"NoHttpParamArray -> " +HttpParamName);

				HttpParamValueArray.push_back("NoHttpParam");

		//ESISTE ALMENO UNA OCCORRENZA
		} else if (HttpParamNamePosition<HttpQueryStringSize){

			//CALCOLO LA LUNGHEZZA DEL NOME DEL PARAMETRO
			unsigned HttpParamNameSize=HttpParamName.size();
	
			while(HttpParamNamePosition<HttpQueryStringSize){

				//CALCOLO LA POSIZIONE FINALE DEL PARAMETRO NELLA STRINGA SOMMANDO 2 SEGNO = E SEGNO &
				unsigned HttpParamNamePositionEnd=HttpParamNamePosition+HttpParamNameSize+2;

				//CERCO IL SUCCESSICO &
				unsigned NextAnd=REQUEST.HeadersString.find("&",HttpParamNamePositionEnd);

					//SE NON CI SONO ALTRI &
					if (NextAnd>HttpQueryStringSize){

						//NextAnd==HttpQueryString.size();
						HttpParamValue = REQUEST.HeadersString.substr(HttpParamNamePositionEnd);

					} else {

						HttpParamValue = REQUEST.HeadersString.substr(HttpParamNamePositionEnd,NextAnd-HttpParamNamePositionEnd);
					}

					string HttpParamValueDecoded;
				
					if (HttpParamValue.size()==0){
					
						HttpParamValueDecoded=HttpParamValue;

					} else {
							
						XaLibChar* LibChar=new XaLibChar();
						HttpParamValueDecoded=LibChar->UrlDecode(HttpParamValue);
						delete (LibChar);
					}

					HttpParamValueArray.push_back(HttpParamValueDecoded);

					if (HttpParamName!="password"){

						LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"HttpParamArray -> " +HttpParamName+" := "+HttpParamValueDecoded);
					}

					HttpParamNamePosition =REQUEST.HeadersString.find("&"+HttpParamName+"=",NextAnd);
			}
	}

	return HttpParamValueArray;	
}

//PER ESEMPIO DATA
vector<string> XaLibHttp::GetHttpParamStruct(string HttpParamName,string StructType){

	vector<string> HttpParamValueArray;

	if (StructType=="input-date" ) {	// year+month+day
		string year =this->GetHttpParam(HttpParamName+"_year");
		string month=this->GetHttpParam(HttpParamName+"_month");
		string day  =this->GetHttpParam(HttpParamName+"_day");
		if (year!="NoHttpParam" && month!="NoHttpParam" && day!="NoHttpParam") {
			HttpParamValueArray.push_back(year);
			HttpParamValueArray.push_back(month);
			HttpParamValueArray.push_back(day);

			LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"HttpParamStruct -> " +HttpParamName+" complete");

		} else 

		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"HttpParamStruct -> " +HttpParamName+" incomplete");

	} else {
		// StructType not defined
		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"HttpParamStruct -> " +HttpParamName+" -> StructType "+StructType+" non defined");

	}

	return HttpParamValueArray;	
};

string XaLibHttp::GetSessionId(){

	string HttpCookieData=this->HTTP_COOKIE;

	unsigned ParamEnd=HttpCookieData.find("XaSessionId=");

	if (ParamEnd!=-1){

		string SessionId = HttpCookieData.substr(ParamEnd+12,XaLibBase::FromStringToInt(SETTINGS["SessionIdLength"]));
		return SessionId;

	} else {
		
		return "";
	}
};

string XaLibHttp::GetIpAddress (){

	string IpAddress="";
	
	//LOAD BALANCING CASE
	if (this->HTTP_X_FORWARDED_FOR!="") {
	
		IpAddress=this->HTTP_X_FORWARDED_FOR;

	} else {

		IpAddress=this->HTTP_REMOTE_ADDR;
	
	}

	return IpAddress;
};

XaLibHttp::~XaLibHttp(){
};