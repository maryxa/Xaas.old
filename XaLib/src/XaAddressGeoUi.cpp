#include <XaAddressGeoUi.h>
#include <XaLibAction.h>

XaAddressGeoUi::XaAddressGeoUi(){
};

void XaAddressGeoUi::Dispatcher (const string &CalledEvent) {

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

void XaAddressGeoUi::CreateFrm() {
	
	AddJsVarFile("XaModel","XaAddressGeo");
	AddJsVarString("XaGuiStyle","default");
	RESPONSE.Content=XaLibDom::HtmlFromStringAndFile(AddHtmlFiles({"XaGuiHead","XaGuiHeader","XaGuiCreateFrm","XaGuiNav"}),HtmlStrings,JsVarFiles,JsVarStrings,0);
};

void XaAddressGeoUi::Create() {

	CreatePrepare({"XaAddressGeo"},"/XaAddressGeo/fieldset/field","XaAddressGeo");
	BuildBackEndCall("XaAddressGeo","Create",FieldsName,FieldsValue);

	XaLibCurl LibCurl;
    string CallResponse = LibCurl.Call(BuildBackEndCall("XaAddressGeo","Create",FieldsName,FieldsValue));
	CheckResponse(CallResponse);

	RESPONSE.Content="OK";
};

void XaAddressGeoUi::List() {

	XaLibCurl LibCurl;
    string CallResponse = LibCurl.Call(BuildBackEndCall("XaAddressGeo","List",{},{}));
	CheckResponse(CallResponse);

	AddJsVarString("XaGuiStyle","default");
	AddJsVarString("WsData",CallResponse);

	RESPONSE.Content=XaLibDom::HtmlFromStringAndFile(AddHtmlFiles({"XaGuiHead","XaGuiHeader","XaGuiList","XaGuiNav"}),HtmlStrings,JsVarFiles,JsVarStrings,0);
};

XaAddressGeoUi::~XaAddressGeoUi() {
};