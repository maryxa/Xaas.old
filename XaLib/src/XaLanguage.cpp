#include <XaLanguage.h>
//#include <XaLibAction.h>
#include <XaLibModel.h>

XaLanguage::XaLanguage(){

};

void XaLanguage::Dispatcher(const string &CalledEvent) {

    /*	if (CalledEvent=="XaLanguageAddFrm"){
        this->XaLanguageAddFrm();
	} else if (CalledEvent=="XaLanguageAdd"){
        this->XaLanguageAdd();
	} else if (CalledEvent=="XaLanguageGen"){
        this->XaLanguageGen();
	} else if (CalledEvent=="XaLanguageList"){
        this->XaLanguageList();
	} else if (CalledEvent=="XaLanguageMod"){
        this->XaLanguageMod();
	}
    */
    if (CalledEvent=="Create"){
        this->Create();
    } else if (CalledEvent=="Read"){
        this->Read();
    } else if (CalledEvent=="List"){
	this->List();
    } else if (CalledEvent=="ListAsOptions"){
        this->ListAsOptions();
    } else if (CalledEvent=="Update"){
	this->Update();
    } else if (CalledEvent=="Delete"){
	this->Delete();
    } else if (CalledEvent=="XaLanguageGen"){
        this->XaLanguageGen();
    } else {
        LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"ERROR-42 Requested Event Does Not Exists -> "+CalledEvent);
        throw 42;
    }
    
};

void XaLanguage::Create() {

	vector<string> FieldName;	
	vector<string> FieldValue;

	CreatePrepare({"XaLanguage"},"/XaLanguage/fieldset/field",FieldName,FieldValue);
	
        int NextId=CreateExecute("XaLanguage",FieldName,FieldValue);
        
        if (NextId!=0) {
	
            unique_ptr<XaLibSql> LibSql (new XaLibSql());

            string qry="SELECT XaLabel_ID FROM XaLabelTranslation, XaLabel WHERE XaLanguage_ID NOT IN ("+FromIntToString(NextId)+") AND XaLabel_id=XaLabel.id GROUP BY XaLabel_ID";

            DbResMap DbRes=LibSql->FreeQuerySelect(DB_READ,qry);

            for(unsigned n=0; n<DbRes.size(); ++n){

                    vector<string> VectorFields;
                    VectorFields.push_back("XaLabel_ID");
                    VectorFields.push_back("XaLanguage_ID");

                    vector<string> VectorValues;
                    VectorValues.push_back(DbRes[n]["XaLabel_ID"]);
                    VectorValues.push_back(FromIntToString(NextId));

                    LibSql->Insert(DB_WRITE,"XaLabelTranslation",VectorFields,VectorValues);
                    
                    VectorFields.clear();
                    VectorValues.clear();

            }

            XaLanguageGen();
            
        }
        
        RESPONSE.Content=CreateResponse(NextId);
};

void XaLanguage::Read() {

	vector<string> FieldsToRead = XaLibModel::ReadPrepare({"XaLanguage"},"/XaLanguage/fieldset/field");
	
	DbResMap DbRes=XaLibSql::Select(DB_READ,"XaLanguage",FieldsToRead,{"id"},{HTTP.GetHttpParam("id")});
	RESPONSE.Content= ReadResponse(DbRes,FieldsToRead);
};

void XaLanguage::List() {

	vector<string> WhereFields={};
	vector<string> WhereValues={};
	vector<string> OrderByFields={};
	vector<string> GroupByFields={};

	string PassedLimit=HTTP.GetHttpParam("limit");
	int Limit={0};

	if (PassedLimit!="NoHttpParam") {
		Limit=FromStringToInt(PassedLimit);
	};

	string OrderBy=HTTP.GetHttpParam("order_by");
	string Status=HTTP.GetHttpParam("status");

	vector<string> ReturnedFields=ListPrepare({"XaLanguage"},"/XaLanguage/fieldset/field");

	DbResMap DbRes=XaLibSql::Select(DB_READ,"XaLanguage",{ReturnedFields},{WhereFields}, {WhereValues}, {OrderByFields},{GroupByFields},Limit);
	RESPONSE.Content=ListResponse(DbRes,ReturnedFields);	
	//Quali campi
	//
	/*
	vector<string> FieldsToRead = XaLibModel::ReadPrepare({"XaLanguage"},"/XaLanguage/fieldset/field");
	DbResMap DbRes = ReadExecute("XaLanguage",FieldsToRead,HTTP.GetHttpParam("id"));
	RESPONSE.Content= ReadResponse(DbRes,FieldsToRead);
	*/
};

