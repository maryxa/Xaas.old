#ifndef XALANGUAGE_H
#define XALANGUAGE_H

//#include <XaLibAction.h>
#include <XaLibModel.h>

//class XaLanguage : public XaLibAction {
class XaLanguage : public XaLibModel {

    private:

        void Dispatcher(const string &CalledEvent);
				
            /*	void XaLanguageAddFrm();
		void XaLanguageAdd();

		void XaLanguageGen();
		
		void XaLanguageList();
		
		void XaLanguageMod(); */
        
        void Create();
        void Read();
        void Update();
        void Delete();
        void List();
        void XaLanguageGen();

    protected:

    public:

        XaLanguage();
        ~XaLanguage();

};
#endif
