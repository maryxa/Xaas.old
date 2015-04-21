#include <XaCurrency.h>
#include <XaLibAction.h>

XaCurrency::XaCurrency(){
};

void XaCurrency::Dispatcher(string CalledEvent) {

	if (CalledEvent=="XaCurrencyRateAddFrm"){
        this->XaCurrencyRateAddFrm();
	} else if (CalledEvent=="XaCurrencyRateAdd"){
        this->XaCurrencyRateAdd();
	} else if (CalledEvent=="XaCurrencyRateList"){
        this->XaCurrencyRateList();
	} else {
		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Requested Event Does Not Exists -> "+CalledEvent);
	}
};

void XaCurrency::XaCurrencyRateAddFrm (){

    XaLibAction::SetLayout("Standard");

    XaLibAction::AddXmlPath("XaCurrencyRate");

    XaLibAction::AddXslPath("XaCurrencyRateTpl");
    XaLibAction::AddXslPath("XaCurrencyRateAddFrm");

    XaLibDom* LibDom=new XaLibDom();
    
    xmlDocPtr XmlDomDocData=LibDom->DomFromFile(SETTINGS["XmlDir"]+"XaCurrencyRateData.xml");
	
	XaLibSql* LibSql=new XaLibSql();

    string QryDomain="SELECT id,name,description FROM (SELECT id,name,description FROM XaDomain WHERE domain='XaCurrency' AND active=1 AND deleted=0 AND name !='EUR' AND position!=99000 ORDER BY description) AS a UNION SELECT id,name,description FROM (SELECT id,name,description FROM XaDomain WHERE domain='XaCurrency' AND active=1 AND deleted=0 AND name !='EUR' AND position!=10 ORDER BY description) AS b";
	
	DbResMap DbResDomain=LibSql->FreeQuery(DB_READ,QryDomain);

		for (int i=0;i<DbResDomain.size();i++) {

			xmlDocPtr XmlDomDocDataTemp=xmlCopyDoc(XmlDomDocData,1);
			
			string XPB="//XaCurrencyRate/data/currency/";
			string ArrayXPathExpr[] = {XPB+"id",XPB+"name",XPB+"description",XPB+"disp",XPB+"placeholder"};
			vector<string> XPathExpr(ArrayXPathExpr, ArrayXPathExpr+5);

			string ArrayXPathValue[] = {DbResDomain[i]["id"],DbResDomain[i]["name"],DbResDomain[i]["description"],DbResDomain[i]["description"],"EUR per "+DbResDomain[i]["name"]+" (format type: 0.123456)"};
			vector<string> XPathValue(ArrayXPathValue, ArrayXPathValue+5);

			LibDom->UpdateElementValueByXPath(XmlDomDocDataTemp, XPathExpr, XPathValue);

			XPathExpr.clear();
			XPathValue.clear();

			XaLibAction::AddXmlString(LibDom->StringFromDom(XmlDomDocDataTemp));
		}

	delete(LibSql);

    xmlDocPtr XmlDomDoc=LibDom->DomFromStringAndFile(XmlFilePaths,XmlStrings,1);
	
	xmlDocPtr XslDomDoc=LibDom->DomFromStringAndFile(XslFilePaths,XslStrings,2);
	delete(LibDom);

    const int MAXITEMS = 2;
    string XslParams[MAXITEMS] = {"a","b"};
    XaLibXsl *LibXsl=new XaLibXsl(XmlDomDoc,XslDomDoc,XslParams,MAXITEMS);
    RESPONSE.Content=LibXsl->GetXHtml();
	delete(LibXsl);

};

