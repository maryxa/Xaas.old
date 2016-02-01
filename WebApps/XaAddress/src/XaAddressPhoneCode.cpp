#include <XaAddressPhoneCode.h>
#include <XaLibModel.h>


XaAddressPhoneCode::XaAddressPhoneCode(){
};

void XaAddressPhoneCode::Dispatcher (const string &CalledEvent) {

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

void XaAddressPhoneCode::Create() {

	XaLibBase::FieldsMap LoadedFields=CreatePrepare({"XaAddressPhoneCode"},"/XaAddressPhoneCode/fieldset/field");
	RESPONSE.Content=CreateResponse(CreateExecute("XaAddressPhoneCode",LoadedFields));
};

void XaAddressPhoneCode::Read() {

	vector<string> FieldsToRead = XaLibModel::ReadPrepare({"XaAddressPhoneCode"},"/XaAddressPhoneCode/fieldset/field");
	
	DbResMap DbRes=XaLibSql::Select(DB_READ,"XaAddressPhoneCode",FieldsToRead,{"id"},{HTTP.GetHttpParam("id")});
	RESPONSE.Content= ReadResponse(DbRes,FieldsToRead);
};

void XaAddressPhoneCode::List() {

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

	vector<string> ReturnedFields=ListPrepare({"XaAddressPhoneCode"},"/XaAddressPhoneCode/fieldset/field");

	DbResMap DbRes=XaLibSql::Select(DB_READ,"XaAddressPhoneCode",{ReturnedFields},{WhereFields}, {WhereValues}, {OrderByFields},{GroupByFields},Limit);
	RESPONSE.Content=ListResponse(DbRes,ReturnedFields);	
	//Quali campi
	//
	/*
	vector<string> FieldsToRead = XaLibModel::ReadPrepare({"XaAddressPhoneCode"},"/XaAddressPhoneCode/fieldset/field");
	DbResMap DbRes = ReadExecute("XaAddressPhoneCode",FieldsToRead,HTTP.GetHttpParam("id"));
	RESPONSE.Content= ReadResponse(DbRes,FieldsToRead);
	*/
};

void XaAddressPhoneCode::ListAsOptions() {

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

	DbResMap DbRes=XaLibSql::Select(DB_READ,"XaAddressPhoneCode",{ReturnedFields},{WhereFields}, {WhereValues}, {OrderByFields},{GroupByFields},Limit);
	RESPONSE.Content=ListResponse(DbRes,ReturnedFields);
};

void XaAddressPhoneCode::Update() {

	BackupRecord("XaAddressPhoneCode",50);

	/*
	XaLibBase::FieldsMap LoadedFields=UpdatePrepare({"XaAddressPhoneCode"},"/XaAddressPhoneCode/fieldset/field");
	RESPONSE.Content=CreateResponse(UpdateExecute("XaAddressPhoneCode",LoadedFields));*/
};

void XaAddressPhoneCode::Delete() {

	int DeletedId=DeleteExecute("XaAddressPhoneCode",HTTP.GetHttpParam("id"));
	RESPONSE.Content=DeleteResponse(DeletedId);
};

XaAddressPhoneCode::~XaAddressPhoneCode(){
};