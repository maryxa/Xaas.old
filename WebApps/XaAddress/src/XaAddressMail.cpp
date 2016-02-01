#include <XaAddressMail.h>
#include <XaLibModel.h>


XaAddressMail::XaAddressMail(){
};

void XaAddressMail::Dispatcher (const string &CalledEvent) {

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

void XaAddressMail::Create() {

	XaLibBase::FieldsMap LoadedFields=CreatePrepare({"XaAddressMail"},"/XaAddressMail/fieldset/field");
	
        string XaTable=HTTP.GetHttpParam("XaTable");
        string XaFieldId=HTTP.GetHttpParam("XaField_ID");
        string XaAddressMailTypeId=HTTP.GetHttpParam("XaAddressMailType_ID");
        
        unique_ptr<XaLibSql> LibSql (new XaLibSql());
        
        if (LibSql->CheckRow(DB_READ,XaTable,XaFieldId,"1","")==0) {
            LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Requested Record ID -> "+XaFieldId+" does not exist into Table -> "+XaTable);
            throw 302;
        }
        
        if (LibSql->CheckRow(DB_READ,"XaAddressMailType",XaAddressMailTypeId,"1","")==0) {
            LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Requested Record ID -> "+XaAddressMailTypeId+" does not exist into Table -> XaAddressMailType");
            throw 302;
        }
        
        RESPONSE.Content=CreateResponse(CreateExecute("XaAddressMail",LoadedFields));
};

void XaAddressMail::Read() {

	vector<string> FieldsToRead = XaLibModel::ReadPrepare({"XaAddressMail"},"/XaAddressMail/fieldset/field");
	
	DbResMap DbRes=XaLibSql::Select(DB_READ,"XaAddressMail",FieldsToRead,{"id"},{HTTP.GetHttpParam("id")});
	RESPONSE.Content= ReadResponse(DbRes,FieldsToRead);
};

void XaAddressMail::List() {

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

	vector<string> ReturnedFields=ListPrepare({"XaAddressMail"},"/XaAddressMail/fieldset/field");

	DbResMap DbRes=XaLibSql::Select(DB_READ,"XaAddressMail",{ReturnedFields},{WhereFields}, {WhereValues}, {OrderByFields},{GroupByFields},Limit);
	RESPONSE.Content=ListResponse(DbRes,ReturnedFields);	
	//Quali campi
	//
	/*
	vector<string> FieldsToRead = XaLibModel::ReadPrepare({"XaAddressMail"},"/XaAddressMail/fieldset/field");
	DbResMap DbRes = ReadExecute("XaAddressMail",FieldsToRead,HTTP.GetHttpParam("id"));
	RESPONSE.Content= ReadResponse(DbRes,FieldsToRead);
	*/
};

void XaAddressMail::Update() {

	BackupRecord("XaAddressMail",50);

	/*
	XaLibBase::FieldsMap LoadedFields=UpdatePrepare({"XaAddressMail"},"/XaAddressMail/fieldset/field");
	RESPONSE.Content=CreateResponse(UpdateExecute("XaAddressMail",LoadedFields));*/
};

void XaAddressMail::Delete() {

	int DeletedId=DeleteExecute("XaAddressMail",HTTP.GetHttpParam("id"));
	RESPONSE.Content=DeleteResponse(DeletedId);
};

XaAddressMail::~XaAddressMail(){
};