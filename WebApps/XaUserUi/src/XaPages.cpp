#include <XaPages.h>

XaPages::XaPages(){
};

void XaPages::Dispatcher (const string &CalledEvent) {

	if (CalledEvent=="XaMyPage"){

        this->XaMyPage();

    } else if (CalledEvent=="XaInfoPage"){

        this->XaInfoPage();

    } else {

		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"REQUESTed Event Does Not Exists 2-> "+CalledEvent);
	}

};

void XaPages::XaMyPage() {

	AddXmlFile("XaMyPage");
	SetLayout(REQUEST.CalledLayout);
	AddXslFile("XaMyPage");
	
    xmlDocPtr XmlDomDoc=XaLibDom::DomFromStringAndFile(XmlFiles,XmlStrings,1);
    xmlDocPtr XslDomDoc=XaLibDom::DomFromStringAndFile(XslFiles,XslStrings,2);

	AddXslParamCommon();

    unique_ptr<XaLibXsl> LibXsl (new XaLibXsl(XmlDomDoc,XslDomDoc,XslParams));

	RESPONSE.Content=LibXsl->GetXHtml();
};

void XaPages::XaInfoPage() {

	string ErrorMessage=HTTP.GetHttpParam("ErrorMessage");

	if(ErrorMessage=="NoHttpParam") {

		ErrorMessage="NoErrorMessage";
	}

	SetLayout("InfoPage");

	xmlDocPtr XmlDomDoc=XaLibDom::DomFromStringAndFile(XmlFiles,XmlStrings,1);
    xmlDocPtr XslDomDoc=XaLibDom::DomFromStringAndFile(XslFiles,XslStrings,2);

	AddXslParamCommon();
	AddXslParam("ErrorMessage",ErrorMessage);

	unique_ptr<XaLibXsl> LibXsl (new XaLibXsl(XmlDomDoc,XslDomDoc,XslParams));
    RESPONSE.Content=LibXsl->GetXHtml();
};

XaPages::~XaPages(){
};