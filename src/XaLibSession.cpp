#include <XaLibSession.h>
#include <XaLibCrypto.h>

/*
	string SessionId =SessionData[0];
	string SessionKey=SessionData[1];
	string SessionCookie=SessionData[2];
 * 
 *  SessionCheck Values:
 *	0 = Not Valid Session
 *  1 = Valid New Session
 *	2 = Old Valid Session
 *	
 */

XaLibSession::XaLibSession(){
};

int XaLibSession::ManageSession(const string& SessionId){

	int SessionCheck=0;

	//NEW SESSION
    if (SessionId=="") {

		if(this->SessionStart()==1){

			SessionCheck=1;
		}

	//OLD SESSION
    } else if (SessionId!="") {

        int SessionValidationStatus=this->SessionValidate(SessionId);

		//ANONYMOUS USER
		if (SessionValidationStatus==-1){

			SessionCheck= 2;

		//LOGGED USER
        } else if (SessionValidationStatus==1) {

			SessionCheck= 2;
	
		//VALIDATION ERROR
        } else {

			LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"SessionId is NOT valid -> "+SessionId);
			SessionCheck= 0;
		}

    } else {
		
		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"SessionId Is NOT Valid Is NOT A String");
		SessionCheck= 0;
	}

	return SessionCheck;
};

int XaLibSession::SessionStart() {

	LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Session -> New Session Is starting");

	int SessionStatus=0;
	int SessionIdStatus=this->GenerateSessionId();

	if (SessionIdStatus==1) {

		XaLibSql LibSql;
		LibSql.LockTable(DB_SESSION,"XaSession");
		DbResMap DbRes=LibSql.FreeQuery(DB_SESSION,"SELECT id FROM XaSession WHERE SessionID=\""+REQUEST.XaSession_ID+"\"");

		//VERIFING DOES NOT EXIST IN THE DATABASE
        if (DbRes.size()!=0){

			LibSql.UnlockTable(DB_SESSION);
			LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Session -> Generated SessionId Already Exists");

			//XXXXXXXXX REPROVA LO START

        } else {

			LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Session -> Generated SessionId Is Valid");

			int NextId=this->SetSessionDbEntry(REQUEST.XaSession_ID,REQUEST.XaSession_KEY);
			LibSql.UnlockTable(DB_SESSION);

            if (NextId==0){

				LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Session -> Error Inserting a new SessionID into session table");

            } else {

				LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Session -> Inserted a new SessionID in session table -> " + XaLibBase::FromIntToString(NextId));
				this->GenerateCookie();
				SessionStatus=1;
            }
		}

	} else {
			
		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Session -> Error generating a new SessionID");
	}

	return SessionStatus;
}

int XaLibSession::SessionValidate(const string& SessionId){

	int SessionValidateStatus=0;

	LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Session Validation -> Validation For SessionId -> "+SessionId);

	DbResMap DbRes;
	XaLibSql LibSql;

	vector<string> ReturnedFields {"XaUser_ID","SessionID","SessionKey"};
	vector<string> WhereFields {"SessionID"};
	vector<string> WhereValues {SessionId};

	DbRes=LibSql.Select(DB_SESSION,"XaSession",ReturnedFields,WhereFields,WhereValues);

	if (DbRes.size()==1){

		REQUEST.XaSession_ID=DbRes[0]["SessionID"];
		REQUEST.XaSession_KEY=DbRes[0]["SessionKey"];

		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Session Validation -> SessionId Exists And Is Unique In XaSession");

		if (DbRes[0]["XaUser_ID"]=="") {

			//ANONYMOUS USER
			REQUEST.XaUser_ID=-1;
			LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Session Validation -> SessionId Valid For Anonymous User");

			return -1;

		} else {

			//LOGGED USER
			REQUEST.XaUser_ID=FromStringToInt(DbRes[0]["XaUser_ID"]);
			LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Session Validation -> SessionId Valid For User Id -> " + DbRes[0]["XaUser_ID"]);

			return 1;
		}

	} else {

		//REMOVE CLIENT COOKIE BECAUSE IS NOT VALID
		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"XXXXXXXXXXXXXXXX");

		cout<<this->RemoveCookie()<<endl;
		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Session Validation ->  SessionId Does Not Exist Or Is Not Unique In XaSession");
		return 0;
	}
}

string XaLibSession::SessionDestroy() {

	string Cookie=this->RemoveCookie();
	return Cookie;
};

