#include <XaAddress.h>
#include <XaLibAction.h>

/*
XaAddress::XaAddress(int C_XaUser_ID,string C_SESSION_ID, ParamsMap C_Request,XaLibHttp* LibHttp,string HeadersString,XaLibLog* LibLog,ofstream* MyLogFile,XaLibDb* LibDbSession,XaLibDb* LibDbRead,XaLibDb* LibDbWrite){

	XaLibAction::SetActionEnvironment(C_XaUser_ID,C_SESSION_ID,C_Request,LibHttp,HeadersString,LibLog,MyLogFile,LibDbSession,LibDbRead,LibDbWrite,WsXml);
    XaLibAction::SetActionVariables();

};
*/

XaAddress::XaAddress() {
};

void XaAddress::Dispatcher(string CalledEvent) {
	
	if (CalledEvent=="XaAddressGeoAddFrm"){

        this->XaAddressGeoAddFrm();

    } else if (CalledEvent=="XaAddressGeoAdd"){

        this->XaAddressGeoAdd();

    } else if (CalledEvent=="XaAddressGeoModFrm"){

        this->XaAddressGeoModFrm();

    } else if (CalledEvent=="XaAddressGeoList"){

        this->XaAddressGeoList();

    } else if (CalledEvent=="XaAddressGeoDel"){

        this->XaAddressGeoDel();

    } else if (CalledEvent=="XaAddressPhoneAddFrm"){

        this->XaAddressPhoneAddFrm();

    } else if (CalledEvent=="XaAddressPhoneAdd"){

        this->XaAddressPhoneAdd();

    } else if (CalledEvent=="XaAddressPhoneModFrm"){

        this->XaAddressPhoneModFrm();

    } else if (CalledEvent=="XaAddressPhoneDel"){

        this->XaAddressPhoneDel();

    } else if (CalledEvent=="XaAddressPhoneList"){

        this->XaAddressPhoneList();

    } else if (CalledEvent=="XaAddressMailAddFrm"){

        this->XaAddressMailAddFrm();

    } else if (CalledEvent=="XaAddressMailAdd"){

        this->XaAddressMailAdd();

    } else if (CalledEvent=="XaAddressMailModFrm"){

		this->XaAddressMailModFrm();

    } else if (CalledEvent=="XaAddressMailDel"){

        this->XaAddressMailDel();

    } else if (CalledEvent=="XaAddressMailList"){

        this->XaAddressMailList();

    } else {

		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"The requested event does not exist -> " + CalledEvent);
	}

};
/*
void XaAddress::XaAddressAddFrm(){
    XaLibAction::SetLayout("Standard");

	string XmlPage="XaAddressAddFrm";
    XaLibAction::AddXmlPath(XmlPage);

    string XslPage="XaAddressAddFrm";
    XaLibAction::AddXslPath(XslPage);

    XaLibDom* LibDom=new XaLibDom();
    xmlDocPtr XmlDomDoc=LibDom->DomFromStringAndFile(XmlFilePaths,XmlStrings,1);
	xmlDocPtr XslDomDoc=LibDom->DomFromStringAndFile(XslFilePaths,XslStrings,2);

	delete(LibDom);

	string XaUser_ID=HTTP.GetHttpParam("XaUser_ID");
	
    const int MAXITEMS = 2;
    string XslParams[MAXITEMS] = {"XaUser_ID",XaUser_ID};
    XaLibXsl *LibXsl=new XaLibXsl(XmlDomDoc,XslDomDoc,XslParams,MAXITEMS);
    RESPONSE.Content=LibXsl->GetXHtml();
	delete(LibXsl);

};
*/
void XaAddress::XaAddressGeoAddFrm(){

	string XaDomainType=HTTP.GetHttpParam("XaDomainType");
	
    XaLibAction::SetLayout("Standard");

    XaLibAction::AddXmlPath("XaAddressGeo");
	XaLibAction::AddXslPath("XaAddressGeoTpl");
    XaLibAction::AddXslPath("XaAddressGeoAddFrm");

    XaLibDom* LibDom=new XaLibDom();
	
	xmlDocPtr XmlDomDoc=LibDom->DomFromStringAndFile(XmlFilePaths,XmlStrings,1);
	XaLibAction::AddOptionsByDomain(LibDom,XmlDomDoc,XaDomainType,"//root/fieldset[@id='XaAddressGeo']/field[@name='XaDomainType_ID']/options");
	xmlDocPtr XslDomDoc=LibDom->DomFromStringAndFile(XslFilePaths,XslStrings,2);
	delete(LibDom);

	string XaUser_ID=HTTP.GetHttpParam("XaUser_ID");
	string XaTable=HTTP.GetHttpParam("XaTable");
	
	if (XaUser_ID!="NoHttpParam" && XaTable!="NoHttpParam"){
	
		const int MAXITEMS = 6;
		string XslParams[MAXITEMS] = {"XaUser_ID",XaUser_ID,"XaTable",XaTable,"XaDomainType",XaDomainType};
		XaLibXsl *LibXsl=new XaLibXsl(XmlDomDoc,XslDomDoc,XslParams,MAXITEMS);
		RESPONSE.Content=LibXsl->GetXHtml();
		delete(LibXsl);

	} else {

		XaLibAction::ErrorExit("XaInfoPage","GetHttpParam");
	}

};

