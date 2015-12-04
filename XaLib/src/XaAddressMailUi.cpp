#include <XaAddressMailUi.h>
#include <XaLibAction.h>

XaAddressMailUi::XaAddressMailUi(){
};

void XaAddressMailUi::Dispatcher (const string &CalledEvent) {

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

void XaAddressMailUi::CreateFrm() {
	
	AddJsVarFile("XaModel","XaAddressMail");
	AddJsVarString("XaGuiStyle","default");
	RESPONSE.Content=XaLibDom::HtmlFromStringAndFile(AddHtmlFiles({"XaGuiHead","XaGuiHeader","XaGuiCreateFrm","XaGuiNav"}),HtmlStrings,JsVarFiles,JsVarStrings,0);
};

void XaAddressMailUi::Create() {

	CreatePrepare({"XaAddressMail"},"/XaAddressMail/fieldset/field","XaAddressMail");
	BuildBackEndCall("XaAddressMail","Create",FieldsName,FieldsValue);

	XaLibCurl LibCurl;
    string CallResponse = LibCurl.Call(BuildBackEndCall("XaAddressMail","Create",FieldsName,FieldsValue));
	CheckResponse(CallResponse);

	RESPONSE.Content="OK";
};

void XaAddressMailUi::List() {

	XaLibCurl LibCurl;
    string CallResponse = LibCurl.Call(BuildBackEndCall("XaAddressMail","List",{},{}));
	CheckResponse(CallResponse);

	AddJsVarString("XaGuiStyle","default");
	AddJsVarString("WsData",CallResponse);

	RESPONSE.Content=XaLibDom::HtmlFromStringAndFile(AddHtmlFiles({"XaGuiHead","XaGuiHeader","XaGuiList","XaGuiNav"}),HtmlStrings,JsVarFiles,JsVarStrings,0);
};

XaAddressMailUi::~XaAddressMailUi() {
};