void XaCurrency::XaCurrencyRateAdd () {
	
	XaLibDom* LibDom=new XaLibDom();
	xmlDocPtr XmlDomDoc=LibDom->DomFromFile(SETTINGS["XmlDir"]+"XaCurrencyRate.xml");

	string StrArrKey[] = {"required","dimension"};
	vector<string> Vectorkey(StrArrKey, StrArrKey + 2);

	ParamFromDomMap ParamFromDom=LibDom->MapParamFromDom(XmlDomDoc,Vectorkey,"fieldset","field");
	
	string Year=HTTP.GetHttpParam("XaCurrency-WithEffectFrom_year");
	string Month=HTTP.GetHttpParam("XaCurrency-WithEffectFrom_month");
	string Day=HTTP.GetHttpParam("XaCurrency-WithEffectFrom_day");

	XaLibSql* LibSql=new XaLibSql();

    string QryDomain="SELECT id,name FROM XaDomain WHERE domain='XaCurrency' AND active=1 AND deleted=0 ORDER BY name";
	
	DbResMap DbResDomain=LibSql->FreeQuery(DB_READ,QryDomain);

	int count=-1;
	for (int i=0;i<DbResDomain.size();i++) {

		string Rate=HTTP.GetHttpParam(DbResDomain[i]["name"]);
		string XaDomainCurrency_ID=DbResDomain[i]["id"];

		Rate=XaLibAction::HttpParamValidation(DbResDomain[i]["name"],Rate,"",ParamFromDom[1]["required"],ParamFromDom[1]["dimension"],"","");
		
		if (Rate!="") {

			if (Rate=="NoHttpParam") {Rate="1.00000000";}
			
			vector<string> ReturnedFields1, WhereFields1, WhereValues1;
							
			ReturnedFields1.push_back("id");
		
			WhereFields1.push_back("XaDomainCurrency_ID");
			WhereFields1.push_back("active");
			WhereFields1.push_back("deleted");
		
			WhereValues1.push_back(XaDomainCurrency_ID);
			WhereValues1.push_back("1");
			WhereValues1.push_back("0");
		
			DbResMap DbRes1=LibSql->Select(DB_READ,"XaCurrencyRate",ReturnedFields1,WhereFields1,WhereValues1);
		
			ReturnedFields1.clear();
			WhereFields1.clear();
			WhereValues1.clear();
			
			// ADD
			vector<string> VectorFields, VectorValues;
			
			VectorFields.push_back("XaDomainCurrency_ID");
			VectorValues.push_back(XaDomainCurrency_ID);
			
			VectorFields.push_back("rate");
			VectorValues.push_back(Rate);
			
			VectorFields.push_back("with_effect_from");
			VectorValues.push_back(Year+"-"+Month+"-"+Day);
			
			VectorFields.push_back("active");
			VectorValues.push_back("1");
	
			VectorFields.push_back("deleted");
			VectorValues.push_back("0");
	
			VectorFields.push_back("created");
			VectorValues.push_back(XaLibAction::NowTimeMysql);
			
			VectorFields.push_back("last_updated");
			VectorValues.push_back(XaLibAction::NowTimeMysql);
	
			int NextId=LibSql->Insert(DB_WRITE,"XaCurrencyRate",VectorFields,VectorValues);
	
			if(NextId==0) {
	
				LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Error Inserting XaCurrencyRate");
	
			} else {
				
				count++;
				LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Inserted XaCurrencyRate ID -> "+ XaLibBase::FromIntToString(NextId));
				
				// UPDATE
				if(DbRes1.size()==1) {
					
					vector<string> VectorFields2, VectorValues2, WhereFields2, WhereValues2;
					
					VectorFields2.push_back("active");
					VectorValues2.push_back("2");
			
					VectorFields2.push_back("last_updated");
					VectorValues2.push_back(XaLibAction::NowTimeMysql);
			
					WhereFields2.push_back("id");
					WhereValues2.push_back(DbRes1[0]["id"]);
					
					int UpdateId=LibSql->Update(DB_WRITE,"XaCurrencyRate",VectorFields2,VectorValues2,WhereFields2,WhereValues2);
				
					VectorFields2.clear();
					VectorValues2.clear();
					WhereFields2.clear();
					WhereValues2.clear();
				
					if(UpdateId==0) {
				
						LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Error Updating Currency Rate, ID -> "+ DbRes1[0]["id"]);
				
					} else {
				
						LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Updated Currency Rate ID -> "+ DbRes1[0]["id"]);
				
					}
						
				}
				
			}
			
			VectorFields.clear();
			VectorValues.clear();
		
		}
	
	}
	
	delete (LibSql);
	
	RESPONSE.Content="Inserted "+ FromIntToString(count) +" Currency Rate";
};

