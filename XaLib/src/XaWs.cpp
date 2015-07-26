#include <XaWs.h>
#include <XaLibAction.h>

XaWs::XaWs(){
};

void XaWs::Dispatcher (const string &CalledEvent) {
	
	if (CalledEvent=="List"){

        this->List();

    } else if (CalledEvent=="boh"){

        this->List();

    } else {
	
		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Requested Event Does Not Exists -> "+CalledEvent);
	}

};

void XaWs::List (){

	XaLibAction::SetLayout("Standard");
    XaLibAction::AddXslFile("XaWsList");

    XaLibAction::AddXmlFile("XaWsListStruct");

	XaLibDom* LibDom=new XaLibDom();
	xmlDocPtr XmlDomDocData=LibDom->DomFromFile(SETTINGS["XmlDir"]+"XaWsListData.xml");

	string Project=HTTP.GetHttpParam("project");
        
        unique_ptr<XaLibSql> LibSql(new XaLibSql());

	string XaWsList{};
        
        if (Project=="MlsClick") {
            XaWsList="SELECT id,XaUser_ID,caller,object,event,request,response,log_data,request_time,response_time FROM XaSessionWsLog WHERE object='MlsClick' ORDER BY request_time DESC LIMIT 100";
        } else {
            XaWsList="SELECT id,XaUser_ID,caller,object,event,request,response,log_data,request_time,response_time FROM XaSessionWsLog WHERE object!='MlsClick' ORDER BY request_time DESC LIMIT 100";
        }

	DbResMap DbResXaWsList=LibSql->FreeQuery(DB_SESSION,XaWsList);

		for (int i=0;i<DbResXaWsList.size();i++) {
			
			xmlDocPtr XmlDomDocDataTemp=xmlCopyDoc(XmlDomDocData,1);

			string XPB="//XaWsList/data/ws/";

			vector<string> XPathExpr {XPB+"XaWs-Id",XPB+"XaWs-XaUser_ID",XPB+"XaWs-Caller",
			                           XPB+"XaWs-Object",XPB+"XaWs-Event",
									   XPB+"XaWs-Request",XPB+"XaWs-Response",
									   XPB+"XaWs-LogData",
									   XPB+"XaWs-Request_Time",XPB+"XaWs-Response_Time"};

			vector<string> XPathValue {DbResXaWsList[i]["id"],DbResXaWsList[i]["XaUser_ID"],DbResXaWsList[i]["caller"],
			                            DbResXaWsList[i]["object"],DbResXaWsList[i]["event"],
										DbResXaWsList[i]["request"],DbResXaWsList[i]["response"],
										DbResXaWsList[i]["log_data"],
										DbResXaWsList[i]["request_time"],DbResXaWsList[i]["response_time"],};

			LibDom->UpdateElementValueByXPath(XmlDomDocDataTemp, XPathExpr, XPathValue);

			XPathExpr.clear();
			XPathValue.clear();

			XaLibAction::AddXmlString(LibDom->StringFromDom(XmlDomDocDataTemp));
		}

	
		xmlDocPtr XmlDomDoc=LibDom->DomFromStringAndFile(XmlFiles,XmlStrings,1);
		xmlDocPtr XslDomDoc=LibDom->DomFromStringAndFile(XslFiles,XslStrings,2);
	delete(LibDom);

    const int MAXITEMS = 2;
    string XslParams[MAXITEMS] = {"a","b"};
    XaLibXsl *LibXsl=new XaLibXsl(XmlDomDoc,XslDomDoc,XslParams,MAXITEMS);

	RESPONSE.Content=LibXsl->GetXHtml();
	//RESPONSE.Content=LibXsl->GetXHtml();
	delete(LibXsl);

};

int XaWs::CheckCaller(const string &CallerName,const string &CallerKey) {

	int ReturnValue=0;

	if (CallerName!="" && CallerKey!="") {

		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"WS -> Caller Name:"+CallerName +":: Caller Key:"+CallerKey);

		XaLibSql LibSql;
		DbResMap DbRes=LibSql.FreeQuery(DB_SESSION,"SELECT id,name,caller_key,active,deleted FROM XaWsCaller WHERE name=\""+CallerName +"\" AND caller_key=\""+CallerKey+"\"");

		if (DbRes.size()==1) {

			if(FromStringToInt(DbRes[0]["active"])==1) {

				if(FromStringToInt(DbRes[0]["deleted"])==0) {

					ReturnValue=1;
					LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"WS Caller Is Authorized -> Caller Name:"+CallerName +":: Caller Key:"+CallerKey);

				} else {

					LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"WS Caller Is Deleted -> Caller Name:"+CallerName +":: Caller Key:"+CallerKey);
				} 

			} else {

				LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"WS Caller Is Not Active -> Caller Name:"+CallerName +":: Caller Key:"+CallerKey);

			}

		} else {

			LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"WS Caller Does Not Exist Or Is Not Unique -> Caller Name:"+CallerName +":: Caller Key:"+CallerKey);
		}
		
		
	} else {

		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"WS Caller Name Or Caller Key are Missing");
	}

	return ReturnValue;
};

XaWs::~XaWs(){
};
