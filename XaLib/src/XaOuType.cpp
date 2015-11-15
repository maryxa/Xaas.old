#include <XaOuType.h>
#include <XaLibModel.h>


XaOuType::XaOuType(){
};

void XaOuType::Dispatcher (const string &CalledEvent) {

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

void XaOuType::Create() {

	XaLibBase::FieldsMap LoadedFields=CreatePrepare({"XaOuType"},"/XaOuType/fieldset/field");
	RESPONSE.Content=CreateResponse(CreateExecute("XaOuType",LoadedFields));
};

void XaOuType::Read() {

	vector<string> FieldsToRead = XaLibModel::ReadPrepare({"XaOuType"},"/XaOuType/fieldset/field");
	DbResMap DbRes = ReadExecute("XaOuType",FieldsToRead,HTTP.GetHttpParam("id"));
	RESPONSE.Content= ReadResponse(DbRes,FieldsToRead);
};

void XaOuType::List() {

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

	vector<string> ReturnedFields=ListPrepare({"XaOuType"},"/XaOuType/fieldset/field");

	ReturnedFields.push_back("id");
	ReturnedFields.push_back("old_id");
	ReturnedFields.push_back("created");
	ReturnedFields.push_back("updated");
	ReturnedFields.push_back("status");
	
	DbResMap DbRes=XaLibSql::Select(DB_READ,"XaOuType",{ReturnedFields},{WhereFields}, {WhereValues}, {OrderByFields},{GroupByFields},Limit);
	RESPONSE.Content=ListResponse(DbRes,ReturnedFields);	
	//Quali campi
	//
	/*
	vector<string> FieldsToRead = XaLibModel::ReadPrepare({"XaOuType"},"/XaOuType/fieldset/field");
	DbResMap DbRes = ReadExecute("XaOuType",FieldsToRead,HTTP.GetHttpParam("id"));
	RESPONSE.Content= ReadResponse(DbRes,FieldsToRead);
	*/
};

void XaOuType::Update(){

	XaLibBase::FieldsMap LoadedFields=UpdatePrepare({"XaOuType"},"/XaOuType/fieldset/field");
	RESPONSE.Content=CreateResponse(UpdateExecute("XaOuType",LoadedFields));
};

void XaOuType::Delete(){

	int DeletedId=DeleteExecute("XaOuType",HTTP.GetHttpParam("id"));
	RESPONSE.Content=DeleteResponse(DeletedId);
};



/*

XaOuModel::Update(){
};



XaOuModel::XaOuModel(){
};
*/
XaOuType::~XaOuType(){
};