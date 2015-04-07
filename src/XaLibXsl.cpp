#include <XaLibXsl.h>
#include <XaLibBase.h>

XaLibXsl::XaLibXsl(xmlDocPtr XmlDoc, xmlDocPtr XslDoc, string XslParams[], int NumElements){

	cur = NULL;
	*WithParams = NULL;
	string ParamName;
	string ParamValue;

	//int NumElements=sizeof(XslParams[]);
	//cout<<"NumElements"<<endl;
	//cout<<NumElements<<endl;

	if(NumElements>0) {

		for(int n=0; n<NumElements; n=n+2) {

			ParamName=XslParams[n];
			ParamValue=XslParams[n+1];
			this->AddParams(ParamName,ParamValue,n);
	    }

		WithParams[NumElements] = NULL;

	} else {

		string strWithParamName="";
		strWithParamName.append("'NoParamName'");

		string strWithParamValue="";
		strWithParamValue.append("'NoParamValue'");
		
		WithParams[0] = (char*)strWithParamName.c_str();
		WithParams[1] = (char*)strWithParamValue.c_str();
		WithParams[2] = NULL;
	}

	xmlSubstituteEntitiesDefault(1);
	xmlLoadExtDtdDefaultValue = 1;

	//cur = xsltParseStylesheetFile((const xmlChar *)XslFilePath.c_str());
    cur = xsltParseStylesheetDoc(XslDoc);
	exsltRegisterAll();

	//xsltTransformContextPtr ctxt;

  // ctxt = xsltNewTransformContext(cur, doc);
   //res = xsltApplyStylesheetUser(cur, doc, WithParams, NULL, stderr, ctxt);

   /*
   if ((ctxt->state == XSLT_STATE_ERROR) ||
       (ctxt->state == XSLT_STATE_STOPPED))
           errx(-1, "fail to do xsltApplyStylesheet()");

*/

	res = xsltApplyStylesheet(cur, XmlDoc, WithParams);
	xmlFreeDoc(XmlDoc);

	*WithParams = NULL;
/*	if (xsltApplyStylesheet(cur, doc, WithParams) == NULL) {
		
			cout<<"xsltApplyStylesheet"<<endl;
			cout<<XslFilePath<<endl;
	}*/
};

//extern int xmlLoadExtDtdDefaultValue;
XaLibXsl::XaLibXsl(string XmlFilePath, string XslFilePath){

	//xsltStylesheetPtr cur = NULL;
	xmlDocPtr doc;

	int len = 9999;

	const char *NoParams[1];
	NoParams[0] = 0;

	xmlSubstituteEntitiesDefault(1);
	xmlLoadExtDtdDefaultValue = 1;
	
	//const char *XslFileChar = XslFile.c_str();
	cur = xsltParseStylesheetFile((const xmlChar *)XslFilePath.c_str());
	exsltRegisterAll();

	char *docname = (char*)XmlFilePath.c_str();
	doc = xmlReadFile(docname,NULL,0);

	res = xsltApplyStylesheet(cur, doc, NoParams);
	xmlFreeDoc(doc);
	
	*NoParams = NULL;
	
};

XaLibXsl::XaLibXsl(string XmlString, string XslFilePath, int XmlStringSize){

	const char *XmlChar = (char*)XmlString.c_str();
	xmlDocPtr doc;

	int len = 9999;

	const char *params[16 + 1];
	int nbparams = 0;

	string strParam="";
		strParam.append("NoParamName");
		const char *chrParam = (char*)strParam.c_str();

		string strValue="";
		strValue.append("'NoParamValue'");
		const char *chrValue = (char*)strValue.c_str();
		
		params[0] = chrParam;
		params[1] = chrValue;
		params[2] = NULL;

	xmlSubstituteEntitiesDefault(1);
	xmlLoadExtDtdDefaultValue = 1;

	cur = xsltParseStylesheetFile((const xmlChar *)XslFilePath.c_str());
	exsltRegisterAll();

	doc = xmlRecoverMemory(XmlChar,XmlStringSize);
	res = xsltApplyStylesheet(cur, doc, params);
/*
	xsltSaveResultToString(&out,&len, res, cur);

	out[len] = 0;
 	xsltFreeStylesheet(cur);

	xmlFreeDoc(res);
	xmlFreeDoc(doc);

    xsltCleanupGlobals();
    xmlCleanupParser();
*/
};


XaLibXsl::XaLibXsl(xmlDocPtr doc, string XslFilePath){

	const char *NoParams[1];
	NoParams[0] = 0;

	xmlSubstituteEntitiesDefault(1);
	xmlLoadExtDtdDefaultValue = 1;

	cur = xsltParseStylesheetFile((const xmlChar *)XslFilePath.c_str());
	exsltRegisterAll();

	res = xsltApplyStylesheet(cur, doc, NoParams);
//	xsltTransformContextPtr ctxt;
//	ctxt = xsltNewTransformContext(cur, doc);
 //  	res = xsltApplyStylesheetUser(cur, doc, NoParams, NULL, stderr, ctxt);
	//cout<<"dopo del parse"<<endl;
	xmlFreeDoc(doc);

};