void XaLanguage::ListAsOptions() {

	vector<string> WhereFields={};
	vector<string> WhereValues={};
	vector<string> OrderByFields={};
	vector<string> GroupByFields={};

	/*LIMIT*/
	string PassedLimit=HTTP.GetHttpParam("limit");
	int Limit={0};

	if (PassedLimit!="NoHttpParam") {
		Limit=FromStringToInt(PassedLimit);
	};

	/*ORDER BY*/
	string PassedOrderBy=HTTP.GetHttpParam("order_by");
	
	if (PassedOrderBy!="NoHttpParam") {
	
		OrderByFields.push_back(PassedOrderBy);
	};
	
	/*STATUS*/
	string PassedStatus=HTTP.GetHttpParam("status");
	
	if (PassedStatus!="NoHttpParam") {

		WhereFields.push_back("status");
		WhereValues.push_back(PassedStatus);
	};

	vector<string> ReturnedFields={"id","name"};

	DbResMap DbRes=XaLibSql::Select(DB_READ,"XaLanguage",{ReturnedFields},{WhereFields}, {WhereValues}, {OrderByFields},{GroupByFields},Limit);
	RESPONSE.Content=ListResponse(DbRes,ReturnedFields);
};

void XaLanguage::Update() {
/*
	string Id=HTTP.GetHttpParam("id");
	int UpdateId=XaLibBase::FromStringToInt(Id);

 	vector<string> FieldName;
	vector<string> FieldValue;

	UpdatePrepare({"XaLanguage"},"/XaLanguage/fieldset/field",FieldName,FieldValue);

	int Updated=UpdateExecute("XaLanguage",FieldName,FieldValue,UpdateId);	
	
	RESPONSE.Content=UpdateResponse(Updated);
*/
};

void XaLanguage::Delete() {

	int DeletedId=DeleteExecute("XaLanguage",HTTP.GetHttpParam("id"));
	XaLanguageGen();
        RESPONSE.Content=DeleteResponse(DeletedId);
};

