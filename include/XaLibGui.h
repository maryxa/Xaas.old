#ifndef XALIBGUI_H
#define XALIBGUI_H

#include <XaLibBase.h>
#include <XaLibLog.h>
#include <XaLibChar.h>

class XaLibGui : protected XaLibBase {

    private:
		typedef vector<string> ElementTagNames;

	protected:

	public:

		static string List(DbResMap ResMap,const ElementTagNames& TagNames,const string& RootTagName,const string& GroupTagName);

		XaLibGui();
		~XaLibGui();
};
#endif