void XaAddress::XaAddressGeoAdd(){

	string XaTable=HTTP.GetHttpParam("XaTable");
	string XaUser_ID=XaLibAction::DecryptParamId(HTTP.GetHttpParam("XaUser_ID"));
	string XaDomainType_ID=HTTP.GetHttpParam("XaDomainType_ID");

// in modifica si passa anche XaAddress_ID cioe la riga corrente che dovra essere disattivata
	string XaAddress_ID=HTTP.GetHttpParam("XaAddress_ID");

	string country=HTTP.GetHttpParam("country");
	string region=HTTP.GetHttpParam("administrative_area_level_1"); //state
	string city=HTTP.GetHttpParam("locality");
	string street=HTTP.GetHttpParam("route");
	string number=HTTP.GetHttpParam("street_number");
	string post_code=HTTP.GetHttpParam("postal_code");

	string address=HTTP.GetHttpParam("XaAddressGeo-Address");

	string latitude=HTTP.GetHttpParam("latitude");
	string longitude=HTTP.GetHttpParam("longitude");


	string StrArrFields[] = {"XaTable","XaField_ID","XaDomainType_ID","country","region","city","street","number","post_code","address","latitude","longitude"};
	vector<string> VectorFields(StrArrFields, StrArrFields + 12);

	string StrArrValues[] = {XaTable,XaUser_ID,XaDomainType_ID,country,region,city,street,number,post_code,address,latitude,longitude};
	vector<string> VectorValues(StrArrValues, StrArrValues + 12);

	VectorFields.push_back("active");
	VectorValues.push_back("1");

	VectorFields.push_back("deleted");
	VectorValues.push_back("0");

	VectorFields.push_back("created");
	VectorValues.push_back(XaLibAction::NowTimeMysql);

	LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Adding XaAddress Id -> " + XaUser_ID);

	XaLibSql* LibSql=new XaLibSql();

	int NextId=LibSql->Insert(DB_WRITE,"XaAddressGeo",VectorFields,VectorValues);
	
	if(NextId==0) {

		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Error Adding XaUserAddress for User -> " + XaUser_ID);

	} else {

		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Inserted Address ID -> "+ XaLibBase::FromIntToString(NextId));

		// disattivazione valore precedente
		if (XaAddress_ID!="NoHttpParam") {

			string DecryptedXaAddress_ID=XaLibAction::DecryptParamId(XaAddress_ID);

			LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Updating XaAddressGeo ->"+DecryptedXaAddress_ID+"for User -> " + XaUser_ID);

			vector<string> VectorFieldsUpd;
			vector<string> VectorValuesUpd;
			VectorFieldsUpd.push_back("active");
			VectorValuesUpd.push_back("2");
		
			vector<string> WhereFieldsUpd;
			vector<string> WhereValuesUpd;
			WhereFieldsUpd.push_back("id");
			WhereValuesUpd.push_back(DecryptedXaAddress_ID);
			
			int UpdateId=LibSql->Update(DB_WRITE,"XaAddressGeo",VectorFieldsUpd,VectorValuesUpd, WhereFieldsUpd,WhereValuesUpd);

			if(UpdateId==0) {
				LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Error Updating XaAddressGeo ->"+DecryptedXaAddress_ID+"for User -> " + XaUser_ID);
			} else {
				LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Updated XaAddressGeo ID -> "+ DecryptedXaAddress_ID);
			}

		}

	}

	delete (LibSql);

	VectorFields.clear();
	VectorValues.clear();

	RESPONSE.Content=XaLibAction::SelectDomainItem(XaDomainType_ID)+": " +address;

};


void XaAddress::XaAddressGeoModFrm(){

	string XaDomainType=HTTP.GetHttpParam("XaDomainType");

// serve anche XaAddress_ID perche deve disattivare solo l indirizzo che si sta modificando e non gli altri
	string XaAddress_ID=HTTP.GetHttpParam("XaAddress_ID");
	
    XaLibAction::SetLayout("Standard");

    XaLibAction::AddXmlPath("XaAddressGeo");
	XaLibAction::AddXslPath("XaAddressGeoTpl");
    XaLibAction::AddXslPath("XaAddressGeoModFrm");

    XaLibDom* LibDom=new XaLibDom();
	
	xmlDocPtr XmlDomDoc=LibDom->DomFromStringAndFile(XmlFilePaths,XmlStrings,1);
	XaLibAction::AddOptionsByDomain(LibDom,XmlDomDoc,XaDomainType,"//root/fieldset[@id='XaAddressGeo']/field[@name='XaDomainType_ID']/options");

	XaLibSql* LibSql=new XaLibSql();
	string QryGeo="SELECT * FROM XaAddressGeo WHERE id="+ XaLibAction::DecryptParamId(XaAddress_ID) +" AND active=1 AND deleted=0";

	DbResMap DbResGeo=LibSql->FreeQuery(DB_READ,QryGeo);

	for (int l=0; l<DbResGeo.size();l++) {
		string XPB="//fieldset[@id='XaAddressGeo']/";
		string r1 =XPB+"field[@id='XaDomainType_ID']/value";
		string r2 =XPB+"field[@id='autocomplete']/value";

		string ArrayXPathExpr[] = {r1,r2};
		vector<string> XPathExpr(ArrayXPathExpr, ArrayXPathExpr+2);

		string s1 =DbResGeo[l]["XaDomainType_ID"];
		string s2 =DbResGeo[l]["address"];

		string ArrayXPathValue[] = {s1,s2};
		vector<string> XPathValue(ArrayXPathValue, ArrayXPathValue+2);

		LibDom->UpdateElementValueByXPath(XmlDomDoc, XPathExpr, XPathValue);

		XPathExpr.clear();
		XPathValue.clear();

	}

	xmlDocPtr XslDomDoc=LibDom->DomFromStringAndFile(XslFilePaths,XslStrings,2);
	delete(LibDom);

	string XaUser_ID=HTTP.GetHttpParam("XaUser_ID");
	string XaTable=HTTP.GetHttpParam("XaTable");
	
	if (XaUser_ID!="NoHttpParam" && XaTable!="NoHttpParam"){
	
		const int MAXITEMS = 8;
		string XslParams[MAXITEMS] = {"XaUser_ID",XaUser_ID,"XaTable",XaTable,"XaAddress_ID",XaAddress_ID,"XaDomainType",XaDomainType};
		XaLibXsl *LibXsl=new XaLibXsl(XmlDomDoc,XslDomDoc,XslParams,MAXITEMS);
		RESPONSE.Content=LibXsl->GetXHtml();
		delete(LibXsl);

	} else {

		XaLibAction::ErrorExit("XaInfoPage","GetHttpParam");
	}

};


