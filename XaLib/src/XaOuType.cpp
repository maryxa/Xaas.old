#include <XaOuType.h>
#include <XaLibModel.h>


XaOuType::XaOuType(){
};

void XaOuType::Dispatcher (const string &CalledEvent) {

	if (CalledEvent=="Create"){

        this->Create();

    } else if (CalledEvent=="Read"){

		 this->Read();

    } else if (CalledEvent=="Update"){

		 this->Update();

    } else if (CalledEvent=="Delete"){

		 this->Delete();

    } else {

		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"ERROR-42 Requested Event Does Not Exists -> "+CalledEvent);
		throw 42;
	}

};

void XaOuType::Create() {

	XaLibBase::FieldsMap LoadedFields=CreatePrepare({"XaOuType"},"/XaOuType/fieldset/field");
	RESPONSE.Content=CreateResponse(CreateExecute("XaOuType",LoadedFields));
};

void XaOuType::Read() {

	vector<string> FieldsToRead = XaLibModel::ReadPrepare({"XaOuType"},"/XaOuType/fieldset/field");
	DbResMap DbRes = ReadExecute("XaOuType",FieldsToRead,HTTP.GetHttpParam("id"));
	RESPONSE.Content= ReadResponse(DbRes,FieldsToRead);
};

void XaOuType::Update(){

	XaLibBase::FieldsMap LoadedFields=UpdatePrepare({"XaOuType"},"/XaOuType/fieldset/field");
	RESPONSE.Content=CreateResponse(UpdateExecute("XaOuType",LoadedFields));
};

void XaOuType::Delete(){

	int DeletedId=DeleteExecute("XaOuType",HTTP.GetHttpParam("id"));
	RESPONSE.Content=DeleteResponse(DeletedId);
};



/*

XaOuModel::Update(){
};



XaOuModel::XaOuModel(){
};
*/
XaOuType::~XaOuType(){
};