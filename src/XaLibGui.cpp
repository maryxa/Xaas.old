#include <XaLibGui.h>

#include <XaLibAction.h>

using namespace std;

XaLibGui::XaLibGui(){
};

string XaLibGui::List(DbResMap ResMap,const ElementTagNames& TagNames,const string& RootTagName,const string& GroupTagName) {

	string Result={""};

	if (ResMap[0].size()!=TagNames.size()) {
		
		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"TagNames and ResMap sizes are different");

	} else {

		Result.append("<" +RootTagName + ">");

		for (auto i=0;i<ResMap.size();i++) {

			Result.append("<" +GroupTagName + ">");

			for (auto j=0;j<TagNames.size();j++) {

				Result.append("<"+TagNames[j]+">" +ResMap[i][TagNames[j]]+ "</"+TagNames[j]+">");
			}

			Result.append("</" +GroupTagName + ">");
		};

		Result.append("</" +RootTagName + ">");
	
	};

	LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Assembled XML -> "+Result);

	return Result;
};

XaLibGui::~XaLibGui(){
};