void XaAddress::XaAddressGeoList(){

	string EncryptedXaUser_ID=HTTP.GetHttpParam("XaUser_ID");
	string DecryptedXaUser_ID=XaLibAction::DecryptParamId(EncryptedXaUser_ID);
	string XaDomainType=HTTP.GetHttpParam("XaDomainType");

    XaLibAction::SetLayout("Standard");

    XaLibAction::AddXmlPath("XaAddressGeoListStruct");
    XaLibAction::AddXslPath("XaAddressGeoList");

	XaLibDom* LibDom=new XaLibDom();
	xmlDocPtr XmlDomDocData=LibDom->DomFromFile(SETTINGS["XmlDir"]+"XaAddressGeoListData.xml");

	XaLibSql* LibSql=new XaLibSql();

	// Check if the user is active, if is active the data is editable
	string Editable="no";
	
	vector<string> ReturnedFields, WhereFields, WhereValues;
	ReturnedFields.push_back("id");
	WhereFields.push_back("id");
	WhereValues.push_back(DecryptedXaUser_ID);
	WhereFields.push_back("active");
	WhereValues.push_back("1");
	WhereFields.push_back("deleted");
	WhereValues.push_back("0");

	DbResMap DbResEmployee=LibSql->Select(DB_READ,"XaUser",ReturnedFields,WhereFields,WhereValues);
	
	ReturnedFields.clear();
	WhereFields.clear();
	WhereValues.clear();
	
	if (DbResEmployee.size()==1) {
		Editable="yes";
	}
	//
	
	string QryGeo="SELECT * FROM XaAddressGeo WHERE XaTable=\"XaUser\" AND XaField_ID="+ DecryptedXaUser_ID +" AND deleted=0 AND active=1";
	DbResMap DbResGeo=LibSql->FreeQuery(DB_READ,QryGeo);

	for (int l=0; l<DbResGeo.size();l++) {

		xmlDocPtr XmlDomDocDataTemp=xmlCopyDoc(XmlDomDocData,1);

		string XPB="//XaAddressGeoList/data/geo/";
		string r1 =XPB+"type";
		string r2 =XPB+"address";
		string r3 =XPB+"id";

		string ArrayXPathExpr[] = {r1,r2,r3};
		vector<string> XPathExpr(ArrayXPathExpr, ArrayXPathExpr+3);

		string s1 =XaLibAction::SelectDomainItem(DbResGeo[l]["XaDomainType_ID"]);
		string s2 =DbResGeo[l]["address"];
		string s3 =XaLibAction::EncryptParam(DbResGeo[l]["id"]);

		string ArrayXPathValue[] = {s1,s2,s3};
		vector<string> XPathValue(ArrayXPathValue, ArrayXPathValue+3);

		LibDom->UpdateElementValueByXPath(XmlDomDocDataTemp, XPathExpr, XPathValue);

		XPathExpr.clear();
		XPathValue.clear();

		//RIMUOVERE INTESTAZIONE XML
		XaLibAction::AddXmlString(LibDom->StringFromDom(XmlDomDocDataTemp));
	}

	delete(LibSql);

	xmlDocPtr XmlDomDoc=LibDom->DomFromStringAndFile(XmlFilePaths,XmlStrings,1);
	xmlDocPtr XslDomDoc=LibDom->DomFromStringAndFile(XslFilePaths,XslStrings,2);
	delete(LibDom);

	const int MAXITEMS = 6;
	string XslParams[MAXITEMS] = {"XaUser_ID",EncryptedXaUser_ID,"XaDomainType",XaDomainType,"Editable",Editable};
    XaLibXsl *LibXsl=new XaLibXsl(XmlDomDoc,XslDomDoc,XslParams,MAXITEMS);
    RESPONSE.Content=LibXsl->GetXHtml();
	delete(LibXsl);

};


void XaAddress::XaAddressPhoneAddFrm(){

	string XaDomainType=HTTP.GetHttpParam("XaDomainType");
	string XaDomainCode=HTTP.GetHttpParam("XaDomainCode");
	
	string XaUser_ID=HTTP.GetHttpParam("XaUser_ID");
	string XaTable=HTTP.GetHttpParam("XaTable");

	
	XaLibAction::SetLayout("Standard");

    XaLibAction::AddXmlPath("XaAddressPhone");
    XaLibAction::AddXslPath("XaAddressPhoneAddFrm");
    XaLibAction::AddXslPath("XaAddressPhoneTpl");

    XaLibDom* LibDom=new XaLibDom();
    xmlDocPtr XmlDomDoc=LibDom->DomFromStringAndFile(XmlFilePaths,XmlStrings,1);

		XaLibAction::AddOptionsByDomain(LibDom,XmlDomDoc,XaDomainType,"//field[@name='XaDomainType_ID']/options");
		XaLibAction::OptionOrderByFields.push_back("description");
		XaLibAction::AddOptionsByDomainWithDescription(LibDom,XmlDomDoc,XaDomainCode,"//field[@name='XaDomainCode_ID']/options");
	
	xmlDocPtr XslDomDoc=LibDom->DomFromStringAndFile(XslFilePaths,XslStrings,2);
	delete(LibDom);


	if (XaUser_ID!="NoHttpParam" && XaTable!="NoHttpParam"){

		const int MAXITEMS = 6;
		string XslParams[MAXITEMS] = {"XaUser_ID",XaUser_ID,"XaTable",XaTable,"XaDomainType",XaDomainType};
		XaLibXsl *LibXsl=new XaLibXsl(XmlDomDoc,XslDomDoc,XslParams,MAXITEMS);
		RESPONSE.Content=LibXsl->GetXHtml();
		delete(LibXsl);

	} else {

		XaLibAction::ErrorExit("XaInfoPage","GetHttpParam");
	}
};

