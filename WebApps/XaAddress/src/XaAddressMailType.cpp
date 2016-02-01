#include <XaAddressMailType.h>
#include <XaLibModel.h>


XaAddressMailType::XaAddressMailType(){
};

void XaAddressMailType::Dispatcher (const string &CalledEvent) {

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
    } else {
	LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"ERROR-42 Requested Event Does Not Exists -> "+CalledEvent);
	throw 42;
    }
};

void XaAddressMailType::Create() {

	XaLibBase::FieldsMap LoadedFields=CreatePrepare({"XaAddressMailType"},"/XaAddressMailType/fieldset/field");
	RESPONSE.Content=CreateResponse(CreateExecute("XaAddressMailType",LoadedFields));
};

void XaAddressMailType::Read() {

	vector<string> FieldsToRead = XaLibModel::ReadPrepare({"XaAddressMailType"},"/XaAddressMailType/fieldset/field");
	
	DbResMap DbRes=XaLibSql::Select(DB_READ,"XaAddressMailType",FieldsToRead,{"id"},{HTTP.GetHttpParam("id")});
	RESPONSE.Content= ReadResponse(DbRes,FieldsToRead);
};

void XaAddressMailType::List() {

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

	vector<string> ReturnedFields=ListPrepare({"XaAddressMailType"},"/XaAddressMailType/fieldset/field");

	DbResMap DbRes=XaLibSql::Select(DB_READ,"XaAddressMailType",{ReturnedFields},{WhereFields}, {WhereValues}, {OrderByFields},{GroupByFields},Limit);
	RESPONSE.Content=ListResponse(DbRes,ReturnedFields);	
	//Quali campi
	//
	/*
	vector<string> FieldsToRead = XaLibModel::ReadPrepare({"XaAddressMailType"},"/XaAddressMailType/fieldset/field");
	DbResMap DbRes = ReadExecute("XaAddressMailType",FieldsToRead,HTTP.GetHttpParam("id"));
	RESPONSE.Content= ReadResponse(DbRes,FieldsToRead);
	*/
};

void XaAddressMailType::ListAsOptions() {

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

	DbResMap DbRes=XaLibSql::Select(DB_READ,"XaAddressMailType",{ReturnedFields},{WhereFields}, {WhereValues}, {OrderByFields},{GroupByFields},Limit);
	RESPONSE.Content=ListResponse(DbRes,ReturnedFields);
};

void XaAddressMailType::Update() {

	BackupRecord("XaAddressMailType",50);

	/*
	XaLibBase::FieldsMap LoadedFields=UpdatePrepare({"XaAddressMailType"},"/XaAddressMailType/fieldset/field");
	RESPONSE.Content=CreateResponse(UpdateExecute("XaAddressMailType",LoadedFields));*/
};

void XaAddressMailType::Delete() {

	int DeletedId=DeleteExecute("XaAddressMailType",HTTP.GetHttpParam("id"));
	RESPONSE.Content=DeleteResponse(DeletedId);
};

XaAddressMailType::~XaAddressMailType(){
};