#include <XaAddressGeo.h>
#include <XaLibModel.h>


XaAddressGeo::XaAddressGeo(){
};

void XaAddressGeo::Dispatcher (const string &CalledEvent) {

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

void XaAddressGeo::Create() {

	XaLibBase::FieldsMap LoadedFields=CreatePrepare({"XaAddressGeo"},"/XaAddressGeo/fieldset/field");
	RESPONSE.Content=CreateResponse(CreateExecute("XaAddressGeo",LoadedFields));
};

void XaAddressGeo::Read() {

	vector<string> FieldsToRead = XaLibModel::ReadPrepare({"XaAddressGeo"},"/XaAddressGeo/fieldset/field");
	
	DbResMap DbRes=XaLibSql::Select(DB_READ,"XaAddressGeo",FieldsToRead,{"id"},{HTTP.GetHttpParam("id")});
	RESPONSE.Content= ReadResponse(DbRes,FieldsToRead);
};

void XaAddressGeo::List() {

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

	vector<string> ReturnedFields=ListPrepare({"XaAddressGeo"},"/XaAddressGeo/fieldset/field");

	DbResMap DbRes=XaLibSql::Select(DB_READ,"XaAddressGeo",{ReturnedFields},{WhereFields}, {WhereValues}, {OrderByFields},{GroupByFields},Limit);
	RESPONSE.Content=ListResponse(DbRes,ReturnedFields);	
	//Quali campi
	//
	/*
	vector<string> FieldsToRead = XaLibModel::ReadPrepare({"XaAddressGeo"},"/XaAddressGeo/fieldset/field");
	DbResMap DbRes = ReadExecute("XaAddressGeo",FieldsToRead,HTTP.GetHttpParam("id"));
	RESPONSE.Content= ReadResponse(DbRes,FieldsToRead);
	*/
};

void XaAddressGeo::Update() {

	BackupRecord("XaAddressGeo",50);

	/*
	XaLibBase::FieldsMap LoadedFields=UpdatePrepare({"XaAddressGeo"},"/XaAddressGeo/fieldset/field");
	RESPONSE.Content=CreateResponse(UpdateExecute("XaAddressGeo",LoadedFields));*/
};

void XaAddressGeo::Delete() {

	int DeletedId=DeleteExecute("XaAddressGeo",HTTP.GetHttpParam("id"));
	RESPONSE.Content=DeleteResponse(DeletedId);
};

XaAddressGeo::~XaAddressGeo(){
};