void XaAddress::XaAddressPhoneAdd(){

	string XaTable=HTTP.GetHttpParam("XaTable");
	string XaUser_ID=XaLibAction::DecryptParamId(HTTP.GetHttpParam("XaUser_ID"));
	string XaDomainType_ID=HTTP.GetHttpParam("XaDomainType_ID");
	string XaDomainCode_ID=HTTP.GetHttpParam("XaDomainCode_ID");

// in modifica si passa anche XaAddress_ID cioe la riga corrente che dovra essere disattivata
	string XaAddress_ID=HTTP.GetHttpParam("XaAddress_ID");

	string number=HTTP.GetHttpParam("XaUserPhone-Number");
	
	string StrArrFields[] = {"XaTable","XaField_ID","XaDomainType_ID","XaDomainCode_ID","number"};
	vector<string> VectorFields(StrArrFields, StrArrFields + 5);

	string StrArrValues[] = {XaTable,XaUser_ID,XaDomainType_ID,XaDomainCode_ID,number};
	vector<string> VectorValues(StrArrValues, StrArrValues + 5);
	
	VectorFields.push_back("active");
	VectorValues.push_back("1");

	VectorFields.push_back("deleted");
	VectorValues.push_back("0");

	VectorFields.push_back("created");
	VectorValues.push_back(XaLibAction::NowTimeMysql);

	LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Adding XaAddressPhone for User -> " + XaUser_ID);

	XaLibSql* LibSql=new XaLibSql();

	int NextId=LibSql->Insert(DB_WRITE,"XaAddressPhone",VectorFields,VectorValues);

	if(NextId==0) {

		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Error Adding XaAddressPhone for User -> " + XaUser_ID);

	} else {

		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Inserted XaAddressPhone ID -> "+ XaLibBase::FromIntToString(NextId));

		// disattivazione valore precedente
		if (XaAddress_ID!="NoHttpParam") {

			string DecryptedXaAddress_ID=XaLibAction::DecryptParamId(XaAddress_ID);	

			LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Updating XaAddressPhone ->"+DecryptedXaAddress_ID+"for User -> " + XaUser_ID);

			vector<string> VectorFieldsUpd;
			vector<string> VectorValuesUpd;
			VectorFieldsUpd.push_back("active");
			VectorValuesUpd.push_back("2");
		
			vector<string> WhereFieldsUpd;
			vector<string> WhereValuesUpd;
			WhereFieldsUpd.push_back("id");
			WhereValuesUpd.push_back(DecryptedXaAddress_ID);
			
			int UpdateId=LibSql->Update(DB_WRITE,"XaAddressPhone",VectorFieldsUpd,VectorValuesUpd, WhereFieldsUpd,WhereValuesUpd);

			if(UpdateId==0) {
				LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Error Updating XaAddressPhone ->"+DecryptedXaAddress_ID+"for User -> " + XaUser_ID);
			} else {
				LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Updated XaAddressPhone ID -> "+ DecryptedXaAddress_ID);
			}

		}

	}

	delete (LibSql);

	VectorFields.clear();
	VectorValues.clear();

	RESPONSE.Content=XaLibAction::SelectDomainItem(XaDomainType_ID)+": "+XaLibAction::SelectDomainItem(XaDomainCode_ID)+" " +number;
};


