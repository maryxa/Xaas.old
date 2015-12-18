#include <XaLabelTranslation.h>
#include <XaLibModel.h>
#include <XaLabel.h>


XaLabelTranslation::XaLabelTranslation(){
};

void XaLabelTranslation::Dispatcher (const string &CalledEvent) {

    if (CalledEvent=="Create"){
        this->Create();
    } else if (CalledEvent=="Read"){
        this->Read();
    } else if (CalledEvent=="List"){
	this->List();
    } else if (CalledEvent=="Update"){
	this->Update();
    } else if (CalledEvent=="Delete"){
	this->Delete();
    } else {

	LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"ERROR-42 Requested Event Does Not Exists -> "+CalledEvent);
	throw 42;
    }
};

void XaLabelTranslation::Create (){
    
    XaLibBase::FieldsMap LoadedFields=CreatePrepare({"XaLabelTranslation"},"/XaLabelTranslation/fieldset/field");

    string StrLabelId=HTTP.GetHttpParam("XaLabel_ID");
    string StrLanguageId=HTTP.GetHttpParam("XaLanguage_ID");
    string StrText=HTTP.GetHttpParam("text");
    string StrHelp=HTTP.GetHttpParam("help");
    string StrPlaceholder=HTTP.GetHttpParam("placeholder");

    unique_ptr<XaLibSql> LibSql (new XaLibSql());
    int Add=0;
    int DbResLabelTranslationSize=1;
    int TranslationId=0;
    
    // controllo che esista e sia attiva la lingua
    int CheckLanguage=LibSql->CheckRow(DB_READ,"XaLanguage",StrLanguageId,"1","");

    // controllo che esista e sia attiva la label
    int CheckLabel=LibSql->CheckRow(DB_READ,"XaLabel",StrLabelId,"1","");

    // se non esiste la lingua o la label
    if (CheckLanguage==0 || CheckLabel==0) {
        throw 302;
    }
    
    // controllo che la traduzione non sia gia esistente
    string qry1="SELECT id FROM XaLabelTranslation WHERE status=1 AND XaLabel_id="+StrLabelId+" AND XaLanguage_ID="+StrLanguageId;
    DbResMap DbResLabelTranslation1=LibSql->FreeQuerySelect(DB_READ,qry1);

    if (DbResLabelTranslation1.size()==0) {
        Add=1;
    } else {
        string qry2="SELECT id FROM XaLabelTranslation WHERE status=1 AND XaLabel_id="+StrLabelId+" AND XaLanguage_ID="+StrLanguageId+" AND text IS NULL";
        DbResMap DbResLabelTranslation2=LibSql->FreeQuerySelect(DB_READ,qry2);

        DbResLabelTranslationSize=DbResLabelTranslation2.size();
        TranslationId=FromStringToInt(DbResLabelTranslation2[0]["id"]);
    }

    // se traduzione gia esistente
    if (DbResLabelTranslationSize==0) {
        throw 303;
    }

    vector<string> VectorFields;
    vector<string> VectorValues;

    if (Add==1) {

        VectorFields.push_back("status");
        VectorValues.push_back("1");

        VectorFields.push_back("XaLabel_ID");
        VectorFields.push_back("XaLanguage_ID");

        VectorValues.push_back(StrLabelId);
        VectorValues.push_back(StrLanguageId);

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

        TranslationId=LibSql->Insert(DB_WRITE,"XaLabelTranslation",VectorFields,VectorValues);

        VectorFields.clear();
        VectorValues.clear();

    } else {

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

        if(LibSql->Update(DB_WRITE,"XaLabelTranslation",VectorFields,VectorValues,{"id"},{FromIntToString(TranslationId)})==0) {
            TranslationId=0;
        }

        VectorFields.clear();
        VectorValues.clear();

    }

    if (TranslationId!=0) {

        unique_ptr<XaLabel> Label (new XaLabel());
        Label->XaLabelGen();

    }

    RESPONSE.Content=CreateResponse(TranslationId);

};

void XaLabelTranslation::Read() {

	vector<string> FieldsToRead = XaLibModel::ReadPrepare({"XaLabelTranslation"},"/XaLabelTranslation/fieldset/field");
	
	DbResMap DbRes=XaLibSql::Select(DB_READ,"XaLabelTranslation",FieldsToRead,{"id"},{HTTP.GetHttpParam("id")});
	RESPONSE.Content= ReadResponse(DbRes,FieldsToRead);
};

void XaLabelTranslation::List() {

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

	vector<string> ReturnedFields=ListPrepare({"XaLabelTranslation"},"/XaLabelTranslation/fieldset/field");

	DbResMap DbRes=XaLibSql::Select(DB_READ,"XaLabelTranslation",{ReturnedFields},{WhereFields}, {WhereValues}, {OrderByFields},{GroupByFields},Limit);
	RESPONSE.Content=ListResponse(DbRes,ReturnedFields);	
	//Quali campi
	//
	/*
	vector<string> FieldsToRead = XaLibModel::ReadPrepare({"XaLabelTranslation"},"/XaLabelTranslation/fieldset/field");
	DbResMap DbRes = ReadExecute("XaLabelTranslation",FieldsToRead,HTTP.GetHttpParam("id"));
	RESPONSE.Content= ReadResponse(DbRes,FieldsToRead);
	*/
};

void XaLabelTranslation::Update() {

	BackupRecord("XaLabelTranslation",50);

	/*
	XaLibBase::FieldsMap LoadedFields=UpdatePrepare({"XaLabelTranslation"},"/XaLabelTranslation/fieldset/field");
	RESPONSE.Content=CreateResponse(UpdateExecute("XaLabelTranslation",LoadedFields));*/
};

void XaLabelTranslation::Delete() {

	int DeletedId=DeleteExecute("XaLabelTranslation",HTTP.GetHttpParam("id"));
	RESPONSE.Content=DeleteResponse(DeletedId);
};

XaLabelTranslation::~XaLabelTranslation(){
};