#include <XaUserAddressMailType.h>
#include <XaLibModel.h>


XaUserAddressMailType::XaUserAddressMailType(){
};

void XaUserAddressMailType::Dispatcher (const string &CalledEvent) {

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

void XaUserAddressMailType::Create() {

	XaLibBase::FieldsMap LoadedFields=CreatePrepare({"XaUserAddressMailType"},"/XaUserAddressMailType/fieldset/field");
	RESPONSE.Content=CreateResponse(CreateExecute("XaUserAddressMailType",LoadedFields));
};

void XaUserAddressMailType::Read() {

	vector<string> FieldsToRead = XaLibModel::ReadPrepare({"XaUserAddressMailType"},"/XaUserAddressMailType/fieldset/field");
	
	DbResMap DbRes=XaLibSql::Select(DB_READ,"XaUserAddressMailType",FieldsToRead,{"id"},{HTTP.GetHttpParam("id")});
	RESPONSE.Content= ReadResponse(DbRes,FieldsToRead);
};

void XaUserAddressMailType::List() {

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

	vector<string> ReturnedFields=ListPrepare({"XaUserAddressMailType"},"/XaUserAddressMailType/fieldset/field");

	DbResMap DbRes=XaLibSql::Select(DB_READ,"XaUserAddressMailType",{ReturnedFields},{WhereFields}, {WhereValues}, {OrderByFields},{GroupByFields},Limit);
	RESPONSE.Content=ListResponse(DbRes,ReturnedFields);	
	//Quali campi
	//
	/*
	vector<string> FieldsToRead = XaLibModel::ReadPrepare({"XaUserAddressMailType"},"/XaUserAddressMailType/fieldset/field");
	DbResMap DbRes = ReadExecute("XaUserAddressMailType",FieldsToRead,HTTP.GetHttpParam("id"));
	RESPONSE.Content= ReadResponse(DbRes,FieldsToRead);
	*/
};

void XaUserAddressMailType::ListAsOptions() {

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

	DbResMap DbRes=XaLibSql::Select(DB_READ,"XaUserAddressMailType",{ReturnedFields},{WhereFields}, {WhereValues}, {OrderByFields},{GroupByFields},Limit);
	RESPONSE.Content=ListResponse(DbRes,ReturnedFields);
};

void XaUserAddressMailType::Update() {

	BackupRecord("XaUserAddressMailType",50);

	/*
	XaLibBase::FieldsMap LoadedFields=UpdatePrepare({"XaUserAddressMailType"},"/XaUserAddressMailType/fieldset/field");
	RESPONSE.Content=CreateResponse(UpdateExecute("XaUserAddressMailType",LoadedFields));*/
};

void XaUserAddressMailType::Delete() {

	int DeletedId=DeleteExecute("XaUserAddressMailType",HTTP.GetHttpParam("id"));
	RESPONSE.Content=DeleteResponse(DeletedId);
};

XaUserAddressMailType::~XaUserAddressMailType(){
};