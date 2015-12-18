#include <XaOuUi.h>
#include <XaLibAction.h>

XaOuUi::XaOuUi(){
};

void XaOuUi::Dispatcher (const string &CalledEvent) {

	if (CalledEvent=="CreateFrm") {
		this->CreateFrm();

    } else if (CalledEvent=="Create") {
        this->Create();

    } else if (CalledEvent=="ListAsOptions") {
        this->ListAsOptions();

    } else if (CalledEvent=="Explorer") {
        this->Explorer();

    } else if (CalledEvent=="Tree") {
        this->Tree();
    } else {

		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Requested Event Does Not Exists -> "+CalledEvent);
		//ErrorPage ("EventNotFound");
	}
};

void XaOuUi::CreateFrm() {

	AddJsVarFile("XaModel","XaOu");
	AddJsVarString("XaGuiStyle","default");

	vector<string> Templates=SetPageLayout(REQUEST.CalledLayout);
	Templates.push_back("XaGuiCreateFrm");

	RESPONSE.Content=XaLibDom::HtmlFromStringAndFile(AddHtmlFiles(Templates),HtmlStrings,JsVarFiles,JsVarStrings,0);
};

void XaOuUi::Create() {

	auto Fields=CreatePrepare({"XaOu"},"/XaOu/fieldset/field","XaOu");
	XaLibCurl LibCurl;
    string CallResponse = LibCurl.Call(BuildBackEndCall("XaOu","Create",get<0>(Fields),get<1>(Fields)));
	CheckResponse(CallResponse);
	RESPONSE.Content="OK";
};

void XaOuUi::ListAsOptions() {

	XaLibCurl LibCurl;
    string CallResponse = LibCurl.Call(BuildBackEndCall("XaOu","ListAsOptions",{"order_by"},{"name"}));
	CheckResponse(CallResponse);

	RESPONSE.Content=CallResponse;
};

void XaOuUi::Tree () {

//	SetLayout(REQUEST.CalledLayout);

	AddXmlFile("XaOuTree");
	AddXslFile("XaOuTree");

	XaLibDom* LibDom=new XaLibDom();
//	xmlDocPtr XmlDomDocTree=LibDom->DomFromFile(SETTINGS["XmlDir"]+"XaOuTree.xml");
	xmlDocPtr XmlDomDocTree=LibDom->DomFromFile(SETTINGS["SharedDir"]+"xml/XaOuTree.xml");

	XaLibSql* LibSql=new XaLibSql();

	string QryMaxTreeLevel="SELECT max(tree_level) AS tree_level FROM XaUser";
	DbResMap DbResMaxTreeLevel=LibSql->FreeQuerySelect(DB_READ,QryMaxTreeLevel);

	int MaxTreeLevel=XaLibBase::FromStringToInt(DbResMaxTreeLevel[0]["tree_level"]);

	string TreeType=HTTP.GetHttpParam("TreeType");
	string LoginFilter=HTTP.GetHttpParam("LoginFilter");

	string QryOrg;

	if (TreeType=="ou") {

		QryOrg="SELECT id,surname,tree_path,tree_parent_ID,tree_level,leaf,XaUserType_ID FROM XaUser WHERE id>2 AND XaUserRole_ID!=2 AND deleted=0 AND leaf=0 ORDER BY surname ";

	} else {
		string cond="";
		if (LoginFilter=="true") {
			cond=" AND login IN (1,0)";
		}
		QryOrg ="(SELECT id,old_id,surname,tree_path,tree_parent_ID,tree_level,leaf,XaUserType_ID FROM XaUser WHERE id>2 AND XaUserType_ID=3 AND deleted=0 AND active=1 "+cond+" ORDER BY surname)";
		QryOrg+=" UNION ";
		QryOrg+="(SELECT id,old_id,surname,tree_path,tree_parent_ID,tree_level,leaf,XaUserType_ID FROM XaUser WHERE id>2 AND XaUserRole_ID!=2 AND deleted=0 AND leaf=0 ORDER BY surname )";
		QryOrg+=" ORDER BY surname ";
	}

	//string QryOrg="SELECT id,surname,tree_path,tree_parent_ID,tree_level,leaf FROM XaUser WHERE deleted=0";
	DbResMap DbResOrg=LibSql->FreeQuerySelect(DB_READ,QryOrg);

	for (int i=2;i<=MaxTreeLevel;i++) {

		typedef map<int, map<string,string> > DbDataMap;
		DbDataMap DbData;

		int k=0;

		for (int j=0;j<DbResOrg.size();j++) {

			if (XaLibBase::FromStringToInt(DbResOrg[j]["tree_level"])==i) {

				//DbData[k]["id"]=XaLibAction::EncryptParam(DbResOrg[j]["id"]);
				DbData[k]["id"]=DbResOrg[j]["id"];
				DbData[k]["tree_level"]=DbResOrg[j]["tree_level"];
				DbData[k]["surname"]=DbResOrg[j]["surname"];
				DbData[k]["tree_parent_ID"]=DbResOrg[j]["tree_parent_ID"];
				DbData[k]["leaf"]=DbResOrg[j]["leaf"];
				DbData[k]["XaUserType_ID"]=DbResOrg[j]["XaUserType_ID"];

				k++;

			} else {

			}

		}

		string XPathExpr="";

		for (int z=0;z<DbData.size();z++) {

			if (i==2) {

				XPathExpr="//XaUserOrgTree";

			} else {

				//XPathExpr="//ou[@id='"+XaLibAction::EncryptParam(DbData[z]["tree_parent_ID"])+"']";
				XPathExpr="//ou[@id='"+DbData[z]["tree_parent_ID"]+"']";
				
			}

			if (XaLibBase::FromStringToInt(DbData[z]["leaf"])==0){

				LibDom->AddOrgTreeOu(XmlDomDocTree, XPathExpr,DbData[z]["id"],DbData[z]["surname"],DbData[z]["XaUserType_ID"]);

			} else if (XaLibBase::FromStringToInt(DbData[z]["leaf"])!=0){

				LibDom->AddOrgTreeUser(XmlDomDocTree, XPathExpr,DbData[z]["id"],DbData[z]["surname"]);
			}
		}

	string pippo=LibDom->StringFromDom(XmlDomDocTree);
		

		DbData.clear();

		}

	DbResOrg.clear();
	DbResMaxTreeLevel.clear();

		XaLibAction::AddXmlString(LibDom->StringFromDom(XmlDomDocTree));

	string TplType=HTTP.GetHttpParam("TplType");
	
	if (TplType=="NoHttpParam") {

		TplType="tree";
	}

	AddXslParamCommon();
	AddXslParam("TplType",TplType);

	RESPONSE.Content=XaLibGui::CreateForm(XmlFiles,XmlStrings,XslFiles,XslStrings,XslParams);

};

void XaOuUi::Explorer () {

//	SetLayout(REQUEST.CalledLayout);
	AddXslFile("XaOuExplorer");
	AddXslParamCommon();

	RESPONSE.Content=XaLibGui::CreateForm(XmlFiles,XmlStrings,XslFiles,XslStrings,XslParams);
};

XaOuUi::~XaOuUi(){
};