void XaAddress::XaAddressPhoneModFrm(){

	string XaDomainType=HTTP.GetHttpParam("XaDomainType");
	string XaDomainCode=HTTP.GetHttpParam("XaDomainCode");
	
	string XaUser_ID=HTTP.GetHttpParam("XaUser_ID");
	string XaTable=HTTP.GetHttpParam("XaTable");

// serve anche XaAddress_ID perche deve disattivare solo il telefono che si sta modificando e non gli altri
	string XaAddress_ID=HTTP.GetHttpParam("XaAddress_ID");

	XaLibAction::SetLayout("Standard");

    XaLibAction::AddXmlPath("XaAddressPhone");
    XaLibAction::AddXslPath("XaAddressPhoneModFrm");
    XaLibAction::AddXslPath("XaAddressPhoneTpl");

    XaLibDom* LibDom=new XaLibDom();
    xmlDocPtr XmlDomDoc=LibDom->DomFromStringAndFile(XmlFilePaths,XmlStrings,1);

	XaLibAction::AddOptionsByDomain(LibDom,XmlDomDoc,XaDomainType,"//field[@name='XaDomainType_ID']/options");
	XaLibAction::OptionOrderByFields.push_back("description");
	XaLibAction::AddOptionsByDomainWithDescription(LibDom,XmlDomDoc,XaDomainCode,"//field[@name='XaDomainCode_ID']/options");

	XaLibSql* LibSql=new XaLibSql();
	string QryPhone="SELECT * FROM XaAddressPhone WHERE id="+ XaLibAction::DecryptParamId(XaAddress_ID) +" AND active=1 AND deleted=0";

	DbResMap DbResPhone=LibSql->FreeQuery(DB_READ,QryPhone);

	for (int l=0; l<DbResPhone.size();l++) {
		string XPB="//fieldset[@id='XaAddressPhone']/";
		string r1 =XPB+"field[@id='XaDomainType_ID']/value";
		string r2 =XPB+"field[@id='XaDomainCode_ID']/value";
		string r3 =XPB+"field[@id='XaUserPhone-Number']/value";

		string ArrayXPathExpr[] = {r1,r2,r3};
		vector<string> XPathExpr(ArrayXPathExpr, ArrayXPathExpr+3);

		string s1 =DbResPhone[l]["XaDomainType_ID"];
		string s2 =DbResPhone[l]["XaDomainCode_ID"];
		string s3 =DbResPhone[l]["number"];

		string ArrayXPathValue[] = {s1,s2,s3};
		vector<string> XPathValue(ArrayXPathValue, ArrayXPathValue+3);

		LibDom->UpdateElementValueByXPath(XmlDomDoc, XPathExpr, XPathValue);

		XPathExpr.clear();
		XPathValue.clear();

	}

	xmlDocPtr XslDomDoc=LibDom->DomFromStringAndFile(XslFilePaths,XslStrings,2);
	delete(LibDom);

	if (XaUser_ID!="NoHttpParam" && XaTable!="NoHttpParam"){

		const int MAXITEMS = 8;
		string XslParams[MAXITEMS] = {"XaUser_ID",XaUser_ID,"XaTable",XaTable,"XaAddress_ID",XaAddress_ID,"XaDomainType",XaDomainType};
		XaLibXsl *LibXsl=new XaLibXsl(XmlDomDoc,XslDomDoc,XslParams,MAXITEMS);
		RESPONSE.Content=LibXsl->GetXHtml();
		delete(LibXsl);

	} else {

		XaLibAction::ErrorExit("XaInfoPage","GetHttpParam");
	}
};


void XaAddress::XaAddressPhoneList(){

	string EncryptedXaUser_ID=HTTP.GetHttpParam("XaUser_ID");
	string DecryptedXaUser_ID=XaLibAction::DecryptParamId(EncryptedXaUser_ID);
	string XaDomainType=HTTP.GetHttpParam("XaDomainType");

    XaLibAction::SetLayout("Standard");

    XaLibAction::AddXmlPath("XaAddressPhoneListStruct");
    XaLibAction::AddXslPath("XaAddressPhoneList");

	XaLibDom* LibDom=new XaLibDom();
	xmlDocPtr XmlDomDocData=LibDom->DomFromFile(SETTINGS["XmlDir"]+"XaAddressPhoneListData.xml");

	XaLibSql* LibSql=new XaLibSql();

	// Check if the user is active, if is active the data is editable
	string Editable="no";
	
	vector<string> ReturnedFields, WhereFields, WhereValues;
	ReturnedFields.push_back("id");
	WhereFields.push_back("id");
	WhereValues.push_back(DecryptedXaUser_ID);
	WhereFields.push_back("active");
	WhereValues.push_back("1");
	WhereFields.push_back("deleted");
	WhereValues.push_back("0");

	DbResMap DbResEmployee=LibSql->Select(DB_READ,"XaUser",ReturnedFields,WhereFields,WhereValues);
	
	ReturnedFields.clear();
	WhereFields.clear();
	WhereValues.clear();
	
	if (DbResEmployee.size()==1) {
		Editable="yes";
	}
	//

	string QryPhone="SELECT * FROM XaAddressPhone WHERE XaTable=\"XaUser\" AND XaField_ID="+ DecryptedXaUser_ID +" AND deleted=0 AND active=1";
	DbResMap DbResPhone=LibSql->FreeQuery(DB_READ,QryPhone);

	for (int l=0; l<DbResPhone.size();l++) {

		xmlDocPtr XmlDomDocDataTemp=xmlCopyDoc(XmlDomDocData,1);

		string XPB="//XaAddressPhoneList/data/phone/";
		string r1 =XPB+"type";
		string r2 =XPB+"code";
		string r3 =XPB+"number";
		string r4 =XPB+"id";

		string ArrayXPathExpr[] = {r1,r2,r3,r4};
		vector<string> XPathExpr(ArrayXPathExpr, ArrayXPathExpr+4);

		string s1 =XaLibAction::SelectDomainItem(DbResPhone[l]["XaDomainType_ID"]);
		string s2 =XaLibAction::SelectDomainItem(DbResPhone[l]["XaDomainCode_ID"]);
		string s3 =DbResPhone[l]["number"];
		string s4 =XaLibAction::EncryptParam(DbResPhone[l]["id"]);

		string ArrayXPathValue[] = {s1,s2,s3,s4};
		vector<string> XPathValue(ArrayXPathValue, ArrayXPathValue+4);

		LibDom->UpdateElementValueByXPath(XmlDomDocDataTemp, XPathExpr, XPathValue);

		XPathExpr.clear();
		XPathValue.clear();

		//RIMUOVERE INTESTAZIONE XML
		XaLibAction::AddXmlString(LibDom->StringFromDom(XmlDomDocDataTemp));
	}

	delete(LibSql);

	xmlDocPtr XmlDomDoc=LibDom->DomFromStringAndFile(XmlFilePaths,XmlStrings,1);
	xmlDocPtr XslDomDoc=LibDom->DomFromStringAndFile(XslFilePaths,XslStrings,2);
	delete(LibDom);

	const int MAXITEMS = 6;
	string XslParams[MAXITEMS] = {"XaUser_ID",EncryptedXaUser_ID,"XaDomainType",XaDomainType,"Editable",Editable};
    XaLibXsl *LibXsl=new XaLibXsl(XmlDomDoc,XslDomDoc,XslParams,MAXITEMS);
    RESPONSE.Content=LibXsl->GetXHtml();
	delete(LibXsl);

};


