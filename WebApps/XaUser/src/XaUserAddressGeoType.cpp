#include <XaUserAddressGeoType.h>
#include <XaLibModel.h>


XaUserAddressGeoType::XaUserAddressGeoType(){
};

void XaUserAddressGeoType::Dispatcher (const string &CalledEvent) {

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

void XaUserAddressGeoType::Create() {

	XaLibBase::FieldsMap LoadedFields=CreatePrepare({"XaUserAddressGeoType"},"/XaUserAddressGeoType/fieldset/field");
	RESPONSE.Content=CreateResponse(CreateExecute("XaUserAddressGeoType",LoadedFields));
};

void XaUserAddressGeoType::Read() {

	vector<string> FieldsToRead = XaLibModel::ReadPrepare({"XaUserAddressGeoType"},"/XaUserAddressGeoType/fieldset/field");
	
	DbResMap DbRes=XaLibSql::Select(DB_READ,"XaUserAddressGeoType",FieldsToRead,{"id"},{HTTP.GetHttpParam("id")});
	RESPONSE.Content= ReadResponse(DbRes,FieldsToRead);
};

void XaUserAddressGeoType::List() {

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

	vector<string> ReturnedFields=ListPrepare({"XaUserAddressGeoType"},"/XaUserAddressGeoType/fieldset/field");

	DbResMap DbRes=XaLibSql::Select(DB_READ,"XaUserAddressGeoType",{ReturnedFields},{WhereFields}, {WhereValues}, {OrderByFields},{GroupByFields},Limit);
	RESPONSE.Content=ListResponse(DbRes,ReturnedFields);	
	//Quali campi
	//
	/*
	vector<string> FieldsToRead = XaLibModel::ReadPrepare({"XaUserAddressGeoType"},"/XaUserAddressGeoType/fieldset/field");
	DbResMap DbRes = ReadExecute("XaUserAddressGeoType",FieldsToRead,HTTP.GetHttpParam("id"));
	RESPONSE.Content= ReadResponse(DbRes,FieldsToRead);
	*/
};

void XaUserAddressGeoType::ListAsOptions() {

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

	DbResMap DbRes=XaLibSql::Select(DB_READ,"XaUserAddressGeoType",{ReturnedFields},{WhereFields}, {WhereValues}, {OrderByFields},{GroupByFields},Limit);
	RESPONSE.Content=ListResponse(DbRes,ReturnedFields);
};

void XaUserAddressGeoType::Update() {

	BackupRecord("XaUserAddressGeoType",50);

	/*
	XaLibBase::FieldsMap LoadedFields=UpdatePrepare({"XaUserAddressGeoType"},"/XaUserAddressGeoType/fieldset/field");
	RESPONSE.Content=CreateResponse(UpdateExecute("XaUserAddressGeoType",LoadedFields));*/
};

void XaUserAddressGeoType::Delete() {

	int DeletedId=DeleteExecute("XaUserAddressGeoType",HTTP.GetHttpParam("id"));
	RESPONSE.Content=DeleteResponse(DeletedId);
};

XaUserAddressGeoType::~XaUserAddressGeoType(){
};