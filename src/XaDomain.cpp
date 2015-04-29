#include <XaDomain.h>
#include <XaLibAction.h>


XaDomain::XaDomain(){
};

void XaDomain::Dispatcher(const string &CalledEvent) {

	if (CalledEvent=="XaDomainList"){
        this->XaDomainList();
	} else if (CalledEvent=="XaDomainAddFrm"){
        this->XaDomainAddFrm();
	} else if (CalledEvent=="XaDomainAdd"){
        this->XaDomainAdd();
	} else if (CalledEvent=="XaDomainRowAddFrm"){
        this->XaDomainRowAddFrm();
	} else if (CalledEvent=="XaDomainRowAdd"){
        this->XaDomainRowAdd();
	} else {
		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Requested Event Does Not Exists -> "+CalledEvent);
	}
};

void XaDomain::XaDomainRowAddFrm (){

	string StrDomain=HTTP.GetHttpParam("domain");
	string StrTarget=HTTP.GetHttpParam("target");
	string StrLabel=HTTP.GetHttpParam("label");
	string StrLegend=HTTP.GetHttpParam("legend");
	string StrAlert=HTTP.GetHttpParam("alert");

    XaLibAction::SetLayout("Standard");

    XaLibAction::AddXmlPath("XaDomainRow");

    XaLibAction::AddXslPath("XaDomainRowTpl");
    XaLibAction::AddXslPath("XaDomainRowAddFrm");

    XaLibDom* LibDom=new XaLibDom();
    xmlDocPtr XmlDomDoc=LibDom->DomFromStringAndFile(XmlFilePaths,XmlStrings,1);
	xmlDocPtr XslDomDoc=LibDom->DomFromStringAndFile(XslFilePaths,XslStrings,2);
	delete(LibDom);

    const int MAXITEMS = 10;
    string XslParams[MAXITEMS] = {"domain",StrDomain,"target",StrTarget,"label",StrLabel,"legend",StrLegend,"alert",StrAlert};
    XaLibXsl *LibXsl=new XaLibXsl(XmlDomDoc,XslDomDoc,XslParams,MAXITEMS);
    RESPONSE.Content=LibXsl->GetXHtml();
	delete(LibXsl);

};

void XaDomain::XaDomainRowAdd () {

	string StrDescription=HTTP.GetHttpParam("XaDomain-Description");
	string StrDomain=HTTP.GetHttpParam("XaDomain-Domain");
	string StrLabel=HTTP.GetHttpParam("label");
	XaLibChar* LibChar=new XaLibChar;
	string StrName=LibChar->RemoveEmptyspace(StrDescription);
	delete (LibChar);
	
	StrName=StrDomain+"-"+StrName;

	vector<string> ReturnedFields2, WhereFields2, WhereValues2;
	ReturnedFields2.push_back("id");
	WhereFields2.push_back("name");
	WhereValues2.push_back(StrName);
	WhereFields2.push_back("domain");
	WhereValues2.push_back(StrDomain);

	XaLibSql* LibSql=new XaLibSql();
	DbResMap DbRes2=LibSql->Select(DB_READ,"XaDomain",ReturnedFields2,WhereFields2,WhereValues2);
	
	ReturnedFields2.clear();
	WhereFields2.clear();
	WhereValues2.clear();
	
	if (DbRes2.size()==0){
	
		vector<string> VectorFields, VectorValues;
	
		VectorFields.push_back("domain");
		VectorValues.push_back(StrDomain);
		
		VectorFields.push_back("name");
		VectorValues.push_back(StrName);
		
		VectorFields.push_back("description");
		VectorValues.push_back(StrDescription);
		
		VectorFields.push_back("active");
		VectorValues.push_back("1");
	
		VectorFields.push_back("deleted");
		VectorValues.push_back("0");
	
		VectorFields.push_back("created");
		VectorValues.push_back(XaLibAction::NowTimeMysql);
		
		VectorFields.push_back("last_updated");
		VectorValues.push_back(XaLibAction::NowTimeMysql);
	
		int NextId=LibSql->Insert(DB_WRITE,"XaDomain",VectorFields,VectorValues);
			
		string XaDomain_ID;
			
		if(NextId==0) {
			XaDomain_ID="0";
			LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Error Inserting XaDomain");
	
		} else {
	
			XaDomain_ID=XaLibBase::FromIntToString(NextId);
			LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Inserted XaDomain ID -> "+ XaLibBase::FromIntToString(NextId));
			
			if(StrLabel=="yes") {
				
				vector<string> ReturnedFields3, WhereFields3, WhereValues3;
				ReturnedFields3.push_back("id");
				WhereFields3.push_back("name");
				WhereValues3.push_back(StrName);
			
				DbResMap DbRes3=LibSql->Select(DB_READ,"XaLabel",ReturnedFields3,WhereFields3,WhereValues3);
				
				ReturnedFields3.clear();
				WhereFields3.clear();
				WhereValues3.clear();
				
				if (DbRes3.size()==0){
				
					vector<string> VectorFieldsL, VectorValuesL;
					
					VectorFieldsL.push_back("name");
					VectorFieldsL.push_back("description");
					
					VectorValuesL.push_back(StrName);
					VectorValuesL.push_back(StrName);
					
					int NextLabelId=LibSql->Insert(DB_WRITE,"XaLabel",VectorFieldsL,VectorValuesL);
					
					VectorFieldsL.clear();
					VectorValuesL.clear();
				
					if(NextLabelId!=0) {
					
						string LabelId=XaLibBase::FromIntToString(NextLabelId);
					
						vector<string> ReturnedFields4, WhereFields4, WhereValues4;
						
						ReturnedFields4.push_back("*");
					
						WhereFields4.push_back("domain");
						WhereFields4.push_back("active");
						WhereFields4.push_back("deleted");
					
						WhereValues4.push_back("XaLanguage");
						WhereValues4.push_back("1");
						WhereValues4.push_back("0");
					
						DbResMap DbRes4=LibSql->Select(DB_READ,"XaDomain",ReturnedFields4,WhereFields4,WhereValues4);
					
						ReturnedFields4.clear();
						WhereFields4.clear();
						WhereValues4.clear();
					
						for(unsigned n=0; n<DbRes4.size(); ++n){
					
							vector<string> VectorFieldsT, VectorValuesT;
							
							VectorFieldsT.push_back("XaLabel_ID");
							VectorFieldsT.push_back("XaDomain_ID");
							VectorFieldsT.push_back("text");
								
							VectorValuesT.push_back(LabelId);
							VectorValuesT.push_back(DbRes4[n]["id"]);
							VectorValuesT.push_back(StrDescription);	
					
							LibSql->Insert(DB_WRITE,"XaLabelTranslation",VectorFieldsT,VectorValuesT);
							
							VectorFieldsL.clear();
							VectorValuesL.clear();
					
						}
				
					}
				}
			}
		}
	
		delete (LibSql);
		VectorFields.clear();
		VectorValues.clear();
	
		RESPONSE.Content="<option value=\""+XaDomain_ID+"\">"+StrDescription+"</option>";
		
	} else {
		RESPONSE.Content="";
	}
};

