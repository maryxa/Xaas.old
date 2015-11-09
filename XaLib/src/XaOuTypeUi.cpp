#include <XaOuTypeUi.h>
#include <XaLibAction.h>

XaOuTypeUi::XaOuTypeUi(){
};

void XaOuTypeUi::Dispatcher (const string &CalledEvent) {

	if (CalledEvent=="CreateFrm") {

		this->CreateFrm();

    } else if (CalledEvent=="View") {
		//this->Tree();

    } else {

		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Requested Event Does Not Exists -> "+CalledEvent);
		throw 42;
	}
};

void XaOuTypeUi::CreateFrm() {

	//SetLayout("Standard");
	//AddXmlFile("XaOuType");
	//AddXslFile("CreateFrm");

	AddHtmlFile("XaGuiHead");
	AddHtmlFile("XaGuiHeader");
	AddHtmlFile("CreateFrm");

	AddJsVarFile("XaOuType","XaOuType");
	AddJsVarString("XaGuiStyle","default");

	//vector<string> HtmlFiles = {};
	//vector<string> HtmlStrings = {};
	//vector<string> JsVarNames = {};
	//vector<string> JsVarValues = {};

	
	
	string pippo= XaLibDom::HtmlFromStringAndFile(HtmlFiles,HtmlStrings,JsVarFiles,JsVarStrings,0);

			LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"XXXXXXXXX "+pippo);

	RESPONSE.Content=pippo;
	
	/*
	
	
	
	
	string XHtml="<!DOCTYPE html>";
	XHtml.append("<html id=\"html\">");
	
	XHtml.append("<head>");
	
	
		XHtml.append("</head>");

	
	
	XHtml.append("</html>");
	
	
	
	AddXslParamCommon();

	RESPONSE.Content=XaLibGui::CreateForm(XmlFiles,XmlStrings,XslFiles,XslStrings,XslParams);
	*/
};

XaOuTypeUi::~XaOuTypeUi() {
};