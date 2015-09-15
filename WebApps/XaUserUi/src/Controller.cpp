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
#include <XaUserUi.h>
//#include <XaPages.h>

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

	//SE C"E" TOKEN MA NON OGGGETTI MANda IN DASHBOARD
	REQUEST.Token=HTTP.GetHttpParam("token");

	//if (REQUEST.Token!="NoHttpParam") {
		
		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Token is empty");

		REQUEST.CalledObject=HTTP.GetHttpParam("obj");
		REQUEST.CalledEvent=HTTP.GetHttpParam("evt");

	//} else {

	//	REQUEST.CalledObject=SETTINGS["DefaultObject"];
	//	REQUEST.CalledEvent=SETTINGS["DefaultEvent"];
			
	//	LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Default Object -> "+SETTINGS["DefaultObject"]);
	//	LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Default Event -> "+SETTINGS["DefaultEvent"]);
	//}

	ExecuteEvent();
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

	if(REQUEST.CalledObject=="XaUserUi") {

		unique_ptr<XaUserUi> UserUi (new XaUserUi());
		UserUi->Execute();

	} /*else if(REQUEST.CalledObject=="XaOuType") {

		unique_ptr<XaOuType> OuType (new XaOuType());
		OuType->Execute();

	} */else {

	}
	//SendResponse();
};
/*
//void Controller::ExecuteCalledObject () {

//	LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Called Object With Event ->"+REQUEST.CalledObject+" :: "+REQUEST.CalledEvent +" :: Ws -> " +REQUEST.WsXml);
/*
	if(REQUEST.CalledObject=="test") {

	} else if(REQUEST.CalledObject=="XaUser") {

		unique_ptr<XaUser> User(new XaUser());

		if (REQUEST.CalledEvent=="XaUserLogout") {

			cout<<SESSION.SessionDestroy()<<endl;
		}

		User->GetResponse();
		SendResponse();

	} else if(REQUEST.CalledObject=="XaOuType") {

		unique_ptr<XaOuType> OuType (new XaOuType());
		OuType->GetResponse();
		SendResponse();

	} else if(REQUEST.CalledObject=="XaOu") {

		unique_ptr<XaOu> Ou (new XaOu());
		Ou->GetResponse();
		SendResponse();

	} else {

		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Called Object Does not exist -> "+REQUEST.CalledObject);

		if (REQUEST.WsData=="yes") {

			RESPONSE.Content="<WsXmlData><error>CalledObjectDoesNotExist</error></WsXmlData>";
			SendResponse();

		} else {

			REQUEST.CalledObject="XaPages";
			REQUEST.CalledEvent="XaInfoPage";
			REQUEST.HeadersStringCustom="&ErrorMessage=ObjectNotFound";
			Dispatch();
		}
	}
	*/
//};

Controller::~Controller(){
};