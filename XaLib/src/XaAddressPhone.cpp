#include <XaAddressPhone.h>
#include <XaLibModel.h>


XaAddressPhone::XaAddressPhone(){
};

void XaAddressPhone::Dispatcher (const string &CalledEvent) {

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

void XaAddressPhone::Create() {

	XaLibBase::FieldsMap LoadedFields=CreatePrepare({"XaAddressPhone"},"/XaAddressPhone/fieldset/field");
	RESPONSE.Content=CreateResponse(CreateExecute("XaAddressPhone",LoadedFields));
};

void XaAddressPhone::Read() {

	vector<string> FieldsToRead = XaLibModel::ReadPrepare({"XaAddressPhone"},"/XaAddressPhone/fieldset/field");
	
	DbResMap DbRes=XaLibSql::Select(DB_READ,"XaAddressPhone",FieldsToRead,{"id"},{HTTP.GetHttpParam("id")});
	RESPONSE.Content= ReadResponse(DbRes,FieldsToRead);
};

void XaAddressPhone::List() {

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

	vector<string> ReturnedFields=ListPrepare({"XaAddressPhone"},"/XaAddressPhone/fieldset/field");

	DbResMap DbRes=XaLibSql::Select(DB_READ,"XaAddressPhone",{ReturnedFields},{WhereFields}, {WhereValues}, {OrderByFields},{GroupByFields},Limit);
	RESPONSE.Content=ListResponse(DbRes,ReturnedFields);	
	//Quali campi
	//
	/*
	vector<string> FieldsToRead = XaLibModel::ReadPrepare({"XaAddressPhone"},"/XaAddressPhone/fieldset/field");
	DbResMap DbRes = ReadExecute("XaAddressPhone",FieldsToRead,HTTP.GetHttpParam("id"));
	RESPONSE.Content= ReadResponse(DbRes,FieldsToRead);
	*/
};

void XaAddressPhone::Update() {

	BackupRecord("XaAddressPhone",50);

	/*
	XaLibBase::FieldsMap LoadedFields=UpdatePrepare({"XaAddressPhone"},"/XaAddressPhone/fieldset/field");
	RESPONSE.Content=CreateResponse(UpdateExecute("XaAddressPhone",LoadedFields));*/
};

void XaAddressPhone::Delete() {

	int DeletedId=DeleteExecute("XaAddressPhone",HTTP.GetHttpParam("id"));
	RESPONSE.Content=DeleteResponse(DeletedId);
};

XaAddressPhone::~XaAddressPhone(){
};