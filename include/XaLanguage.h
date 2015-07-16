#ifndef XALANGUAGE_H
#define XALANGUAGE_H

#include <XaLibAction.h>

class XaLanguage : public XaLibAction {

    private:

		void Dispatcher(const string &CalledEvent);
				
		void XaLanguageAddFrm();
		void XaLanguageAdd();

		void XaLanguageGen();
		
		void XaLanguageList();
		
		void XaLanguageMod();

	protected:

	public:

		XaLanguage();
		~XaLanguage();

};
#endif
