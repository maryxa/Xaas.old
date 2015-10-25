#include <XaLibModel.h>

XaLibModel::XaLibModel() {
};

vector<string> XaLibModel::AddXmlFile(const vector<string>& FileName){

	vector<string> XmlFiles;

	for (auto &i : FileName) {

		//BUILDING THE PATH
		string XmlDefaultPath=SETTINGS["XmlDir"]+i+".xml";
		string XmlSharedPath=SETTINGS["SharedDir"]+"xml/"+i+".xml";

		//TEST THE FILE
		unique_ptr<FILE, int(*)(FILE*)> f1(fopen(XmlDefaultPath.c_str(), "r"), fclose);
		unique_ptr<FILE, int(*)(FILE*)> f2(fopen(XmlSharedPath.c_str(), "r"), fclose);

		//ADD THE FILE TO THE VECTOR
		if (f1) {
			XmlFiles.push_back(XmlDefaultPath);
			LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Added XmlFile Custom-> "+XmlDefaultPath);

		} else if (f2) {
			XmlFiles.push_back(XmlSharedPath);
			LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Added XmlFile Shared-> "+XmlSharedPath);

		} else {

			LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Requested Xml File Does Not Exist -> "+i);
			throw 203;
		}
	}	

	return XmlFiles;
};

XaLibBase::FieldsMap XaLibModel::CreatePrepare(const vector<string>& XmlFiles,const string& XPathExpr) {

	//TODO:GESTIONE ERRORI

	//PROPERTIES DEFINED
	vector <string> Properties ={"name","type","size","required"};

	//LOAD XML FOR MODEL
	xmlDocPtr XmlDomDoc=XaLibDom::DomFromFile(AddXmlFile(XmlFiles),0);

	//GET NUMBER OF FILEDS
	int FieldsNum=XaLibDom::GetNumRowByXPathInt(XmlDomDoc,XPathExpr);

	FieldsMap Fields;
	
	for (auto i=0;i<FieldsNum;i++) {

		for ( auto &j : Properties) {	

			//LOADING PROPERTIES
			Fields[i][j]=XaLibDom::GetElementValueByXPath(XmlDomDoc,XPathExpr+"["+ to_string(i+1) + "]/"+j);

			LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Loaded value for property ->" +j +" :: "+Fields[i][j]);			
		};

		//LOADING PASSED VALUE
		Fields[i]["value"]=HTTP.GetHttpParam(Fields[i]["name"]);	
	};

	return Fields;
};

int XaLibModel::CreateExecute(const string& DbTable,XaLibBase::FieldsMap& LoadedFields) {

	//CHECK FIELDS
	vector <string> Fields={"status","old_id"};
	vector <string> Values={"1","0"};

	for (auto i=0;i<LoadedFields.size();i++) {

		Fields.push_back(LoadedFields[i]["name"]);	
		Values.push_back(LoadedFields[i]["value"]);
	};

	int NextId=XaLibSql::Insert(DB_WRITE,DbTable,Fields,Values);

	if (NextId==0) {

		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"ERROR-301 Inserted a new record into table -> "+DbTable+" with id ->"+to_string(NextId));
		throw 301;
	}

	LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Inserted a new record into table -> "+DbTable+" with id ->"+to_string(NextId));

	return NextId;
};

string XaLibModel::CreateResponse(const int& NextId) {

	return "<create>"+to_string(NextId)+"</create>";
};

vector<string> XaLibModel::ReadPrepare(const vector<string>& XmlFiles,const string& XPathExpr) {

	//TODO:GESTIONE ERRORI
	vector<string> FieldsToRead;

	//LOAD XML FOR MODEL
	xmlDocPtr XmlDomDoc=XaLibDom::DomFromFile(AddXmlFile(XmlFiles),0);

	//GET NUMBER OF FILEDS
	int FieldsNum=XaLibDom::GetNumRowByXPathInt(XmlDomDoc,XPathExpr);
	
	for (auto i=0;i<FieldsNum;i++) {
		
		if (XaLibDom::GetElementValueByXPath(XmlDomDoc,XPathExpr+"["+ to_string(i+1) + "]/read")=="yes"){
		
			FieldsToRead.push_back(XaLibDom::GetElementValueByXPath(XmlDomDoc,XPathExpr+"["+ to_string(i+1) + "]/name"));
		};
		
	};
	
	//SE E" VUOTO
	return FieldsToRead;
};

