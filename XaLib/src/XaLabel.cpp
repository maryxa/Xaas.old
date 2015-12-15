#include <XaLabel.h>
//#include <XaLibAction.h>
#include <XaLibModel.h>

XaLabel::XaLabel(){

    //XaLibAction::SetActionVariables();
};

void XaLabel::Dispatcher(const string &CalledEvent) {

	if (CalledEvent=="XaLabelGen"){
            this->XaLabelGen();
	} else if (CalledEvent=="Create"){
            this->Create();
	} else if (CalledEvent=="Delete"){
            this->Delete();
	} else {
        LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"ERROR-42 Requested Event Does Not Exists -> "+CalledEvent);
        throw 42;
    }
};

/*
void XaLabel::XaLabelFromXaDomainGen (){
	
	DbResMap DbRes;
	
	XaLibSql* LibSql=new XaLibSql();
	
	string qry="SELECT name,description FROM XaDomain WHERE active=1 AND deleted=0 AND domain NOT IN ('XaCurrency','XaPhoneCode','XaLanguage','XaCountryCode','XaSalaryBase','XaYear','XaJobTitle')";
	
	DbRes=LibSql->FreeQuery(DB_READ,qry);
	
	for(unsigned n=0; n<DbRes.size(); ++n){

		this->XaLabelInsertLabelFromXaDomain(DbRes[n]["name"],DbRes[n]["description"]);
		
	}
	
	this->XaLabelGen();

};

void XaLabel::XaLabelInsertLabelFromXaDomain(string NameLabel,string TextLabel){

	DbResMap DbRes2;

	XaLibSql* LibSql2=new XaLibSql();

	vector<string> ReturnedFields2;
	ReturnedFields2.push_back("*");

	vector<string> WhereFields2;
	WhereFields2.push_back("name");

	vector<string> WhereValues2;
	WhereValues2.push_back(NameLabel);

	DbRes2=LibSql2->Select(DB_READ,"XaLabel",ReturnedFields2,WhereFields2,WhereValues2);
	
	delete(LibSql2);
	
	if (DbRes2.size()==0){
	
		vector<string> VectorFields;
		vector<string> VectorValues;
		
		VectorFields.push_back("name");
		VectorFields.push_back("description");
		
		VectorValues.push_back(NameLabel);
		VectorValues.push_back(NameLabel);
		
		XaLibSql* LibSql=new XaLibSql();
	
		int NextId=LibSql->Insert(DB_WRITE,"XaLabel",VectorFields,VectorValues);
	
		string LabelId=XaLibBase::FromIntToString(NextId);
	
		DbResMap DbRes;
	
		XaLibSql* LibSql1=new XaLibSql();
	
		vector<string> ReturnedFields;
		ReturnedFields.push_back("*");
	
		vector<string> WhereFields;
		WhereFields.push_back("domain");
		WhereFields.push_back("active");
	
		vector<string> WhereValues;
		WhereValues.push_back("XaLanguage");
		WhereValues.push_back("1");
	
		DbRes=LibSql1->Select(DB_READ,"XaDomain",ReturnedFields,WhereFields,WhereValues);
	
		delete(LibSql1);
	
		for(unsigned n=0; n<DbRes.size(); ++n){
	
			vector<string> VectorFields1;
			vector<string> VectorValues1;
			
			if (DbRes[n]["name"]==REQUEST.Language){ 
	
				VectorFields1.push_back("XaLabel_ID");
				VectorFields1.push_back("XaDomain_ID");
				VectorFields1.push_back("text");
				
				VectorValues1.push_back(LabelId);
				VectorValues1.push_back(DbRes[n]["id"]);
				VectorValues1.push_back(TextLabel);
				
			} else {
			
				VectorFields1.push_back("XaLabel_ID");
				VectorFields1.push_back("XaDomain_ID");
		
				VectorValues1.push_back(LabelId);
				VectorValues1.push_back(DbRes[n]["id"]);
			
			}
	
			LibSql->Insert(DB_WRITE,"XaLabelTranslation",VectorFields1,VectorValues1);
	
		}
	
		delete(LibSql);
	
	}
};

void XaLabel::XaLabelFromFileAdd (){
	
	string StrName=HTTP.GetHttpParam("XaLabel-Name");
	
	string NameFile;
	xmlDocPtr XmlDomDoc;

	NameFile=SETTINGS["XmlDir"]+StrName+".xml";

	XaLibDom* LibDom=new XaLibDom();

	XmlDomDoc=LibDom->DomFromFile(NameFile);
	
	string StrArrKey[] = {"name"};
	vector<string> Vectorkey(StrArrKey, StrArrKey + 1);

	ParamFromDomMap ParamFromDom;
	ParamFromDom=LibDom->MapParamFromDom(XmlDomDoc,Vectorkey,"fieldset","field");

	for(unsigned i=0; i<ParamFromDom.size(); ++i){

		this->XaLabelInsertLabel(StrName+"-"+ParamFromDom[i]["name"]);
		
	}
	
	this->XaLabelInsertLabel(StrName+"-Legend");
	
	this->XaLabelGen();
	
	RESPONSE.Content="Inserted Label From File: "+StrName+".xml";

};

void XaLabel::XaLabelInsertLabel(string NameLabel){

	vector<string> VectorFields;
	vector<string> VectorValues;
	
	VectorFields.push_back("name");
	VectorFields.push_back("description");
	
	VectorValues.push_back(NameLabel);
	VectorValues.push_back(NameLabel);
	
	XaLibSql* LibSql=new XaLibSql();

	int NextId=LibSql->Insert(DB_WRITE,"XaLabel",VectorFields,VectorValues);

	string LabelId=XaLibBase::FromIntToString(NextId);

	DbResMap DbRes;

	XaLibSql* LibSql1=new XaLibSql();

	vector<string> ReturnedFields;
	ReturnedFields.push_back("*");

	vector<string> WhereFields;
	WhereFields.push_back("domain");
	WhereFields.push_back("active");

	vector<string> WhereValues;
	WhereValues.push_back("XaLanguage");
	WhereValues.push_back("1");

	DbRes=LibSql1->Select(DB_READ,"XaDomain",ReturnedFields,WhereFields,WhereValues);

	delete(LibSql1);

	for(unsigned n=0; n<DbRes.size(); ++n){

		vector<string> VectorFields1;
		VectorFields1.push_back("XaLabel_ID");
		VectorFields1.push_back("XaDomain_ID");

		vector<string> VectorValues1;
		VectorValues1.push_back(LabelId);
		VectorValues1.push_back(DbRes[n]["id"]);

		LibSql->Insert(DB_WRITE,"XaLabelTranslation",VectorFields1,VectorValues1);

	}

	delete(LibSql);
	
};

void XaLabel::XaLabelFromFileAddFrm (){

    XaLibAction::SetLayout("Standard");

    XaLibAction::AddXmlFile("XaLabelFromFile");
    
    XaLibAction::AddXslFile("XaLabelFromFileTpl");
    XaLibAction::AddXslFile("XaLabelFromFileAddFrm");

    XaLibDom* LibDom=new XaLibDom();
		xmlDocPtr XmlDomDoc=LibDom->DomFromStringAndFile(XmlFiles,XmlStrings,1);
		xmlDocPtr XslDomDoc=LibDom->DomFromStringAndFile(XslFiles,XslStrings,2);
	delete(LibDom);


    const int MAXITEMS = 2;
    string XslParams[MAXITEMS] = {"a","b"};
    XaLibXsl *LibXsl=new XaLibXsl(XmlDomDoc,XslDomDoc,XslParams,MAXITEMS);
    RESPONSE.Content=LibXsl->GetXHtml();
	delete(LibXsl);

};

void XaLabel::XaLabelMod (){

	XaLibSql* LibSql=new XaLibSql();

	DbResMap DbRes1;
	
	XaLibSql* LibSql1=new XaLibSql();
	
	vector<string> ReturnedFields1;
	ReturnedFields1.push_back("*");

	vector<string> WhereFields1;
	WhereFields1.push_back("domain");
	WhereFields1.push_back("active");

	vector<string> WhereValues1;
	WhereValues1.push_back("XaLanguage");
	WhereValues1.push_back("1");
	
	DbRes1=LibSql1->Select(DB_READ,"XaDomain",ReturnedFields1,WhereFields1,WhereValues1);
	
	delete(LibSql1);
	
	string LabelId;
	
	for(unsigned n=0; n<DbRes1.size(); ++n){

		string StrText=HTTP.GetHttpParam(DbRes1[n]["name"]);
		string StrHelp=HTTP.GetHttpParam("help"+DbRes1[n]["name"]);
		string StrPlaceholder=HTTP.GetHttpParam("ph"+DbRes1[n]["name"]);
		LabelId=HTTP.GetHttpParam("id");
		
		if (StrText!="" or StrHelp!="" or StrPlaceholder!=""){
		
			vector<string> VectorFields;
			vector<string> VectorValues;
			
			if (StrText!="" and StrText!="NoHttpParam"){
				VectorFields.push_back("text");
				VectorValues.push_back(StrText);
			}
			if (StrHelp!="" and StrHelp!="NoHttpParam"){
				VectorFields.push_back("help");
				VectorValues.push_back(StrHelp);
			}
			if (StrPlaceholder!="" and StrPlaceholder!="NoHttpParam"){
				VectorFields.push_back("placeholder");
				VectorValues.push_back(StrPlaceholder);
			}
			
			vector<string> WhereFields;
			WhereFields.push_back("XaLabel_ID");
			WhereFields.push_back("XaDomain_ID");
		
			vector<string> WhereValues;
			WhereValues.push_back(LabelId);
			WhereValues.push_back(DbRes1[n]["id"]);
	
			LibSql->Update(DB_WRITE,"XaLabelTranslation",VectorFields,VectorValues,WhereFields,WhereValues);

		}

	}
	
	delete(LibSql);
	
	this->XaLabelGen();
	
	RESPONSE.Content=" - Modified Label ID: " +LabelId;

};

void XaLabel::XaLabelList (){
	
	string StrLanguage=HTTP.GetHttpParam("XaLanguage");
	
	DbResMap DbRes;
	DbResMap DbRes1;
	DbResMap DbRes2;
	DbResMap DbRes3;
	
	string XmlString;
	string ListLang;
	string cond;
	
	XaLibSql* LibSql=new XaLibSql();

	if (StrLanguage!="" and StrLanguage!="NoHttpParam") {
		cond.append(" AND id=");
		cond.append(StrLanguage);
	} else {
		cond.append(" AND name='it'");
	}
	
	string qry="SELECT * FROM XaDomain WHERE domain = 'XaLanguage' AND active=1";
	qry.append(cond);
	qry.append(" ORDER BY id");
	
	DbRes=LibSql->FreeQuery(DB_READ,qry);
	
	XmlString="<titles>";
		
		XmlString.append("<title>");
			XmlString.append("<label>");
			XmlString.append("id");
			XmlString.append("</label>");
		XmlString.append("</title>");
		XmlString.append("<title>");
			XmlString.append("<label>");
			XmlString.append("name");
			XmlString.append("</label>");
		XmlString.append("</title>");
		XmlString.append("<title>");
			XmlString.append("<label>");
			XmlString.append("description");
			XmlString.append("</label>");
		XmlString.append("</title>");
		XmlString.append("<title>");
			XmlString.append("<label>");
			XmlString.append("text_placeholder_help");
			XmlString.append("</label>");
		XmlString.append("</title>");
	
	for(unsigned n=0; n<DbRes.size(); ++n){
		
		ListLang.append(DbRes[n]["name"]);
		ListLang.append(",");
		
	}
	
	XmlString.append("</titles>");
	
	int ListLangSize=ListLang.size()-1;
	ListLang=ListLang.substr (0,ListLangSize);
	
	XmlString.append("<list_lang>");
	XmlString.append(ListLang);
	XmlString.append("</list_lang>");
	
	vector<string> ReturnedFields;
	ReturnedFields.push_back("*");

	vector<string> WhereFields;
	WhereFields.push_back("1");

	vector<string> WhereValues;
	WhereValues.push_back("1");
	
	vector<string> OrderByFields;
	OrderByFields.push_back("name");
	
	DbRes1=LibSql->Select(DB_READ,"XaLabel",ReturnedFields,WhereFields,WhereValues,OrderByFields);
	DbRes2=LibSql->Select(DB_READ,"XaLabelTranslation",ReturnedFields,WhereFields,WhereValues);
						
	XmlString.append("<fieldset>");
		
		//label
		for(unsigned i=0; i<DbRes1.size(); ++i){
		
			XmlString.append("<field name=\""+DbRes1[i]["name"]+"\" id=\""+DbRes1[i]["id"]+"\">");
			//XmlString.append("<label>");
			
				XmlString.append("<id>");
				XmlString.append(DbRes1[i]["id"]);
				XmlString.append("</id>");
				
				XmlString.append("<name>");
				XmlString.append(DbRes1[i]["name"]);
				XmlString.append("</name>");
				
				XmlString.append("<desc>");
				XmlString.append(DbRes1[i]["description"]);
				XmlString.append("</desc>");
				
				//language
				for(unsigned n=0; n<DbRes.size(); ++n){
		
					XmlString.append("<lang>");
					
						XmlString.append("<id>");
						XmlString.append(DbRes[n]["id"]);
						XmlString.append("</id>");
						
						XmlString.append("<label>");
						XmlString.append(DbRes[n]["description"]);
						XmlString.append("</label>");
						
						XmlString.append("<code>");
						XmlString.append(DbRes[n]["name"]);
						XmlString.append("</code>");
					
						//translation
						for(unsigned t=0; t<DbRes2.size(); ++t){
							
							if (DbRes[n]["id"]==DbRes2[t]["XaDomain_ID"] and DbRes1[i]["id"]==DbRes2[t]["XaLabel_ID"]){
								
								string qry3="SELECT * FROM XaLabelTranslation WHERE XaLabel_ID="+DbRes2[t]["XaLabel_ID"]+" AND XaDomain_ID=482";
								
								DbRes3=LibSql->FreeQuery(DB_READ,qry3);
								
								if (DbRes3.size()==1) {

									XmlString.append("<text-en>");
									XmlString.append(DbRes3[0]["text"]);
									XmlString.append("</text-en>");
									
									XmlString.append("<placeholder-en>");
									XmlString.append(DbRes3[0]["placeholder"]);
									XmlString.append("</placeholder-en>");
									
									XmlString.append("<help-en>");
									XmlString.append(DbRes3[0]["help"]);
									XmlString.append("</help-en>");
							
								}
								
								XmlString.append("<text>");
								XmlString.append(DbRes2[t]["text"]);
								XmlString.append("</text>");
								
								XmlString.append("<placeholder>");
								XmlString.append(DbRes2[t]["placeholder"]);
								XmlString.append("</placeholder>");
								
								XmlString.append("<help>");
								XmlString.append(DbRes2[t]["help"]);
								XmlString.append("</help>");
							
							}
						
						}
						
					XmlString.append("</lang>");
					
				}
			
			XmlString.append("</field>");
		}
		
	XmlString.append("</fieldset>");
	
	
	
	delete(LibSql);
	
	XaLibAction::AddXmlString(XmlString);

    string XmlPage="XaLabelList";
    XaLibAction::AddXmlFile(XmlPage);

	XaLibAction::SetLayout("Standard");

    string XslPage="XaLabelList";
    XaLibAction::AddXslFile(XslPage);

    XaLibDom* LibDom=new XaLibDom();
    xmlDocPtr XmlDomDoc=LibDom->DomFromStringAndFile(XmlFiles,XmlStrings,1);
    
    string XPathExprType;

	XPathExprType="/root/fieldset[@id='XaLabelList']/field[@name='XaDomain-XaLanguage']/options";
	XaLibAction::AddOptionsByDomain(LibDom,XmlDomDoc,"XaLanguage",XPathExprType);

	string XPB1="/root/fieldset[@id='XaLabelList']/";
	string r1 =XPB1+"field[@name='XaDomain-XaLanguage']/value";
	
	string ArrayXPathExpr1[] = {r1};
	vector<string> XPathExpr1(ArrayXPathExpr1, ArrayXPathExpr1+1);
		
	string s1 =StrLanguage;

	string ArrayXPathValue1[] = {s1};
	vector<string> XPathValue1(ArrayXPathValue1, ArrayXPathValue1+1);
	
	LibDom->UpdateElementValueByXPath(XmlDomDoc, XPathExpr1, XPathValue1);
		
	XPathExpr1.clear();
	XPathValue1.clear();
	
	xmlDocPtr XslDomDoc=LibDom->DomFromStringAndFile(XslFiles,XslStrings,2);

	delete(LibDom);

    const int MAXITEMS = 2;
    string XslParams[MAXITEMS] = {"a","b"};
    XaLibXsl *LibXsl=new XaLibXsl(XmlDomDoc,XslDomDoc,XslParams,MAXITEMS);
    RESPONSE.Content=LibXsl->GetXHtml();
	delete(LibXsl);

};

void XaLabel::XaLabelAddFrm (){

    string XmlPage="XaLabelAddFrm";
    XaLibAction::AddXmlFile(XmlPage);

	XaLibAction::SetLayout("Standard");

    string XslPage="XaLabelAddFrm";
    XaLibAction::AddXslFile(XslPage);

    XaLibDom* LibDom=new XaLibDom();
    xmlDocPtr XmlDomDoc=LibDom->DomFromStringAndFile(XmlFiles,XmlStrings,1);
    
    string XPathExprType;

	XPathExprType="/root/fieldset[@id='XaLabelAddFrm']/field[@name='XaDomain-XaLanguage']/options";
	XaLibAction::AddOptionsByDomain(LibDom,XmlDomDoc,"XaLanguage",XPathExprType);

	xmlDocPtr XslDomDoc=LibDom->DomFromStringAndFile(XslFiles,XslStrings,2);

	delete(LibDom);

    const int MAXITEMS = 2;
    string XslParams[MAXITEMS] = {"a","b"};
    XaLibXsl *LibXsl=new XaLibXsl(XmlDomDoc,XslDomDoc,XslParams,MAXITEMS);
    RESPONSE.Content=LibXsl->GetXHtml();
	delete(LibXsl);

};
*/
void XaLabel::Create (){
    
    XaLibBase::FieldsMap LoadedFields=CreatePrepare({"XaLabel"},"/XaLabel/fieldset/field");

	string StrName=HTTP.GetHttpParam("name");
	string StrDescription=HTTP.GetHttpParam("description");
	string StrLanguage=HTTP.GetHttpParam("XaLanguage_ID");
	string StrText=HTTP.GetHttpParam("text");
	string StrHelp=HTTP.GetHttpParam("help");
	string StrPlaceholder=HTTP.GetHttpParam("placeholder");

	unique_ptr<XaLibSql> LibSql (new XaLibSql());
        
        // se non esiste la lingua
        if (LibSql->CheckRow(DB_READ,"XaLanguage",StrLanguage,"1","")==0) {
            throw 302;
        }
        
        vector<string> VectorFields;
	VectorFields.push_back("name");
	VectorFields.push_back("description");
        VectorFields.push_back("status");

	vector<string> VectorValues;
	VectorValues.push_back(StrName);
	VectorValues.push_back(StrDescription);
        VectorValues.push_back("1");
	
	int NextId=LibSql->Insert(DB_WRITE,"XaLabel",VectorFields,VectorValues);

	VectorFields.clear();
        VectorValues.clear();
        
        bool FlowCheck=true;
        
        if (NextId!=0) {
        
            string LabelId=XaLibBase::FromIntToString(NextId);

            vector<string> ReturnedFields;
            ReturnedFields.push_back("*");

            vector<string> WhereFields;
            WhereFields.push_back("status");

            vector<string> WhereValues;
            WhereValues.push_back("1");

            DbResMap DbRes=LibSql->Select(DB_READ,"XaLanguage",ReturnedFields,WhereFields,WhereValues);

            ReturnedFields.clear();
            WhereFields.clear();
            WhereValues.clear();

            for(unsigned n=0; n<DbRes.size(); ++n){

                VectorFields.push_back("status");
                VectorValues.push_back("1");
                
                if (StrLanguage==DbRes[n]["id"]){ 

                    VectorFields.push_back("XaLabel_ID");
                    VectorFields.push_back("XaLanguage_ID");

                    VectorValues.push_back(LabelId);
                    VectorValues.push_back(DbRes[n]["id"]);

                    if (StrText!="" && StrText!="NoHttpParam"){
                        VectorFields.push_back("text");
                        VectorValues.push_back(StrText);
                    }
                    if (StrHelp!="" && StrHelp!="NoHttpParam"){
                        VectorFields.push_back("help");
                        VectorValues.push_back(StrHelp);
                    }
                    if (StrPlaceholder!="" && StrPlaceholder!="NoHttpParam"){
                        VectorFields.push_back("placeholder");
                        VectorValues.push_back(StrPlaceholder);
                    }

                } else {

                    VectorFields.push_back("XaLabel_ID");
                    VectorFields.push_back("XaLanguage_ID");

                    VectorValues.push_back(LabelId);
                    VectorValues.push_back(DbRes[n]["id"]);

                }

                int NextTranslationId=LibSql->Insert(DB_WRITE,"XaLabelTranslation",VectorFields,VectorValues);
                
                if (NextTranslationId==0) {
                    FlowCheck=false;
                }

                VectorFields.clear();
                VectorValues.clear();
            }
            
        }
	
	if (NextId!=0 && FlowCheck==true) {
            this->XaLabelGen();
        } else {
            NextId=0;
        }
	
	//RESPONSE.Content="Inserted Label: "+StrName+" - ID: " +LabelId;
        RESPONSE.Content=CreateResponse(NextId);

};