/*
void XaLanguage::XaLanguageMod (){

	XaLibSql* LibSql=new XaLibSql();
	
	DbResMap DbRes1;
	
	XaLibSql* LibSql1=new XaLibSql();
	
	vector<string> ReturnedFields1;
	ReturnedFields1.push_back("*");

	vector<string> WhereFields1;
	WhereFields1.push_back("1");

	vector<string> WhereValues1;
	WhereValues1.push_back("1");
	
	DbRes1=LibSql1->Select(DB_READ,"XaLanguage",ReturnedFields1,WhereFields1,WhereValues1);
	
	delete(LibSql1);
	
	for(unsigned n=0; n<DbRes1.size(); ++n){

		string StrText=HTTP.GetHttpParam(DbRes1[n]["code"]);
		string StrHelp=HTTP.GetHttpParam("help"+DbRes1[n]["code"]);
		string StrPlaceholder=HTTP.GetHttpParam("ph"+DbRes1[n]["code"]);
		string LabelId=HTTP.GetHttpParam("id");
		
		if (StrText!="" or StrHelp!="" or StrPlaceholder!=""){
		
			vector<string> VectorFields;
			vector<string> VectorValues;
			
			if (StrText!=""){
				VectorFields.push_back("text");
				VectorValues.push_back(StrText);
			}
			if (StrHelp!=""){
				VectorFields.push_back("help");
				VectorValues.push_back(StrHelp);
			}
			if (StrPlaceholder!=""){
				VectorFields.push_back("placeholder");
				VectorValues.push_back(StrPlaceholder);
			}
			
			vector<string> WhereFields;
			WhereFields.push_back("XaLabel_ID");
			WhereFields.push_back("XaLanguage_ID");
		
			vector<string> WhereValues;
			WhereValues.push_back(LabelId);
			WhereValues.push_back(DbRes1[n]["id"]);
	
			LibSql->Update(DB_WRITE,"XaLabelTranslation",VectorFields,VectorValues,WhereFields,WhereValues);

		}
	}
	
	delete(LibSql);
	
	this->XaLanguageGen();

};

void XaLanguage::XaLanguageList (){
	
	DbResMap DbRes;
	
	string XmlString;
	
	XaLibSql* LibSql=new XaLibSql();
	
	vector<string> ReturnedFields;
	ReturnedFields.push_back("*");

	vector<string> WhereFields;
	WhereFields.push_back("domain");

	vector<string> WhereValues;
	WhereValues.push_back("XaLanguage");
	
	DbRes=LibSql->Select(DB_READ,"XaDomain",ReturnedFields,WhereFields,WhereValues);

	
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
			XmlString.append("active");
			XmlString.append("</label>");
		XmlString.append("</title>");
		XmlString.append("<title>");
			XmlString.append("<label>");
			XmlString.append("deleted");
			XmlString.append("</label>");
		XmlString.append("</title>");
	
	XmlString.append("</titles>");
	
	XmlString.append("<fieldset>");
	
		for(unsigned n=0; n<DbRes.size(); ++n){

			XmlString.append("<field name=\""+DbRes[n]["name"]+"\" id=\""+DbRes[n]["id"]+"\">");

				XmlString.append("<id>");
				XmlString.append(DbRes[n]["id"]);
				XmlString.append("</id>");

				XmlString.append("<name>");
				XmlString.append(DbRes[n]["name"]);
				XmlString.append("</name>");
				
				XmlString.append("<description>");
				XmlString.append(DbRes[n]["description"]);
				XmlString.append("</description>");
				
				XmlString.append("<active>");
				XmlString.append(DbRes[n]["active"]);
				XmlString.append("</active>");
				
				XmlString.append("<deleted>");
				XmlString.append(DbRes[n]["deleted"]);
				XmlString.append("</deleted>");
			
			XmlString.append("</field>");
		
		}
		
	XmlString.append("</fieldset>");
	
	delete(LibSql);
	
	XaLibAction::AddXmlString(XmlString);

    string XmlPage="XaLanguageList";
    XaLibAction::AddXmlFile(XmlPage);

	XaLibAction::SetLayout("Standard");

    string XslPage="XaLanguageList";
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

void XaLanguage::XaLanguageAddFrm (){

    string XmlPage="XaLanguageAddFrm";
    XaLibAction::AddXmlFile(XmlPage);

	XaLibAction::SetLayout("Standard");

    string XslPage="XaLanguageAddFrm";
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

void XaLanguage::XaLanguageAdd (){
	
	typedef map<string, string> ParamsConfigurationMap;
	ParamsConfigurationMap LocalParamsConfiguration;

	string StrLanguage=HTTP.GetHttpParam("language");
	string StrCode=HTTP.GetHttpParam("code");

	XaLibTime* LibTime=new XaLibTime();
    string now=LibTime->GetDateTimeMySql();
	
	vector<string> VectorFields;
	VectorFields.push_back("domain");
	VectorFields.push_back("description");
	VectorFields.push_back("name");
	VectorFields.push_back("active");
	VectorFields.push_back("deleted");
	VectorFields.push_back("created");
	VectorFields.push_back("last_updated");

	vector<string> VectorValues;
	VectorValues.push_back("XaLanguage");
	VectorValues.push_back(StrLanguage);
	VectorValues.push_back(StrCode);
	VectorValues.push_back("1");
	VectorValues.push_back("0");
	VectorValues.push_back(now);
	VectorValues.push_back(now);

	XaLibSql* LibSql=new XaLibSql();
	
	int NextId=LibSql->Insert(DB_WRITE,"XaDomain",VectorFields,VectorValues);

	string LanguageId=XaLibBase::FromIntToString(NextId);
	
	DbResMap DbRes;
	
	XaLibSql* LibSql1=new XaLibSql();
	
	string qry="SELECT XaLabel_ID FROM XaLabelTranslation, XaLabel WHERE XaDomain_ID NOT IN (";
	qry.append(LanguageId);
	qry.append(") AND XaLabel_id=XaLabel.id GROUP BY XaLabel_ID");
	
	DbRes=LibSql1->FreeQuerySelect(DB_READ,qry);
	
	delete(LibSql1);
	
	for(unsigned n=0; n<DbRes.size(); ++n){

		vector<string> VectorFields1;
		VectorFields1.push_back("XaLabel_ID");
		VectorFields1.push_back("XaDomain_ID");

		vector<string> VectorValues1;
		VectorValues1.push_back(DbRes[n]["XaLabel_ID"]);
		VectorValues1.push_back(LanguageId);

		LibSql->Insert(DB_WRITE,"XaLabelTranslation",VectorFields1,VectorValues1);

	}
	
	delete(LibSql);
	
	this->XaLanguageGen();

};
*/
void XaLanguage::XaLanguageGen (){
	
	string XmlString;

	unique_ptr<XaLibSql> LibSql (new XaLibSql());

	vector<string> ReturnedFields;
	ReturnedFields.push_back("*");

	vector<string> WhereFields;
	WhereFields.push_back("status");

	vector<string> WhereValues;
	WhereValues.push_back("1");

	DbResMap DbRes=LibSql->Select(DB_READ,"XaLanguage",ReturnedFields,WhereFields,WhereValues);
	
		XmlString="<languages>";
	
		for(unsigned n=0; n<DbRes.size(); ++n){

			XmlString.append("<language name=\""+DbRes[n]["name"]+"\" id=\""+DbRes[n]["id"]+"\">");

				XmlString.append("<id>");
				XmlString.append(DbRes[n]["id"]);
				XmlString.append("</id>");

				XmlString.append("<name>");
				XmlString.append(DbRes[n]["description"]);
				XmlString.append("</name>");
				
				XmlString.append("<code>");
				XmlString.append(DbRes[n]["name"]);
				XmlString.append("</code>");
			
			XmlString.append("</language>");
		
		}
		
		XmlString.append("</languages>");
		
	string FileName="XaLanguage-list";
	string FilePath=SETTINGS["SharedDir"]+"xml/"+FileName+".xml";
	
	const char* FilePathChar = FilePath.c_str();
	ofstream myfile;
	myfile.open (FilePathChar);
	myfile << XmlString;
	myfile.close();
	
        RESPONSE.Content="<xml_language_gen>ok</xml_language_gen>";
};

XaLanguage::~XaLanguage(){
};
