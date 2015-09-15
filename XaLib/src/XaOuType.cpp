#include <XaOuType.h>
#include <XaLibModel.h>

XaOuType::XaOuType(){

	DbTable="XaOuType";
};

void XaOuType::Dispatcher (const string &CalledEvent) {

	if (CalledEvent=="GetList"){

        this->GetList();

    } else {

		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Requested Event Does Not Exists -> "+CalledEvent);
		throw 42;
	}
};

void XaOuType::GetList(){

	ReturnedFields={"id","name","description"};
	DbResMap ResMap=Read();

	RESPONSE.Content=BuildXml(ResMap,"OuTypes","OuType");
};

XaOuType::~XaOuType(){
};