XaLibBase::DbResMap XaLibModel::ReadExecute(const string& DbTable,vector<string>& FieldsToRead,const string& FieldId) {

	FieldsToRead.push_back("id");
	FieldsToRead.push_back("created");
	FieldsToRead.push_back("updated");

	LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Read From Table -> "+DbTable+" with id ->"+FieldId);

	return XaLibSql::Select(DB_READ,DbTable,FieldsToRead,{"id"},{FieldId});;
};

string XaLibModel::ReadResponse(DbResMap& DbRes,vector<string>& FieldsToRead) {

	string Res="<read>";
	
	for (auto &i: FieldsToRead) {
			
		Res.append("<"+i+">");
		Res.append(DbRes[0][i]);
		Res.append("</"+i+">");
	};

	Res.append("</read>");

	return Res;	
};

int XaLibModel::BackupRecord(const string& DbTable,const int& FieldId) {
/*
	vector<string> Columns=XaLibSql::ColumnsList(DB_READ,"XaOuType");
	
	string List="(";
	
	
	for (auto i=0;i<Columns.size();i++) {
	
		L'ultimo no virgola
	}
	
	for (const auto &e : Columns) {
	
		List.append(e);
		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"FIELD -> "+e);

	};

	
	INSERT INTO table (col1, col2, col3, ...)
	SELECT col1, col2, col3, ... FROM table
	WHERE primarykey = 1
*/	
};

XaLibBase::FieldsMap XaLibModel::UpdatePrepare(const vector<string>& XmlFiles,const string& XPathExpr) {

	//TODO:GESTIONE ERRORI

	//PROPERTIES DEFINED
	vector <string> Properties ={"name","type","size","required","update"};

	//LOAD XML FOR MODEL
	xmlDocPtr XmlDomDoc=XaLibDom::DomFromFile(AddXmlFile(XmlFiles),0);

	//GET NUMBER OF FILEDS
	int FieldsNum=XaLibDom::GetNumRowByXPathInt(XmlDomDoc,XPathExpr);

	FieldsMap Fields;
	
	for (auto i=0;i<FieldsNum;i++) {

		for ( auto &j : Properties) {	

			//LOADING PROPERTIES
			Fields[i][j]=XaLibDom::GetElementValueByXPath(XmlDomDoc,XPathExpr+"["+ to_string(i+1) + "]/"+j);

			LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Loaded value for property ->" +j +" :: "+Fields[i][j]);			
		};

		//LOADING PASSED VALUE
		Fields[i]["value"]=HTTP.GetHttpParam(Fields[i]["name"]);	
	};

	return Fields;
};

int XaLibModel::UpdateExecute(const string& DbTable,XaLibBase::FieldsMap& LoadedFields) {

	//CHECK FIELDS
	//vector <string> Fields={"status","old_id"};
	//vector <string> Values={"1","0"};

	string IdToUpdate=HTTP.GetHttpParam("id");
	vector <string> Fields;
	vector <string> Values;

	for (auto i=0;i<LoadedFields.size();i++) {
		
		if (LoadedFields[i]["value"]!="NoHttpParam") {

			Fields.push_back(LoadedFields[i]["name"]);	
			Values.push_back(LoadedFields[i]["value"]);

		}
	};
	
	if(XaLibSql::Update(DB_WRITE,DbTable,Fields,Values,{"id"},{IdToUpdate})==1) {

		return FromStringToInt(IdToUpdate);

	} else {

		return 0;
	}
};

string XaLibModel::UpdateResponse(const int& UpdatedId) {

	return "<update>"+to_string(UpdatedId)+"</update>";
};



int XaLibModel::DeleteExecute(const string& DbTable,const string& FieldId) {

	//TODO: ERROR CHECK
	if (XaLibSql::Update(DB_WRITE,DbTable,{"status"},{"4"},{"id"},{FieldId})==1){
	
		return FromStringToInt(FieldId);

	} else {

		return 0;
	}

};

string XaLibModel::DeleteResponse(const int& DeletedId) {

	return "<delete>"+to_string(DeletedId)+"</delete>";
};

/*
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
*/
/*
 se voglio properties->property nell'xml passo Properties,property
 */
/*
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
*/
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

XaLibModel::~XaLibModel(){
};