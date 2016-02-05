#include <XaUserAddressMail.h>
#include <XaLibModel.h>


XaUserAddressMail::XaUserAddressMail(){
};

void XaUserAddressMail::Dispatcher (const string &CalledEvent) {

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

void XaUserAddressMail::Create() {

	XaLibBase::FieldsMap LoadedFields=CreatePrepare({"XaUserAddressMail"},"/XaUserAddressMail/fieldset/field");
	
        string XaTable="XaUser";
        string XaUserId=HTTP.GetHttpParam("XaUser_ID");
        string XaUserAddressMailTypeId=HTTP.GetHttpParam("XaUserAddressMailType_ID");
        
        unique_ptr<XaLibSql> LibSql (new XaLibSql());
        
        if (LibSql->CheckRow(DB_READ,XaTable,XaUserId,"1","")==0) {
            LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Requested Record ID -> "+XaUserId+" does not exist into Table -> "+XaTable);
            throw 302;
        }
        
        if (LibSql->CheckRow(DB_READ,"XaUserAddressMailType",XaUserAddressMailTypeId,"1","")==0) {
            LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Requested Record ID -> "+XaUserAddressMailTypeId+" does not exist into Table -> XaUserAddressMailType");
            throw 302;
        }
        
        RESPONSE.Content=CreateResponse(CreateExecute("XaUserAddressMail",LoadedFields));
};

void XaUserAddressMail::Read() {

	vector<string> FieldsToRead = XaLibModel::ReadPrepare({"XaUserAddressMail"},"/XaUserAddressMail/fieldset/field");
	
	DbResMap DbRes=XaLibSql::Select(DB_READ,"XaUserAddressMail",FieldsToRead,{"id"},{HTTP.GetHttpParam("id")});
	RESPONSE.Content= ReadResponse(DbRes,FieldsToRead);
};

void XaUserAddressMail::List() {

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

	vector<string> ReturnedFields=ListPrepare({"XaUserAddressMail"},"/XaUserAddressMail/fieldset/field");

	DbResMap DbRes=XaLibSql::Select(DB_READ,"XaUserAddressMail",{ReturnedFields},{WhereFields}, {WhereValues}, {OrderByFields},{GroupByFields},Limit);
	RESPONSE.Content=ListResponse(DbRes,ReturnedFields);	
	//Quali campi
	//
	/*
	vector<string> FieldsToRead = XaLibModel::ReadPrepare({"XaUserAddressMail"},"/XaUserAddressMail/fieldset/field");
	DbResMap DbRes = ReadExecute("XaUserAddressMail",FieldsToRead,HTTP.GetHttpParam("id"));
	RESPONSE.Content= ReadResponse(DbRes,FieldsToRead);
	*/
};

void XaUserAddressMail::Update() {

	BackupRecord("XaUserAddressMail",50);

	/*
	XaLibBase::FieldsMap LoadedFields=UpdatePrepare({"XaUserAddressMail"},"/XaUserAddressMail/fieldset/field");
	RESPONSE.Content=CreateResponse(UpdateExecute("XaUserAddressMail",LoadedFields));*/
};

void XaUserAddressMail::Delete() {

	int DeletedId=DeleteExecute("XaUserAddressMail",HTTP.GetHttpParam("id"));
	RESPONSE.Content=DeleteResponse(DeletedId);
};

XaUserAddressMail::~XaUserAddressMail(){
};