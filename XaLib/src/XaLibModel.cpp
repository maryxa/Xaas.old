#include <XaLibModel.h>

XaLibModel::XaLibModel(){
};



int XaLibModel::Create() {

	int NextId=XaLibSql::Insert(DB_WRITE,DbTable,Fields,Values);

	if(NextId==0) {

		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Error Db Insert");

	} else {

		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Db Insert -> Table :"+ DbTable +":: ID : " + FromIntToString(NextId));
	}

	ResetPoperites();
	return NextId;
};

XaLibBase::DbResMap XaLibModel::Read(){

	LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Executing Read");

	DbResMap ResMap= XaLibSql::Select(DB_READ,DbTable,ReturnedFields,WhereFields,WhereValues,OrderByFields,GroupByFields,0);

	LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Executed Read");

	ResetPoperites();
	return ResMap;
};

void XaLibModel::ResetPoperites () {

	Fields.empty();
	Values.empty();
	ReturnedFields.empty();
	WhereFields.empty();
	WhereValues.empty();
	OrderByFields.empty();
	GroupByFields.empty();
	Limit=0;
};

/*
 se voglio properties->property nell'xml passo Properties,property
 */

string XaLibModel::BuildXml(DbResMap& ResMap,const string& Container,const string& GroupBy) {
	
	string Xml="";
	Xml.append("<").append(Container).append(">");
	
	for (auto i=0;i<ResMap.size();i++) {

		Xml.append("<").append(GroupBy).append(">");

		for (auto j=0;j<ReturnedFields.size();j++) {
			
			Xml.append("<").append(ReturnedFields[j]).append(">");
			Xml.append(ResMap[i][ReturnedFields[j]]);
			Xml.append("</").append(ReturnedFields[j]).append(">");
		}

		Xml.append("</").append(GroupBy).append(">");
	}

	Xml.append("</").append(Container).append(">");

	return Xml;
};

void XaLibModel::Execute(){

	//EXECUTE OBJECT DISPATCHER (CLASS DISPATCHER)
	if (REQUEST.CalledObject!="" && REQUEST.CalledEvent!="") {

		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Executing Object Event ->"+REQUEST.CalledEvent);
		this->Dispatcher(REQUEST.CalledEvent);

	} else {

		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Event Is empty");
		throw 41;
	}

};


/*
XaLibModel::GetFieldName (const& string TableName) {
DbResMap ResMap= XaLibSql::Select(DB_READ,"XaAdvChannel",ReturnedFields);	
SELECT `COLUMN_NAME` 
FROM `INFORMATION_SCHEMA`.`COLUMNS` 
WHERE `TABLE_SCHEMA`='yourdatabasename' 
    AND `TABLE_NAME`='yourtablename';
};
*/
XaLibModel::~XaLibModel(){
};