void XaCurrency::XaCurrencyRateList(){
	
	string StrCurrency=HTTP.GetHttpParam("XaCurrency");

    XaLibAction::SetLayout("Standard");

    XaLibAction::AddXmlPath("XaCurrencyRateListStruct");
    XaLibAction::AddXslPath("XaCurrencyRateList");

	XaLibDom* LibDom=new XaLibDom();
	xmlDocPtr XmlDomDocData=LibDom->DomFromFile(SETTINGS["XmlDir"]+"XaCurrencyRateListData.xml");
	
	XaLibSql* LibSql=new XaLibSql();

	string filter="";
	
	if (StrCurrency!="" && StrCurrency!="NoHttpParam") {
		filter.append(" AND XaDomainCurrency_ID = '"+StrCurrency+"'");
	}
	
	string Qry="SELECT name,description,c.id,with_effect_from,XaDomainCurrency_ID,rate FROM XaCurrencyRate c, XaDomain d WHERE c.deleted=0 AND XaDomainCurrency_ID=d.id AND XaDomainCurrency_ID!='44' "+filter+" ORDER BY with_effect_from DESC,id DESC,description";
	
	DbResMap DbRes=LibSql->FreeQuery(DB_READ,Qry);

		for (int i=0;i<DbRes.size();i++) {

			xmlDocPtr XmlDomDocDataTemp=xmlCopyDoc(XmlDomDocData,1);
			
			string XPB="//XaCurrencyRateList/data/rate/";
			string ArrayXPathExpr[] = {XPB+"XaCurrencyRate-Id",XPB+"XaCurrencyRate-WithEffectFrom",XPB+"XaCurrencyRate-XaDomainCurrency_ID",XPB+"XaCurrencyRate-Rate",XPB+"XaDomain-Name",XPB+"XaDomain-Description"};
			vector<string> XPathExpr(ArrayXPathExpr, ArrayXPathExpr+6);

			string ArrayXPathValue[] = {DbRes[i]["id"],DbRes[i]["with_effect_from"],DbRes[i]["XaDomainCurrency_ID"],DbRes[i]["rate"],DbRes[i]["name"],DbRes[i]["description"]};
			vector<string> XPathValue(ArrayXPathValue, ArrayXPathValue+6);

			LibDom->UpdateElementValueByXPath(XmlDomDocDataTemp, XPathExpr, XPathValue);

			XPathExpr.clear();
			XPathValue.clear();

			XaLibAction::AddXmlString(LibDom->StringFromDom(XmlDomDocDataTemp));
		}

	delete(LibSql);
	
		xmlDocPtr XmlDomDoc=LibDom->DomFromStringAndFile(XmlFilePaths,XmlStrings,1);
		xmlDocPtr XslDomDoc=LibDom->DomFromStringAndFile(XslFilePaths,XslStrings,2);
	
		string XPathExprType;
		XPathExprType="/root/XaCurrencyRateList/fieldset/field[@name='XaCurrency']/options";
		XaLibAction::AddOptionsByDomainWithDescription(LibDom,XmlDomDoc,"XaCurrency",XPathExprType);
		
		string XPB="/root/XaCurrencyRateList/fieldset/";
		string ArrayXPathExpr[] = {XPB+"field[@name='XaCurrency']/value"};
		vector<string> XPathExpr(ArrayXPathExpr, ArrayXPathExpr+1);

		string ArrayXPathValue[] = {StrCurrency};
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

double XaCurrency::CalculateCurrencyRate(string FromCurrency,string ToCurrency,string Date) {
	
	double Rate=1;
	
	XaLibSql* LibSql=new XaLibSql();

	string QryFrom="SELECT rate FROM XaCurrencyRate WHERE XaDomainCurrency_ID="+ FromCurrency + " AND with_effect_from<='"+ Date +"' AND deleted=0 ORDER BY with_effect_from DESC,id DESC";
	string QryTo="SELECT rate FROM XaCurrencyRate WHERE XaDomainCurrency_ID="+ ToCurrency + " AND with_effect_from<='"+ Date +"' AND deleted=0 ORDER BY with_effect_from DESC, id DESC";
		
	DbResMap DbResFrom=LibSql->FreeQuery(DB_READ,QryFrom);
	DbResMap DbResTo=LibSql->FreeQuery(DB_READ,QryTo);

	if (DbResFrom.size()>0 && DbResTo.size()>0) {
		
		Rate = FromStringToDouble(DbResFrom[0]["rate"]) / FromStringToDouble(DbResTo[0]["rate"]);
		
		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Calculated Currency Rate -> " + XaLibBase::FromDoubleToString(Rate));
		
	} else {
		
		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Error Calculated Currency Rate");
		
	}
	
	delete(LibSql);
	
	return Rate;
};

double XaCurrency::CalculateMonthlyCurrencyRate(string FromCurrency,string ToCurrency,string Year,string Month) {
	
	double Rate=1;
	if (FromCurrency=="") {FromCurrency="44";}
	
	XaLibTime* LibTime=new XaLibTime();
	
	int IntYear=XaLibBase::FromStringToInt(Year);
	int IntMonth=XaLibBase::FromStringToInt(Month);
	
	int IntNextMonth=IntMonth+1;
	int IntNextYear=IntYear;
	if (IntNextMonth==13) {
		IntNextMonth=1;
		IntNextYear++;
	}
	
	string NextYear=XaLibBase::FromIntToString(IntNextYear);
	string NextMonth=XaLibBase::FromIntToString(IntNextMonth);
	
	string StartNextDate=NextYear+"-"+NextMonth+"-01";
	string EndNextDate=LibTime->LastDateOfMonth(NextYear,NextMonth);
	
	string StartDate=Year+"-"+Month+"-01";
	string EndDate=LibTime->LastDateOfMonth(Year,Month);
	
	XaLibSql* LibSql=new XaLibSql();

	string QryFrom="SELECT rate FROM XaCurrencyRate WHERE XaDomainCurrency_ID="+ FromCurrency + " AND with_effect_from BETWEEN '"+StartDate+"' AND '"+EndDate+"' AND deleted=0 ORDER BY with_effect_from DESC, id DESC";
	string QryTo="SELECT rate FROM XaCurrencyRate WHERE XaDomainCurrency_ID="+ ToCurrency + " AND with_effect_from BETWEEN '"+StartDate+"' AND '"+EndDate+"' AND deleted=0 ORDER BY with_effect_from DESC,id DESC";
		
	DbResMap DbResFrom=LibSql->FreeQuery(DB_READ,QryFrom);
	DbResMap DbResTo=LibSql->FreeQuery(DB_READ,QryTo);
	
	string QryFrom1="SELECT rate FROM XaCurrencyRate WHERE XaDomainCurrency_ID="+ FromCurrency + " AND with_effect_from BETWEEN '"+StartNextDate+"' AND '"+EndNextDate+"' AND deleted=0 ORDER BY with_effect_from ASC,id DESC";
	string QryTo1="SELECT rate FROM XaCurrencyRate WHERE XaDomainCurrency_ID="+ ToCurrency + " AND with_effect_from BETWEEN '"+StartNextDate+"' AND '"+EndNextDate+"' AND deleted=0 ORDER BY with_effect_from ASC,id DESC";
		
	DbResMap DbResFrom1=LibSql->FreeQuery(DB_READ,QryFrom1);
	DbResMap DbResTo1=LibSql->FreeQuery(DB_READ,QryTo1);
	
	string QryFrom2="SELECT rate FROM XaCurrencyRate WHERE XaDomainCurrency_ID="+ FromCurrency + " AND with_effect_from <= '"+StartDate+"' AND deleted=0 ORDER BY with_effect_from DESC,id DESC";
	string QryTo2="SELECT rate FROM XaCurrencyRate WHERE XaDomainCurrency_ID="+ ToCurrency + " AND with_effect_from <= '"+StartDate+"' AND deleted=0 ORDER BY with_effect_from DESC,id DESC";
		
	DbResMap DbResFrom2=LibSql->FreeQuery(DB_READ,QryFrom2);
	DbResMap DbResTo2=LibSql->FreeQuery(DB_READ,QryTo2);

	if (DbResFrom.size()>0 && DbResTo.size()>0) {
		
		Rate = FromStringToDouble(DbResFrom[0]["rate"]) / FromStringToDouble(DbResTo[0]["rate"]);
		
		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Calculated Currency Rate -> " + XaLibBase::FromDoubleToString(Rate));
		
	} else if (DbResFrom1.size()>0 && DbResTo1.size()>0) {
		
		Rate = FromStringToDouble(DbResFrom1[0]["rate"]) / FromStringToDouble(DbResTo1[0]["rate"]);
		
		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Calculated Currency Rate -> " + XaLibBase::FromDoubleToString(Rate));
		
	} else if (DbResFrom2.size()>0 && DbResTo2.size()>0) {
		
		Rate = FromStringToDouble(DbResFrom2[0]["rate"]) / FromStringToDouble(DbResTo2[0]["rate"]);
		
		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Calculated Currency Rate -> " + XaLibBase::FromDoubleToString(Rate));
		
	} else {
		
		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Error Calculated Currency Rate");
		
	}
	
	delete(LibSql);
	
	return Rate;
};

XaCurrency::~XaCurrency(){
};                          
