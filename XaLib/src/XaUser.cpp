#include <XaUser.h>

XaUser::XaUser(){
};

void XaUser::Dispatcher (const string &CalledEvent) {

	if (CalledEvent=="Login"){

        this->Login();

    } else if (CalledEvent=="Logout"){

		this->Logout();

    } else {

		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Requested Event Does Not Exists -> "+CalledEvent);
		throw 42;
	}

};

/*TEST CASE
 TUTTE LE COMBINAZIONI
 */
void XaUser::Login (){

	string StrUsername=HTTP.GetHttpParam("username");
	string StrPassword=HTTP.GetHttpParam("password");

	if (StrUsername !="" && StrPassword !="") {

		string ShaPassword=XaLibCrypto::GetSha1(StrPassword);

		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"USER Encrypted Password -> "+ShaPassword);
		DbResMap DbRes=XaLibSql::FreeQuery(DB_SESSION,"SELECT id FROM XaUser WHERE username=\""+StrUsername+"\" AND password=\""+ShaPassword+"\" AND status in (0,1)");

		int n=DbRes.size();

		if (n==0){

			LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"USER Does Not Exist Or The Password Is Wrong -> " + StrUsername);
			throw 45;

		} else if (n==1){

			LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"USER Valid With ID ->"+DbRes[0]["id"]);
	
			//controllare se ha gia un token
			
			XaLibToken LibToken;
			
			SESSION.Token=LibToken.CreateToken(FromStringToInt(DbRes[0]["id"]));
			
			LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"USER Valid With ID ->"+DbRes[0]["id"]+"And Token  ->"+RESPONSE.Content);

		} else {

			LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"User Is Not Unique");
			throw 46;
		}

	} else {

		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Username Or Password Is Empty");
		throw 47;
	}

};

void XaUser::Logout (){

	LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Destroying Session -> SessionID::"+REQUEST.XaSession_ID +" AND UserID::"+ XaLibBase::FromIntToString(SESSION.XaUser_ID));

	XaLibSql LibSql;
	LibSql.LockTable(DB_SESSION,"XaSession");

		//DELETE SESSION DATA
		vector<string> VectorWhereSessionDataFields {"XaSession_ID"};
		vector<string> VectorWhereSessionDataValues {REQUEST.XaSession_ID};

		LibSql.Delete(DB_SESSION,"XaSessionData",VectorWhereSessionDataFields,VectorWhereSessionDataValues);

		VectorWhereSessionDataFields.clear();
		VectorWhereSessionDataValues.clear();
				
		//DELETE SESSION
		vector<string> VectorWhereSessionFields {"SessionID","XaUser_ID"};
		vector<string> VectorWhereSessionValues {REQUEST.XaSession_ID,XaLibBase::FromIntToString(SESSION.XaUser_ID)};

		LibSql.Delete(DB_SESSION,"XaSession",VectorWhereSessionFields,VectorWhereSessionValues);
		
		VectorWhereSessionFields.clear();
		VectorWhereSessionValues.clear();

	LibSql.UnlockTable(DB_SESSION);

//	SetLayout("LoginFrm");

//	AddXmlFile("Logout");
//	AddXslFile("Logout");
//
//	xmlDocPtr XmlDomDoc=XaLibDom::DomFromStringAndFile(XmlFiles,XmlStrings,1);
//	xmlDocPtr XslDomDoc=XaLibDom::DomFromStringAndFile(XslFiles,XslStrings,2);

//	AddXslParamCommon();
  //  unique_ptr<XaLibXsl> LibXsl (new XaLibXsl(XmlDomDoc,XslDomDoc,XslParams));

	//RESPONSE.Content=LibXsl->GetXHtml();
};

XaUser::~XaUser(){
};