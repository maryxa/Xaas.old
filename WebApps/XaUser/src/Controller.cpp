#include <Controller.h>
#include <XaLibControllerBackEnd.h>
#include <XaLibError.h>

/*
* General System Post or Get Parameters 
* @param do=action
* @param obj=object
* @param evt=event
* @param lay=layout
* @param l=language
* @param b=brand
* @param d=device type - pc tablet smartphone
*/

/*
&ReqType=xml
&Encoding=B64, no
&Encryption=yes;
&Data=;
&ResType=xml;
&ConsumerId=3;
&token=9879879
*/

/**** APPLICATION ****/
#include <XaOuType.h>
#include <XaOu.h>
#include <XaUserLogin.h>
//#include <XaPages.h>
#include <XaAddressPhone.h>
#include <XaAddressMail.h>
#include <XaAddressGeo.h>
#include <XaAddressPhoneType.h>
#include <XaAddressPhoneCode.h>
#include <XaAddressMailType.h>
#include <XaAddressGeoType.h>

#include <XaAddress.h>
#include <XaLabel.h>
#include <XaLanguage.h>
//#include <XaDomain.h>
#include <XaCurrency.h>
#include <XaUserRole.h>
#include <XaUserProfile.h>
//#include <XaLibRbGpIo.h>
#include <XaLibWs.h>

int main (void) {

	string ConfigurationFile {"../config/XaUser.xml"};

	unique_ptr<FILE, int(*)(FILE*)> fp(fopen(ConfigurationFile.c_str(), "r"), fclose);

	if (fp) {

		Controller ControllerObj(ConfigurationFile.c_str());

	} else {

		cout<< "Content-Type: text/html; charset=utf-8\n\n";
		cout<< "Configuration file doesn't exist -> "+ConfigurationFile<<endl;
	}

	return 0;
};

Controller::Controller(string ConfFile) {

	auto start = chrono::steady_clock::now();

	try {

		OnStart(ConfFile);
		DispatchWs();

	} catch (int e) {

		XaLibError Error;
		string ErrorDesc=Error.GetError(e);

		SendHtmlHeaders();
		//cout<<"ERROR: "+FromIntToString(e) +" :: "+ErrorDesc<<endl;

		cout<<"<WsData><error><number>"+FromIntToString(e)+"</number><description>"+ErrorDesc+"</description></error></WsData>"<<endl;
		
	} catch (...) {

		SendHtmlHeaders();
		cout<<"Generic not handled Error"<<endl;
		

	}

	auto diff = chrono::steady_clock::now() - start;
	string duration=to_string(chrono::duration <double, std::milli> (diff).count());

	LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Action Execution Time In Ms -> "+duration);

	//////VERIFICARE QUESTO CLOSE
	LOG.Close();
};

void Controller::DispatchWs () {

	XaLibWs Ws;
	Ws.Setup();

	REQUEST.CalledObject=Ws.GetObject();
	REQUEST.CalledEvent=Ws.GetEvent();
	SESSION.Token=Ws.GetToken();

	RESPONSE.ResponseType=Ws.GetResType();

	if (REQUEST.CalledObject=="XaUser" || REQUEST.CalledEvent=="Login") {
		/* In Case of Login I do not check the Token validity */
		REQUEST.HeadersString.append("&username="+Ws.GetUsername()+"&password="+Ws.GetPassword());

	} else {
		/* Token Validation */
		SESSION.XaUser_ID=XaLibToken::ValidateToken(SESSION.Token);
	}

	SESSION.ClientIp=Ws.GetClientIp();

	this->ExecuteWs(Ws);
	Ws.AddResponseLog();
	this->SendResponse();
};

void Controller::ExecuteWs(XaLibWs& Ws){

	if(REQUEST.CalledObject=="XaUserLogin") {

		unique_ptr<XaUserLogin> UserLogin (new XaUserLogin());
		UserLogin->Execute();

	} else if(REQUEST.CalledObject=="XaOuType") {

		unique_ptr<XaOuType> OuType (new XaOuType());
		OuType->Execute();

	} else if(REQUEST.CalledObject=="XaAddressPhone") {
                unique_ptr<XaAddressPhone> AddressPhone (new XaAddressPhone());
                AddressPhone->Execute();
        } else if(REQUEST.CalledObject=="XaAddressMail") {
                unique_ptr<XaAddressMail> AddressMail (new XaAddressMail());
                AddressMail->Execute();
        } else if(REQUEST.CalledObject=="XaAddressGeo") {
                unique_ptr<XaAddressGeo> AddressGeo (new XaAddressGeo());
                AddressGeo->Execute();
        } else if(REQUEST.CalledObject=="XaAddressPhoneType") {
                unique_ptr<XaAddressPhoneType> AddressPhoneType (new XaAddressPhoneType());
                AddressPhoneType->Execute();
        } else if(REQUEST.CalledObject=="XaAddressPhoneCode") {
                unique_ptr<XaAddressPhoneCode> AddressPhoneCode (new XaAddressPhoneCode());
                AddressPhoneCode->Execute();
        } else if(REQUEST.CalledObject=="XaAddressMailType") {
                unique_ptr<XaAddressMailType> AddressMailType (new XaAddressMailType());
                AddressMailType->Execute();
        } else if(REQUEST.CalledObject=="XaAddressGeoType") {
                unique_ptr<XaAddressGeoType> AddressGeoType (new XaAddressGeoType());
                AddressGeoType->Execute();
        } else {

		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"WS Called Object Doesn't Exist -> "+REQUEST.CalledObject);
		throw 119;
	}
};

Controller::~Controller(){
};