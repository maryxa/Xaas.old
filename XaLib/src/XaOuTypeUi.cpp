#include <XaOuTypeUi.h>
#include <XaLibAction.h>

XaOuTypeUi::XaOuTypeUi(){
};

void XaOuTypeUi::Dispatcher (const string &CalledEvent) {

	if (CalledEvent=="Explorer") {
		//this->Explorer();

    } else if (CalledEvent=="Tree") {
        //this->Tree();
    } else {

		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Requested Event Does Not Exists -> "+CalledEvent);
		//ErrorPage ("EventNotFound");
	}
};

XaOuTypeUi::~XaOuTypeUi(){
};