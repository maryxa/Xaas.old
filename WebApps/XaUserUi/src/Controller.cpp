#include <Controller.h>

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
//#include <XaOuType.h>
//#include <XaOu.h>
#include <XaUserLoginUi.h>
#include <XaOuTypeUi.h>
#include <XaOuUi.h>

#include <XaPages.h>

//#include <XaAddress.h>
//#include <XaLabel.h>
//#include <XaLanguage.h>
//#include <XaDomain.h>
//#include <XaCurrency.h>
//#include <XaUserRole.h>
//#include <XaUserProfile.h>
//#include <XaLibRbGpIo.h>
//#include <XaLibWs.h>

int main (void) {

	string ConfigurationFile {"../config/XaUserUi.xml"};

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
		Dispatch();

	} catch (int e) {

		XaLibError Error;
		string ErrorDesc=Error.GetError(e);

		SendHtmlHeaders();
		cout<<FromIntToString(e) +" :: "+ErrorDesc<<endl;

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

void Controller::Dispatch () {

	LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Dispatching Event");

	SESSION.Token=HTTP.GetSessionId();	

	LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Token got from Session -> "+ SESSION.Token);

	REQUEST.CalledObject=HTTP.GetHttpParam("obj");
	REQUEST.CalledEvent=HTTP.GetHttpParam("evt");

	/*CHANGE WITH PROFILER*/
	/*CASE LOGGED IN*/
	if (REQUEST.CalledObject=="XaUserLoginUi" && REQUEST.CalledEvent=="Login") {

	} else if (REQUEST.CalledObject=="XaUserLoginUi" && REQUEST.CalledEvent=="LogoutFrm") {

	} else if (SESSION.Token!="") {

		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Token is Valid");

		if (REQUEST.CalledObject=="NoHttpParam" || REQUEST.CalledEvent=="NoHttpParam") {

			REQUEST.CalledObject=SETTINGS["DefaultObject"];
			REQUEST.CalledEvent=SETTINGS["DefaultEvent"];
		}

	/*CASE NOT LOGGED IN*/
	} else {

		REQUEST.CalledObject="XaUserLoginUi";
		REQUEST.CalledEvent="LoginFrm";

		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Default Object -> "+SETTINGS["DefaultObject"]);
	}

	ExecuteEvent();
	ManageSession();
	SendResponse();

		//PROFILA COL BACK END

//		REQUEST.HeadersString.append("&username="+Ws.GetUsername()+"&password="+Ws.GetPassword());

//		RESPONSE.ResponseType=Ws.GetResType();

//		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Requested Object -> "+Ws.GetObject());
//		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Requested Event -> "+Ws.GetEvent());

		//SET RESPONSE TYPE

		//PROFILARE
//		this->ExecuteWs(Ws);
//		this->SendResponse();

};

void Controller::ExecuteEvent() {

	if(REQUEST.CalledObject=="XaUserLoginUi") {

		unique_ptr<XaUserLoginUi> UserLoginUi (new XaUserLoginUi());
		UserLoginUi->Execute();

	} else if(REQUEST.CalledObject=="XaOuTypeUi") {

		unique_ptr<XaOuTypeUi> OuTypeUi (new XaOuTypeUi());
		OuTypeUi->Execute();

	} else if(REQUEST.CalledObject=="XaOuUi") {

		unique_ptr<XaOuUi> OuUi (new XaOuUi());
		OuUi->Execute();

	} else if(REQUEST.CalledObject=="XaPages") {

		unique_ptr<XaPages> Pages (new XaPages());
		Pages->Execute();

	} else {

		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Called Object Doesn't Exist -> "+REQUEST.CalledObject);
		throw 611;
	}

	//SendResponse();
};

Controller::~Controller(){
};