#include <XaOu.h>
#include <XaLibModel.h>

XaOu::XaOu(){
};


void XaOu::Dispatcher (const string &CalledEvent) {

	if (CalledEvent=="Create"){
		this->Create();
//    } else if (CalledEvent=="Read"){
//		 this->Read();
  //  } else if (CalledEvent=="List"){
	//	 this->List();
    } else if (CalledEvent=="ListAsOptions"){
		 this->ListAsOptions();
    //} else if (CalledEvent=="Update"){
		 //this->Update();
    //} else if (CalledEvent=="Delete"){
		 //this->Delete();
    } else {

		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"ERROR-42 Requested Event Does Not Exists -> "+CalledEvent);
		throw 42;
	}
};

void XaOu::Create() {

	vector<string> FieldName;	
	vector<string> FieldValue;

	CreatePrepare({"XaOu"},"/XaOu/fieldset/field",FieldName,FieldValue);
	int NextId=CreateExecute("XaOu",FieldName,FieldValue);

	RESPONSE.Content=CreateResponse(NextId);
};

/*
void XaOu::Create() {

};
*/
/*
XaOuModel::Read(){
};

XaOuModel::Update(){
};

XaOuModel::Delete(){
};

XaOuModel::XaOuModel(){
};
*/

void XaOu::ListAsOptions() {

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
	OrderByFields.push_back("tree_path");
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

	//vector<string> ReturnedFields=ListPrepare({"XaOuType"},"/XaOuType/fieldset/field");

	vector<string> ReturnedFields={"id","name","tree_level"};

	DbResMap DbRes=XaLibSql::Select(DB_READ,"XaOu",{ReturnedFields},{WhereFields}, {WhereValues}, {OrderByFields},{GroupByFields},Limit);
	RESPONSE.Content=ListResponse(DbRes,ReturnedFields);
};

XaOu::~XaOu(){
};