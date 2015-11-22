#include <XaOuTypeUi.h>
#include <XaLibAction.h>

XaOuTypeUi::XaOuTypeUi(){
};

void XaOuTypeUi::Dispatcher (const string &CalledEvent) {

	if (CalledEvent=="CreateFrm") {
		this->CreateFrm();
    } else if (CalledEvent=="Create") {
		this->Create();
    } else if (CalledEvent=="List") {
		this->List();
    } else {
		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Requested Event Does Not Exists -> "+CalledEvent);
		throw 42;
	}
};

void XaOuTypeUi::CreateFrm() {
	
	AddJsVarFile("XaModel","XaOuType");
	AddJsVarString("XaGuiStyle","default");
	RESPONSE.Content=XaLibDom::HtmlFromStringAndFile(AddHtmlFiles({"XaGuiHead","XaGuiHeader","XaGuiCreateFrm","XaGuiNav"}),HtmlStrings,JsVarFiles,JsVarStrings,0);
};

void XaOuTypeUi::Create() {

	CreatePrepare({"XaOuType"},"/XaOuType/fieldset/field","XaOuType");
	BuildBackEndCall("XaOuType","Create",FieldsName,FieldsValue);

	XaLibCurl LibCurl;
    string CallResponse = LibCurl.Call(BuildBackEndCall("XaOuType","Create",FieldsName,FieldsValue));
	CheckResponse(CallResponse);

	RESPONSE.Content="OK";
};

void XaOuTypeUi::List() {

	XaLibCurl LibCurl;
    string CallResponse = LibCurl.Call(BuildBackEndCall("XaOuType","List",{},{}));
	CheckResponse(CallResponse);

	AddJsVarString("XaGuiStyle","default");
	AddJsVarString("WsData",CallResponse);

	RESPONSE.Content=XaLibDom::HtmlFromStringAndFile(AddHtmlFiles({"XaGuiHead","XaGuiHeader","XaGuiList","XaGuiNav"}),HtmlStrings,JsVarFiles,JsVarStrings,0);
};

XaOuTypeUi::~XaOuTypeUi() {
};