int XaLibSession::GenerateSessionId(){

	int SessionIdStatus=0;

	mt19937_64 generator (chrono::system_clock::now().time_since_epoch().count());
	string MtSring=to_string(generator());


	LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Session -> Generated Mersenne Key ->"+ MtSring);

	string SessionString=MtSring+REQUEST.ClientIpAddress;

	LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Session -> Generated Browser Signature ->"+ SessionString);

	XaLibCrypto LibCrypto;
	string SessionId=LibCrypto.GetSha1(SessionString);

	LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Session -> Generated SessionId ->"+ SessionId);
	
	if (SessionId.size()==XaLibBase::FromStringToInt(SETTINGS["SessionIdLength"])){
		
		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Session -> SessionId Length Correct");

		REQUEST.XaSession_ID=SessionId;
		REQUEST.XaSession_KEY=MtSring;
		
		SessionIdStatus=1;
	
	} else {

		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Session -> SessionId Length Not Correct");
    }

	return SessionIdStatus;
};

void XaLibSession::GenerateCookie(){

	string cookie1="Set-Cookie:XaSessionId=";
	string cookie2=";path=/;HttpOnly;";
	string cookie= cookie1+REQUEST.XaSession_ID+cookie2;

	LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Session -> Generated Cookie -> " +cookie);
	REQUEST.XaSession_COOKIE=cookie;

};

string XaLibSession::RemoveCookie() {

	string cookie1="Set-Cookie:XaSessionId=deleted;";

	string cookie2="path=/;";
	string cookie3="expires=Thu, 01 Jan 1970 00:00:00 GMT;";

	string cookie= cookie1+cookie2+cookie3;

	LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Session -> Generated Remove Cookie -> " +cookie);

return cookie;
};

int XaLibSession::SetSessionDbEntry(const string &SessionId,const string &SessionKey) const{

    XaLibTime LibTime;
    string now=LibTime.GetDateTimeMySql();
            
	vector<string> VectorFields {"SessionID","SessionKey","creation_time"};
	vector<string> VectorValues{SessionId,SessionKey,now};

	XaLibSql LibSql;	
	int NextId=LibSql.Insert(DB_SESSION,"XaSession",VectorFields,VectorValues);

return NextId;
};

int XaLibSession::SetParameter(const string& SessionId, string ParamName, string ParamValue) {

	//controllare la dimensione param value e paramname 2048

	unique_ptr<XaLibSql> LibSql (new XaLibSql());

	DbResMap DbResCheckParam=LibSql->Select(DB_SESSION,"XaSessionData",{"param_value"},{"XaSession_ID","param_name"},{SessionId,ParamName});

	if (DbResCheckParam.size()!=0) {

		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Session Parameter Already Exists -> " +ParamName);

		vector<string> VectorFields {"param_value"}, VectorValues {ParamValue}, WhereFields{"XaSession_ID","param_name"}, WhereValues {SessionId,ParamName};

		int UpdatedId=LibSql->Update(DB_SESSION,"XaSessionData", VectorFields, VectorValues, WhereFields, WhereValues);

		if (UpdatedId!=0) {

			LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Session Parameter -> " + ParamName +" Updated -> " +ParamValue);
			return 1;
			
		} else {
			
			LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Session Parameter -> " + ParamName +" Update Error-> " +ParamValue);
			return 0;
		}
		
		VectorFields.clear();VectorValues.clear();WhereFields.clear();WhereValues.clear();
		
	} else {

		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Session Parameter Is New -> " +ParamName);
		
		vector<string> VectorFields {"XaSession_ID","param_name","param_value"}, VectorValues {SessionId,ParamName,ParamValue};

		int InsertedId=LibSql->Insert(DB_SESSION,"XaSessionData", VectorFields, VectorValues);

		if (InsertedId!=0) {

			LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Session Parameter -> " + ParamName +" Inserted Value -> " +ParamValue);
			return 1;

		} else {
			
			LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Session Parameter -> " + ParamName +" Insert Error-> " +ParamValue);
			return 0;
		}
	}
};

string XaLibSession::GetParameter(const string& SessionId, string ParamName) {

	unique_ptr<XaLibSql> LibSql (new XaLibSql());
	string QryParam="SELECT param_value FROM XaSessionData WHERE XaSession_ID='"+SessionId+"' AND param_name='"+ParamName+"'";

	DbResMap DbResParam=LibSql->FreeQuery(DB_SESSION,QryParam);

	if (DbResParam.size()==1) {

		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Session Parameter Loaded -> " + ParamName +" :: " +DbResParam[0]["param_value"]);
		return DbResParam[0]["param_value"];

	} else {

		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Session Parameter Doesn't exist-> " + ParamName);
		return "NoSessionParam";
	}
};

XaLibSession::~XaLibSession(){
};