void XaAddress::XaAddressMailAddFrm(){
	
	string XaDomainType=HTTP.GetHttpParam("XaDomainType");
	
	string XaUser_ID=HTTP.GetHttpParam("XaUser_ID");
	string XaTable=HTTP.GetHttpParam("XaTable");
	
	XaLibAction::SetLayout("Standard");

    XaLibAction::AddXmlPath("XaAddressMail");

    XaLibAction::AddXslPath("XaAddressMailAddFrm");
    XaLibAction::AddXslPath("XaAddressMailTpl");

    XaLibDom* LibDom=new XaLibDom();
    xmlDocPtr XmlDomDoc=LibDom->DomFromStringAndFile(XmlFilePaths,XmlStrings,1);

		XaLibAction::AddOptionsByDomain(LibDom,XmlDomDoc,XaDomainType,"//field[@name='XaDomainType_ID']/options");
	
	xmlDocPtr XslDomDoc=LibDom->DomFromStringAndFile(XslFilePaths,XslStrings,2);
	delete(LibDom);


	if (XaUser_ID!="NoHttpParam" && XaTable!="NoHttpParam"){

		const int MAXITEMS = 6;
		string XslParams[MAXITEMS] = {"XaUser_ID",XaUser_ID,"XaTable",XaTable,"XaDomainType",XaDomainType};
		XaLibXsl *LibXsl=new XaLibXsl(XmlDomDoc,XslDomDoc,XslParams,MAXITEMS);
		RESPONSE.Content=LibXsl->GetXHtml();
		delete(LibXsl);

	} else {

		XaLibAction::ErrorExit("XaInfoPage","GetHttpParam");
	}

};

void XaAddress::XaAddressMailAdd(){

	string XaTable=HTTP.GetHttpParam("XaTable");
	string XaUser_ID=XaLibAction::DecryptParamId(HTTP.GetHttpParam("XaUser_ID"));
	string XaDomainType_ID=HTTP.GetHttpParam("XaDomainType_ID");

// in modifica si passa anche XaAddress_ID cioe la riga corrente che dovra essere disattivata
	string XaAddress_ID=HTTP.GetHttpParam("XaAddress_ID");

	string email=HTTP.GetHttpParam("XaUserEmail-Email");
	
	string StrArrFields[] = {"XaTable","XaField_ID","XaDomainType_ID","email"};
	vector<string> VectorFields(StrArrFields, StrArrFields + 4);

	string StrArrValues[] = {XaTable,XaUser_ID,XaDomainType_ID,email};
	vector<string> VectorValues(StrArrValues, StrArrValues + 4);
	
	VectorFields.push_back("active");
	VectorValues.push_back("1");

	VectorFields.push_back("deleted");
	VectorValues.push_back("0");

	VectorFields.push_back("created");
	VectorValues.push_back(XaLibAction::NowTimeMysql);

	LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Adding XaAddressMail for User -> " + XaUser_ID);

	XaLibSql* LibSql=new XaLibSql();

	int NextId=LibSql->Insert(DB_WRITE,"XaAddressMail",VectorFields,VectorValues);

	if(NextId==0) {

		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Error Adding XaAddressMail for User -> " + XaUser_ID);

	} else {

		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Inserted XaAddressMail ID -> "+ XaLibBase::FromIntToString(NextId));

		// disattivazione valore precedente
		if (XaAddress_ID!="NoHttpParam") {

			string DecryptedXaAddress_ID=XaLibAction::DecryptParamId(XaAddress_ID);	

			LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Updating XaAddressMail ->"+DecryptedXaAddress_ID+"for User -> " + XaUser_ID);

			vector<string> VectorFieldsUpd;
			vector<string> VectorValuesUpd;
			VectorFieldsUpd.push_back("active");
			VectorValuesUpd.push_back("2");
		
			vector<string> WhereFieldsUpd;
			vector<string> WhereValuesUpd;
			WhereFieldsUpd.push_back("id");
			WhereValuesUpd.push_back(DecryptedXaAddress_ID);
			
			int UpdateId=LibSql->Update(DB_WRITE,"XaAddressMail",VectorFieldsUpd,VectorValuesUpd, WhereFieldsUpd,WhereValuesUpd);

			if(UpdateId==0) {
				LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Error Updating XaAddressMail ->"+DecryptedXaAddress_ID+"for User -> " + XaUser_ID);
			} else {
				LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Updated XaAddressMail ID -> "+ DecryptedXaAddress_ID);
			}

		}

	}

	delete (LibSql);

	VectorFields.clear();
	VectorValues.clear();

	RESPONSE.Content=XaLibAction::SelectDomainItem(XaDomainType_ID)+": " +email;

};


