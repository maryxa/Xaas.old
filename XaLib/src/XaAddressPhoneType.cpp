#include <XaAddressPhoneType.h>
#include <XaLibModel.h>


XaAddressPhoneType::XaAddressPhoneType(){
};

void XaAddressPhoneType::Dispatcher (const string &CalledEvent) {

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

void XaAddressPhoneType::Create() {

	XaLibBase::FieldsMap LoadedFields=CreatePrepare({"XaAddressPhoneType"},"/XaAddressPhoneType/fieldset/field");
	RESPONSE.Content=CreateResponse(CreateExecute("XaAddressPhoneType",LoadedFields));
};

void XaAddressPhoneType::Read() {

	vector<string> FieldsToRead = XaLibModel::ReadPrepare({"XaAddressPhoneType"},"/XaAddressPhoneType/fieldset/field");
	
	DbResMap DbRes=XaLibSql::Select(DB_READ,"XaAddressPhoneType",FieldsToRead,{"id"},{HTTP.GetHttpParam("id")});
	RESPONSE.Content= ReadResponse(DbRes,FieldsToRead);
};

void XaAddressPhoneType::List() {

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

	vector<string> ReturnedFields=ListPrepare({"XaAddressPhoneType"},"/XaAddressPhoneType/fieldset/field");

	DbResMap DbRes=XaLibSql::Select(DB_READ,"XaAddressPhoneType",{ReturnedFields},{WhereFields}, {WhereValues}, {OrderByFields},{GroupByFields},Limit);
	RESPONSE.Content=ListResponse(DbRes,ReturnedFields);	
	//Quali campi
	//
	/*
	vector<string> FieldsToRead = XaLibModel::ReadPrepare({"XaAddressPhoneType"},"/XaAddressPhoneType/fieldset/field");
	DbResMap DbRes = ReadExecute("XaAddressPhoneType",FieldsToRead,HTTP.GetHttpParam("id"));
	RESPONSE.Content= ReadResponse(DbRes,FieldsToRead);
	*/
};

void XaAddressPhoneType::Update() {

	BackupRecord("XaAddressPhoneType",50);

	/*
	XaLibBase::FieldsMap LoadedFields=UpdatePrepare({"XaAddressPhoneType"},"/XaAddressPhoneType/fieldset/field");
	RESPONSE.Content=CreateResponse(UpdateExecute("XaAddressPhoneType",LoadedFields));*/
};

void XaAddressPhoneType::Delete() {

	int DeletedId=DeleteExecute("XaAddressPhoneType",HTTP.GetHttpParam("id"));
	RESPONSE.Content=DeleteResponse(DeletedId);
};

XaAddressPhoneType::~XaAddressPhoneType(){
};