void XaDomain::XaDomainList (){
	
	string StrDomain=HTTP.GetHttpParam("domain");

    XaLibAction::SetLayout("Standard");

    XaLibAction::AddXmlPath("XaDomainListStruct");
    XaLibAction::AddXslPath("XaDomainList");

	XaLibDom* LibDom=new XaLibDom();
	xmlDocPtr XmlDomDocData=LibDom->DomFromFile(SETTINGS["XmlDir"]+"XaDomainListData.xml");
	
	XaLibSql* LibSql=new XaLibSql();

	string filter="";
	
	if (StrDomain!="" and StrDomain!="NoHttpParam") {
		filter.append(" AND domain = '"+StrDomain+"'");
	}
	
	
	string QryDomain="SELECT * FROM XaDomain WHERE deleted=0 "+filter+" ORDER BY domain,id";
	
	DbResMap DbResDomain=LibSql->FreeQuery(DB_READ,QryDomain);

		for (int i=0;i<DbResDomain.size();i++) {

			xmlDocPtr XmlDomDocDataTemp=xmlCopyDoc(XmlDomDocData,1);
			
			string XPB="//XaDomainList/data/domain/";
			string ArrayXPathExpr[] = {XPB+"XaDomain-Id",XPB+"XaDomain-Domain",XPB+"XaDomain-Name",XPB+"XaDomain-Description",XPB+"XaDomain-Position",XPB+"XaDomain-Active"};
			vector<string> XPathExpr(ArrayXPathExpr, ArrayXPathExpr+6);

			string ArrayXPathValue[] = {XaLibAction::EncryptParam(DbResDomain[i]["id"]),DbResDomain[i]["domain"],DbResDomain[i]["name"],DbResDomain[i]["description"],DbResDomain[i]["position"],DbResDomain[i]["active"]};
			vector<string> XPathValue(ArrayXPathValue, ArrayXPathValue+6);

			LibDom->UpdateElementValueByXPath(XmlDomDocDataTemp, XPathExpr, XPathValue);

			XPathExpr.clear();
			XPathValue.clear();

			

			string ArrayXPathExprID[] = {"//XaDomainList/data/actions/action/id"};
			vector<string> XPathExprID(ArrayXPathExprID, ArrayXPathExprID+1);

			string ArrayXPathValueID[] = {XaLibAction::EncryptParam(DbResDomain[i]["id"])};
			vector<string> XPathValueID(ArrayXPathValueID, ArrayXPathValueID+1);

			
			LibDom->UpdateElementValueByXPath(XmlDomDocDataTemp,XPathExprID,XPathValueID);
			
			XPathExprID.clear();
			XPathValueID.clear();
			//RIMUOVERE INTESTAZIONE XML
			XaLibAction::AddXmlString(LibDom->StringFromDom(XmlDomDocDataTemp));
		}

	delete(LibSql);
	
		xmlDocPtr XmlDomDoc=LibDom->DomFromStringAndFile(XmlFilePaths,XmlStrings,1);
		xmlDocPtr XslDomDoc=LibDom->DomFromStringAndFile(XslFilePaths,XslStrings,2);
	
		string XPathExprType;
		XPathExprType="/root/XaDomainList/fieldset/field[@name='XaDomain-Domain']/options";
		this->AddOptionsAllDomain(LibDom,XmlDomDoc,XPathExprType);
		
		
		
		string XPB="/root/XaDomainList/fieldset/";
		string ArrayXPathExpr[] = {XPB+"field[@name='XaDomain-Domain']/value"};
		vector<string> XPathExpr(ArrayXPathExpr, ArrayXPathExpr+1);

		string ArrayXPathValue[] = {StrDomain};
		vector<string> XPathValue(ArrayXPathValue, ArrayXPathValue+1);

		LibDom->UpdateElementValueByXPath(XmlDomDoc, XPathExpr, XPathValue);

		XPathExpr.clear();
		XPathValue.clear();
		
		
	
	delete(LibDom);

    const int MAXITEMS = 2;
    string XslParams[MAXITEMS] = {"a","b"};
    XaLibXsl *LibXsl=new XaLibXsl(XmlDomDoc,XslDomDoc,XslParams,MAXITEMS);
    RESPONSE.Content=LibXsl->GetXHtml();
	delete(LibXsl);

};

