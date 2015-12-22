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

		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"ERROR-42:: Requested Event Does Not Exists -> "+CalledEvent);
		throw 42;
	}
};

void XaOu::Create() {

	vector<string> FieldName;	
	vector<string> FieldValue;

	CreatePrepare({"XaOu"},"/XaOu/fieldset/field",FieldName,FieldValue);

	/*Get parent level*/
	int pos=PositionInVector(FieldName,"tree_parent_ID");

	if (pos==-1) {

		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"ERROR-206:: Searched Element is Not present in the Vector");
		throw 206;
	};

	string tree_parent_ID= FieldValue[pos];

	LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Retrieved tree_parent_ID ->"+ tree_parent_ID);

	DbResMap Parent=XaLibSql::Select(DB_READ,"XaOu",{"id","tree_level","tree_path"},{"id"},{tree_parent_ID});

	if (Parent.size()!=1) {

		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"ERROR-304:: The record is not unique");
		throw 304;
	};

	/*CALCULATING TREE LEVEL*/
	string TreeLevel=FromIntToString((FromStringToInt(Parent[0]["tree_level"])+1));

	FieldName.push_back("tree_level");
	FieldValue.push_back(TreeLevel);

	int NextId=CreateExecute("XaOu",FieldName,FieldValue);

	/*CALCULATING TREE PATH*/
	string TreePath=Parent[0]["tree_path"]+FromIntToString(NextId)+"|";

	XaLibSql::Update(DB_WRITE,"XaOu",{"tree_path"},{TreePath},{"id"},{FromIntToString(NextId)});
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