void XaAddress::XaAddressMailModFrm(){

	string XaDomainType=HTTP.GetHttpParam("XaDomainType");
	
	string XaUser_ID=HTTP.GetHttpParam("XaUser_ID");
	string XaTable=HTTP.GetHttpParam("XaTable");

// serve anche XaAddress_ID perche deve disattivare solo l indirizzo che si sta modificando e non gli altri
	string XaAddress_ID=HTTP.GetHttpParam("XaAddress_ID");

	XaLibAction::SetLayout("Standard");

    XaLibAction::AddXmlPath("XaAddressMail");
    XaLibAction::AddXslPath("XaAddressMailModFrm");
    XaLibAction::AddXslPath("XaAddressMailTpl");

    XaLibDom* LibDom=new XaLibDom();
    xmlDocPtr XmlDomDoc=LibDom->DomFromStringAndFile(XmlFilePaths,XmlStrings,1);

	XaLibAction::AddOptionsByDomain(LibDom,XmlDomDoc,XaDomainType,"//field[@name='XaDomainType_ID']/options");

	XaLibSql* LibSql=new XaLibSql();
	string QryMail="SELECT * FROM XaAddressMail WHERE id="+ XaLibAction::DecryptParamId(XaAddress_ID) +" AND active=1 AND deleted=0";

	DbResMap DbResMail=LibSql->FreeQuery(DB_READ,QryMail);

	for (int l=0; l<DbResMail.size();l++) {
		string XPB="//fieldset[@id='XaAddressMail']/";
		string r1 =XPB+"field[@id='XaDomainType_ID']/value";
		string r2 =XPB+"field[@id='XaUserEmail-Email']/value";

		string ArrayXPathExpr[] = {r1,r2};
		vector<string> XPathExpr(ArrayXPathExpr, ArrayXPathExpr+2);

		string s1 =DbResMail[l]["XaDomainType_ID"];
		string s2 =DbResMail[l]["email"];

		string ArrayXPathValue[] = {s1,s2};
		vector<string> XPathValue(ArrayXPathValue, ArrayXPathValue+2);

		LibDom->UpdateElementValueByXPath(XmlDomDoc, XPathExpr, XPathValue);

		XPathExpr.clear();
		XPathValue.clear();

	}

	xmlDocPtr XslDomDoc=LibDom->DomFromStringAndFile(XslFilePaths,XslStrings,2);
	delete(LibDom);

	if (XaUser_ID!="NoHttpParam" && XaTable!="NoHttpParam"){

		const int MAXITEMS = 8;
		string XslParams[MAXITEMS] = {"XaUser_ID",XaUser_ID,"XaTable",XaTable,"XaAddress_ID",XaAddress_ID,"XaDomainType",XaDomainType};
		XaLibXsl *LibXsl=new XaLibXsl(XmlDomDoc,XslDomDoc,XslParams,MAXITEMS);
		RESPONSE.Content=LibXsl->GetXHtml();
		delete(LibXsl);

	} else {

		XaLibAction::ErrorExit("XaInfoPage","GetHttpParam");
	}
};


void XaAddress::XaAddressMailList(){

	string EncryptedXaUser_ID=HTTP.GetHttpParam("XaUser_ID");
	string DecryptedXaUser_ID=XaLibAction::DecryptParamId(EncryptedXaUser_ID);
	string XaDomainType=HTTP.GetHttpParam("XaDomainType");

    XaLibAction::SetLayout("Standard");

    XaLibAction::AddXmlPath("XaAddressMailListStruct");
    XaLibAction::AddXslPath("XaAddressMailList");

	XaLibDom* LibDom=new XaLibDom();
	xmlDocPtr XmlDomDocData=LibDom->DomFromFile(SETTINGS["XmlDir"]+"XaAddressMailListData.xml");

	XaLibSql* LibSql=new XaLibSql();

	// Check if the user is active, if is active the data is editable
	string Editable="no";
	
	vector<string> ReturnedFields, WhereFields, WhereValues;
	ReturnedFields.push_back("id");
	WhereFields.push_back("id");
	WhereValues.push_back(DecryptedXaUser_ID);
	WhereFields.push_back("active");
	WhereValues.push_back("1");
	WhereFields.push_back("deleted");
	WhereValues.push_back("0");

	DbResMap DbResEmployee=LibSql->Select(DB_READ,"XaUser",ReturnedFields,WhereFields,WhereValues);
	
	ReturnedFields.clear();
	WhereFields.clear();
	WhereValues.clear();
	
	if (DbResEmployee.size()==1) {
		Editable="yes";
	}
	//

	string QryPhone="SELECT * FROM XaAddressMail WHERE XaTable=\"XaUser\" AND XaField_ID="+ DecryptedXaUser_ID +" AND deleted=0 AND active=1";
	DbResMap DbResPhone=LibSql->FreeQuery(DB_READ,QryPhone);

	for (int l=0; l<DbResPhone.size();l++) {

		xmlDocPtr XmlDomDocDataTemp=xmlCopyDoc(XmlDomDocData,1);

		string XPB="//XaAddressMailList/data/mail/";
		string r1 =XPB+"type";
		string r2 =XPB+"email";
		string r3 =XPB+"id";

		string ArrayXPathExpr[] = {r1,r2,r3};
		vector<string> XPathExpr(ArrayXPathExpr, ArrayXPathExpr+3);

		string s1 =XaLibAction::SelectDomainItem(DbResPhone[l]["XaDomainType_ID"]);
		string s2 =DbResPhone[l]["email"];
		string s3 =XaLibAction::EncryptParam(DbResPhone[l]["id"]);

		string ArrayXPathValue[] = {s1,s2,s3};
		vector<string> XPathValue(ArrayXPathValue, ArrayXPathValue+3);

		LibDom->UpdateElementValueByXPath(XmlDomDocDataTemp, XPathExpr, XPathValue);

		XPathExpr.clear();
		XPathValue.clear();

		//RIMUOVERE INTESTAZIONE XML
		XaLibAction::AddXmlString(LibDom->StringFromDom(XmlDomDocDataTemp));
	}

	delete(LibSql);

	xmlDocPtr XmlDomDoc=LibDom->DomFromStringAndFile(XmlFilePaths,XmlStrings,1);
	xmlDocPtr XslDomDoc=LibDom->DomFromStringAndFile(XslFilePaths,XslStrings,2);
	delete(LibDom);

	const int MAXITEMS = 6;
	string XslParams[MAXITEMS] = {"XaUser_ID",EncryptedXaUser_ID,"XaDomainType",XaDomainType,"Editable",Editable};
    XaLibXsl *LibXsl=new XaLibXsl(XmlDomDoc,XslDomDoc,XslParams,MAXITEMS);
    RESPONSE.Content=LibXsl->GetXHtml();
	delete(LibXsl);

};