void XaLabel::Read (){
    
};

void XaLabel::Delete (){
    string Id=HTTP.GetHttpParam("id");
    // update XaLabel
    int DeletedId=DeleteExecute("XaLabel",Id);
    // update XaLabelTranslation
    XaLibSql::Update(DB_WRITE,"XaLabelTranslation",{"status"},{"4"},{"XaLabel_ID"},{Id});
    XaLabelGen();
    RESPONSE.Content=DeleteResponse(DeletedId);
};

void XaLabel::Update (){
    
};

/*
void XaLabel::XaTranslationAddFrm (){
	
	DbResMap DbRes;
	
	string XmlString;
	
	XaLibSql* LibSql=new XaLibSql();
	
	string qry="SELECT name,description FROM XaDomain WHERE domain = 'XaLanguage' AND active=1 ORDER BY id";
	
	DbRes=LibSql->FreeQuery(DB_READ,qry);
	
	XmlString="<language>";
	
	for(unsigned n=0; n<DbRes.size(); ++n){
		
		XmlString.append("<lang>");
		
			XmlString.append("<label>");
			XmlString.append(DbRes[n]["description"]);
			XmlString.append("</label>");
			
			XmlString.append("<code>");
			XmlString.append(DbRes[n]["name"]);
			XmlString.append("</code>");
		
		XmlString.append("</lang>");
		
	}
	
	XmlString.append("</language>");
	
	delete(LibSql);
	
	XaLibAction::AddXmlString(XmlString);

    string XmlPage="XaTranslationAddFrm";
    XaLibAction::AddXmlFile(XmlPage);

	XaLibAction::SetLayout("Standard");

    string XslPage="XaTranslationAddFrm";
    XaLibAction::AddXslFile(XslPage);

    XaLibDom* LibDom=new XaLibDom();
    xmlDocPtr XmlDomDoc=LibDom->DomFromStringAndFile(XmlFiles,XmlStrings,1);

	xmlDocPtr XslDomDoc=LibDom->DomFromStringAndFile(XslFiles,XslStrings,2);

	delete(LibDom);

    const int MAXITEMS = 2;
    string XslParams[MAXITEMS] = {"a","b"};
    XaLibXsl *LibXsl=new XaLibXsl(XmlDomDoc,XslDomDoc,XslParams,MAXITEMS);
    RESPONSE.Content=LibXsl->GetXHtml();
	delete(LibXsl);

};

void XaLabel::XaTranslationAdd (){
	
	string StrName=HTTP.GetHttpParam("XaLabel-Name");
	string StrDescription=HTTP.GetHttpParam("XaLabel-Description");

	vector<string> VectorFields;
	VectorFields.push_back("name");
	VectorFields.push_back("description");

	vector<string> VectorValues;
	VectorValues.push_back(StrName);
	VectorValues.push_back(StrDescription);

	XaLibSql* LibSql=new XaLibSql();
	
	int NextId=LibSql->Insert(DB_WRITE,"XaLabel",VectorFields,VectorValues);

	string LabelId=XaLibBase::FromIntToString(NextId);
	
	DbResMap DbRes;
	
	XaLibSql* LibSql1=new XaLibSql();
	
	string qry="SELECT id,name FROM XaDomain WHERE domain = 'XaLanguage' AND active=1 ORDER BY id";
	
	DbRes=LibSql1->FreeQuerySelect(DB_READ,qry);
	
	delete(LibSql1);
	
	for(unsigned n=0; n<DbRes.size(); ++n){

		string StrText=HTTP.GetHttpParam(DbRes[n]["name"]);
		string StrHelp=HTTP.GetHttpParam("help"+DbRes[n]["name"]);
		string StrPlaceholder=HTTP.GetHttpParam("ph"+DbRes[n]["name"]);
		
		vector<string> VectorFields1;
		VectorFields1.push_back("XaLabel_ID");
		VectorFields1.push_back("XaDomain_ID");
		VectorFields1.push_back("text");
		VectorFields1.push_back("help");
		VectorFields1.push_back("placeholder");

		vector<string> VectorValues1;
		VectorValues1.push_back(LabelId);
		VectorValues1.push_back(DbRes[n]["id"]);
		VectorValues1.push_back(StrText);
		VectorValues1.push_back(StrHelp);
		VectorValues1.push_back(StrPlaceholder);

		LibSql->Insert(DB_WRITE,"XaLabelTranslation",VectorFields1,VectorValues1);

	}
	
	delete(LibSql);
	
	this->XaLabelGen();
};
*/
void XaLabel::XaLabelGen (){

	DbResMap DbRes;
	DbResMap DbRes1;

	string XmlString;

	unique_ptr<XaLibSql> LibSql (new XaLibSql());
	vector<string> ReturnedFields;
	ReturnedFields.push_back("*");

	vector<string> WhereFields;
	WhereFields.push_back("status");

	vector<string> WhereValues;
	WhereValues.push_back("1");

	DbRes=LibSql->Select(DB_READ,"XaLanguage",ReturnedFields,WhereFields,WhereValues);

	for(unsigned n=0; n<DbRes.size(); ++n){
		
		string FileName="XaLabel-"+DbRes[n]["name"];
		string FilePath=SETTINGS["SharedDir"]+"xml/"+FileName+".xml";
		
		string qry1="SELECT XaLabel_ID,XaLanguage_ID,text,help,placeholder,name,description FROM XaLabelTranslation t,XaLabel l WHERE t.XaLabel_id=l.id AND l.status=1 AND XaLanguage_ID=";
		qry1.append(DbRes[n]["id"]);

		DbRes1=LibSql->FreeQuerySelect(DB_READ,qry1);

		XmlString="<labels>";

		for(unsigned i=0; i<DbRes1.size(); ++i){

			XmlString.append("<label name=\""+DbRes1[i]["name"]+"\" id=\""+DbRes1[i]["XaLabel_ID"]+"\">");

				XmlString.append("<disp>");
				XmlString.append(DbRes1[i]["text"]);
				XmlString.append("</disp>");
			
				XmlString.append("<placeholder>");
				XmlString.append(DbRes1[i]["placeholder"]);
				XmlString.append("</placeholder>");
				
				XmlString.append("<help>");
				XmlString.append(DbRes1[i]["help"]);
				XmlString.append("</help>");
			
			XmlString.append("</label>");
		}
		
		XmlString.append("</labels>");
		
		const char* FilePathChar = FilePath.c_str();
		ofstream myfile;
		myfile.open (FilePathChar);
		myfile << XmlString;
		myfile.close();
	}
	
	RESPONSE.Content="<xml_label_gen>ok</xml_label_gen>";
};


XaLabel::~XaLabel(){
};                          
