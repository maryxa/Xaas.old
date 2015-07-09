#include <XaLanguage.h>
#include <XaLibAction.h>

XaLanguage::XaLanguage(){

};

void XaLanguage::Dispatcher(const string &CalledEvent) {

	if (CalledEvent=="XaLanguageAddFrm"){
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
};

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
    xmlDocPtr XmlDomDoc=LibDom->DomFromStringAndFile(XmlFilePaths,XmlStrings,1);

	xmlDocPtr XslDomDoc=LibDom->DomFromStringAndFile(XslFilePaths,XslStrings,2);

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
    xmlDocPtr XmlDomDoc=LibDom->DomFromStringAndFile(XmlFilePaths,XmlStrings,1);

	xmlDocPtr XslDomDoc=LibDom->DomFromStringAndFile(XslFilePaths,XslStrings,2);

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
	
	DbRes=LibSql1->FreeQuery(DB_READ,qry);
	
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

void XaLanguage::XaLanguageGen (){

	DbResMap DbRes;
	
	string XmlString;

	XaLibSql* LibSql=new XaLibSql();

	vector<string> ReturnedFields;
	ReturnedFields.push_back("*");

	vector<string> WhereFields;
	WhereFields.push_back("domain");
	WhereFields.push_back("active");

	vector<string> WhereValues;
	WhereValues.push_back("XaLanguage");
	WhereValues.push_back("1");

	DbRes=LibSql->Select(DB_READ,"XaDomain",ReturnedFields,WhereFields,WhereValues);
	
	delete(LibSql);
	
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
		
	string FileName="XaLanguage";
	string FilePath=SETTINGS["XmlDir"]+FileName+".xml";
	
	const char* FilePathChar = FilePath.c_str();
	ofstream myfile;
	myfile.open (FilePathChar);
	myfile << XmlString;
	myfile.close();
	
};

XaLanguage::~XaLanguage(){
};