XaLibXsl::XaLibXsl(xmlDocPtr doc, string XslFilePath,string XslParams[],int NumElements){


	cur = NULL;
	*WithParams = NULL;
	string ParamName;
	string ParamValue;
	
	//int NumElements=sizeof(XslParams[]);
	//cout<<NumElements<<endl;

	if(NumElements>0) {

		for(int n=0; n<NumElements; n=n+2) {

			ParamName=XslParams[n];
			ParamValue=XslParams[n+1];
			this->AddParams(ParamName,ParamValue,n);
	    }

		WithParams[NumElements] = NULL;

	} else {

		string strWithParamName="";
		strWithParamName.append("NoParamName");

		string strWithParamValue="";
		strWithParamValue.append("'NoParamValue'");
		
		WithParams[0] = (char*)strWithParamName.c_str();
		WithParams[1] = (char*)strWithParamValue.c_str();
		WithParams[2] = NULL;
	}

	xmlSubstituteEntitiesDefault(1);
	xmlLoadExtDtdDefaultValue = 1;

	cur = xsltParseStylesheetFile((const xmlChar *)XslFilePath.c_str());
	exsltRegisterAll();

	//xsltTransformContextPtr ctxt;
 
  // ctxt = xsltNewTransformContext(cur, doc);
   //res = xsltApplyStylesheetUser(cur, doc, WithParams, NULL, stderr, ctxt);
   
   /*
   if ((ctxt->state == XSLT_STATE_ERROR) ||
       (ctxt->state == XSLT_STATE_STOPPED))
           errx(-1, "fail to do xsltApplyStylesheet()");

*/

	res = xsltApplyStylesheet(cur, doc, WithParams);
	xmlFreeDoc(doc);

	*WithParams = NULL;
/*	if (xsltApplyStylesheet(cur, doc, WithParams) == NULL) {
		
			cout<<"xsltApplyStylesheet"<<endl;
			cout<<XslFilePath<<endl;
	}*/
};

XaLibXsl::XaLibXsl(xmlDocPtr doc, string XslFilePath,VectorXslParamsName XslParamsName, VectorXslParamsValue XslParamsValue){

	cur = NULL;
	*WithParams = NULL;

	unsigned XslParamsNameSize=XslParamsName.size();
	unsigned XslParamsValueSize=XslParamsValue.size();

	if(XslParamsNameSize==XslParamsValueSize && XslParamsNameSize>0) {
		
		int j=0;

		for(int n=0; n<XslParamsValueSize; n++) {

			string pippo=XslParamsName.at(n).c_str();
			string pluto=XslParamsValue.at(n).c_str();
			
			this->AddParams(pippo,pluto,j);
			j=j+2;
	    }

		WithParams[j] = 0;

	} else {

		string strWithParamName="";
		strWithParamName.append("NoParamName");

		string strWithParamValue="";
		strWithParamValue.append("'NoParamValue'");
		
		WithParams[0] = (char*)strWithParamName.c_str();
		WithParams[1] = (char*)strWithParamValue.c_str();
		WithParams[2] = 0;
	}

	xmlSubstituteEntitiesDefault(1);
	xmlLoadExtDtdDefaultValue = 1;

	cur = xsltParseStylesheetFile((const xmlChar *)XslFilePath.c_str());
	exsltRegisterAll();

	res = xsltApplyStylesheet(cur, doc, WithParams);
	xmlFreeDoc(doc);

	*WithParams = NULL;
/*	if (xsltApplyStylesheet(cur, doc, WithParams) == NULL) {
		
			cout<<"xsltApplyStylesheet"<<endl;
			cout<<XslFilePath<<endl;
	}*/
};

void XaLibXsl::AddParams(string XslParamsName, string XslParamsValue,int ParamPosition){

	string strWithParamName="";
	string strWithParamValue="";
	int j=ParamPosition;


	strWithParamName.append(XslParamsName.c_str());
	
	strWithParamValue.append("'");
	strWithParamValue.append(XslParamsValue.c_str());
	strWithParamValue.append("'");

	char* s = new char[strWithParamName.length()+1];
	strcpy(s,strWithParamName.c_str());

	char* t = new char[strWithParamValue.length()+1];
	strcpy(t,strWithParamValue.c_str());


	WithParams[j] = s;
	WithParams[j+1] =t;

};

string XaLibXsl::GetXHtml(){

	xmlChar *out=0;
	int len = 9999;
	
	if( xsltSaveResultToString(&out,&len, res, cur)==0) {

		out[len] = 0;

		xsltFreeStylesheet(cur);
		xmlFreeDoc(res);

		xsltCleanupGlobals();
		xmlCleanupParser();

	} else {

		cout<<"errore parsing"<<endl;
		//cout<<XslFilePath<<endl;
	}

	string strVoid="";
	string *XHtmlStr = &strVoid;
	
	char* XHtmlChr;

	XHtmlChr=(char*)out;

	if( *XHtmlChr==0){

		return "Error XmlOutput";

	} else {

		*XHtmlStr=XHtmlChr;
		
		return *XHtmlStr;
	}

};

XaLibXsl::~XaLibXsl(){
	//xsltFreeStylesheet(cur);
	//xmlFreeDoc(res);
};