void XaAddress::XaAddressGeoDel(){

	string XaAddress_ID=HTTP.GetHttpParam("XaAddress_ID");
	string XaUser_ID=HTTP.GetHttpParam("XaUser_ID");

	string DecryptedXaAddress_ID=XaLibAction::DecryptParamId(XaAddress_ID);
	string DecryptedXaUser_ID=XaLibAction::DecryptParamId(XaUser_ID);

	XaLibSql* LibSql=new XaLibSql();

	LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Deleting XaAddressGeo ->"+DecryptedXaAddress_ID+" for User ->"+DecryptedXaUser_ID);

	int DeleteId=LibSql->DeleteOneLogicWithKey(DB_WRITE,"XaAddressGeo",DecryptedXaAddress_ID,"XaUser",DecryptedXaUser_ID);

	if(DeleteId==0) {
		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Error Deleting XaAddressGeo ->"+DecryptedXaAddress_ID);
	} else {
		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Deleted XaAddressGeo ID -> "+ DecryptedXaAddress_ID);
	}

	RESPONSE.Content=" deleted " ;

};

void XaAddress::XaAddressPhoneDel(){

	string XaAddress_ID=HTTP.GetHttpParam("XaAddress_ID");
	string XaUser_ID=HTTP.GetHttpParam("XaUser_ID");

	string DecryptedXaAddress_ID=XaLibAction::DecryptParamId(XaAddress_ID);
	string DecryptedXaUser_ID=XaLibAction::DecryptParamId(XaUser_ID);

	XaLibSql* LibSql=new XaLibSql();

	LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Deleting XaAddressPhone ->"+DecryptedXaAddress_ID+" for User ->"+DecryptedXaUser_ID);

	int DeleteId=LibSql->DeleteOneLogicWithKey(DB_WRITE,"XaAddressPhone",DecryptedXaAddress_ID,"XaUser",DecryptedXaUser_ID);

	if(DeleteId==0) {
		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Error Deleting XaAddressPhone ->"+DecryptedXaAddress_ID);
	} else {
		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Deleted XaAddressPhone ID -> "+ DecryptedXaAddress_ID);
	}

	RESPONSE.Content=" deleted " ;

};

void XaAddress::XaAddressMailDel(){

	string XaAddress_ID=HTTP.GetHttpParam("XaAddress_ID");
	string XaUser_ID=HTTP.GetHttpParam("XaUser_ID");

	string DecryptedXaAddress_ID=XaLibAction::DecryptParamId(XaAddress_ID);
	string DecryptedXaUser_ID=XaLibAction::DecryptParamId(XaUser_ID);

	XaLibSql* LibSql=new XaLibSql();

	LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Deleting XaAddressMail ->"+DecryptedXaAddress_ID+" for User ->"+DecryptedXaUser_ID);

	int DeleteId=LibSql->DeleteOneLogicWithKey(DB_WRITE,"XaAddressMail",DecryptedXaAddress_ID,"XaUser",DecryptedXaUser_ID);

	if(DeleteId==0) {
		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Error Deleting XaAddressMail ->"+DecryptedXaAddress_ID);
	} else {
		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Deleted XaAddressMail ID -> "+ DecryptedXaAddress_ID);
	}

	RESPONSE.Content=" deleted " ;

};

void XaAddress::AddXaAddressPhoneOptionsByDb(XaLibDom* LibDom,xmlDocPtr XmlDomDoc,string XPathExpr,string XaTable,string XaField_ID,string Language){

	XaLibSql* LibSql=new XaLibSql();
 	
	string QryPhone="SELECT p.id, concat(d1.name,' ',p.number) AS fullnumber, p.XaDomainType_ID as type FROM XaAddressPhone p, XaDomain d1";
	QryPhone+=" WHERE p.active=1 AND p.deleted=0 AND p.XaTable='"+XaTable+"' AND p.XaField_ID="+XaField_ID;
	QryPhone+=" AND d1.domain='XaPhoneCode' AND d1.id=p.XaDomainCode_ID";
	QryPhone+=" ORDER BY fullnumber";

	DbResMap DbResPhone=LibSql->FreeQuery(DB_READ,QryPhone);

	for(unsigned n=0; n<DbResPhone.size(); ++n) {

		string QryType="SELECT t.text AS text FROM XaDomain d2, XaLabel l, XaLabelTranslation t, XaDomain d3";
		QryType+=" WHERE d2.id="+DbResPhone[n]["type"];
		QryType+=" AND l.name=d2.name";
		QryType+=" AND t.XaLabel_ID=l.id";
		QryType+=" AND t.XaDomain_ID=d3.id";
		QryType+=" AND d3.domain='XaLanguage' AND d3.name='"+Language+"'";

		DbResMap DbResType=LibSql->FreeQuery(DB_READ,QryType);

		string OptionValue=DbResPhone[n]["id"];
		string OptionLabel=DbResPhone[n]["fullnumber"]+"  ("+DbResType[0]["text"]+")";

		LibDom->AddOptionElementByXPath(XmlDomDoc, XPathExpr,OptionLabel,OptionValue);
	}
	delete(LibSql);

	LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Added XaAddessPhone Options By Db-> "+ XPathExpr);

}

XaAddress::~XaAddress(){
};