void XaDomain::XaDomainAddFrm (){

    XaLibAction::SetLayout("Standard");

    XaLibAction::AddXmlPath("XaDomain");

    XaLibAction::AddXslPath("XaDomainTpl");
    XaLibAction::AddXslPath("XaDomainAddFrm");

    XaLibDom* LibDom=new XaLibDom();
    xmlDocPtr XmlDomDoc=LibDom->DomFromStringAndFile(XmlFilePaths,XmlStrings,1);

	string XPathExprType;

	XPathExprType="/root/fieldset[@id='XaDomain']/field[@name='XaDomain-Domain']/options";
	this->AddOptionsAllDomain(LibDom,XmlDomDoc,XPathExprType);

	xmlDocPtr XslDomDoc=LibDom->DomFromStringAndFile(XslFilePaths,XslStrings,2);
	delete(LibDom);

    const int MAXITEMS = 2;
    string XslParams[MAXITEMS] = {"a","b"};
    XaLibXsl *LibXsl=new XaLibXsl(XmlDomDoc,XslDomDoc,XslParams,MAXITEMS);
    RESPONSE.Content=LibXsl->GetXHtml();
	delete(LibXsl);

};

void XaDomain::XaDomainAdd () {

	XaLibDom* LibDom=new XaLibDom();
	xmlDocPtr XmlDomDoc=LibDom->DomFromFile(SETTINGS["XmlDir"]+"XaDomain.xml");

	string StrArrKey[] = {"name","dbname","datatype","required"};
	vector<string> Vectorkey(StrArrKey, StrArrKey + 4);

	ParamFromDomMap ParamFromDom=LibDom->MapParamFromDom(XmlDomDoc,Vectorkey,"fieldset","field");

	vector<string> VectorFields, VectorValues;

	for(unsigned i=0; i<ParamFromDom.size(); ++i){

		string ParamValue=HTTP.GetHttpParam(ParamFromDom[i]["name"]);

		VectorFields.push_back(ParamFromDom[i]["dbname"]);
		VectorValues.push_back(ParamValue);
	}

		VectorFields.push_back("active");
		VectorValues.push_back("1");

		VectorFields.push_back("deleted");
		VectorValues.push_back("0");

		VectorFields.push_back("created");
		VectorValues.push_back(XaLibAction::NowTimeMysql);
		
		VectorFields.push_back("last_updated");
		VectorValues.push_back(XaLibAction::NowTimeMysql);

		XaLibSql* LibSql=new XaLibSql();
		int NextId=LibSql->Insert(DB_WRITE,"XaDomain",VectorFields,VectorValues);
		delete (LibSql);

		if(NextId==0) {

			LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Error Inserting XaDomain");

		} else {

			LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Inserted XaDomain ID -> "+ XaLibBase::FromIntToString(NextId));

		}

	ParamFromDom.clear();
	VectorFields.clear();
	VectorValues.clear();

	RESPONSE.Content="Inserted XaDomain -> ID: " + XaLibBase::FromIntToString(NextId);
};

void XaDomain::AddOptionsAllDomain(XaLibDom* LibDom,xmlDocPtr XmlDomDoc,string XPathExpr){

	XaLibSql* LibSql=new XaLibSql();

	string Qry="SELECT distinct domain FROM XaDomain WHERE active=1 AND deleted=0";
	
	DbResMap DbRes=LibSql->FreeQuery(DB_READ,Qry);
	
	delete(LibSql);

	for(unsigned n=0; n<DbRes.size(); ++n) {

		string OptionValue=DbRes[n]["domain"];
		string OptionLabel=DbRes[n]["domain"];

		LibDom->AddOptionElementByXPath(XmlDomDoc, XPathExpr,OptionLabel,OptionValue);
	}

	DbRes.clear();
	
};

XaDomain::~XaDomain(){
};                          
