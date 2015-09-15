#include <XaLibControllerBackEnd.h>

XaLibControllerBackEnd::XaLibControllerBackEnd() {
};

void XaLibControllerBackEnd::OnStart(const string& ConfFile) {

	try {

		LoadXmlConfFile(ConfFile);
		StartLog();

		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"########################### STARTING ACTION LOG ############################");

		StartDb();
		StartHttp();

		GetServerInfo();
	//	GetClientInfo();

		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Request IP -> "+REQUEST.ClientIpAddress);
		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Read HttpString -> " + REQUEST.HeadersString);
		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Request Language -> "+REQUEST.Language);
		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Request Device -> "+REQUEST.Device);

		//RESPONSE.ResponseType=REQUEST.ResponseType;

	} catch (int e) {

		throw;
	}
};


/*
void XaLibController::GetClientInfo(){

	REQUEST.ClientIpAddress=HTTP.GetClientIpAddress();

	//LOG.SetIpAddress(REQUEST.ClientIpAddress);

	string Language=HTTP.GetHttpParam("l");

    if (Language=="NoHttpParam"){

		REQUEST.Language=SETTINGS["DefaultLanguage"];

    } else {

		REQUEST.Language=Language;
	}

	string Device=HTTP.GetHttpParam("d");

    if (Device=="NoHttpParam"){

		REQUEST.Device=SETTINGS["DefaultDevice"];

    } else {

		REQUEST.Device=Device;
	}

};*/

int XaLibControllerBackEnd::ProfileCalledObject(const string& CalledObject,const string& CalledEvent){

	int ReturnStatus=0;

	XaUserProfile UserProfile;

	if (UserProfile.EventIsFree(CalledObject,CalledEvent)==1){

		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Granted Access FREE -> Object:="+CalledObject+" :: Event:="+CalledEvent);
		ReturnStatus=1;

	} else {

		if(UserProfile.EventProfile(CalledObject,CalledEvent)==1){

			LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Granted Access -> Object:="+CalledObject+" :: Event:="+CalledEvent);
			ReturnStatus=1;

		} else {

			LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"REFUSED Access -> Object:="+CalledObject+" :: Event:="+CalledEvent);
		}
	}

	return ReturnStatus;
};

void XaLibControllerBackEnd::SendResponse(){

		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"RESPONSE="+RESPONSE.Content);

		SendHeaders(RESPONSE.ResponseType);
		cout<<"<WsData><Token>"+REQUEST.Token+"</Token>"+RESPONSE.Content+"</WsData>"<<endl;
};
/*
void XaLibControllerBackEnd::SendLocationHeaders(string Location){

	cout<<"Location: ?"+Location<<endl;
	cout<< "Content-Type: text/html; charset=utf-8\n\n";
};
*/


XaLibControllerBackEnd::~XaLibControllerBackEnd() {
};