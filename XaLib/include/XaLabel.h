#ifndef XALABEL_H
#define XALABEL_H

//#include <XaLibAction.h>
#include <XaLibModel.h>

//class XaLabel : public XaLibAction {
class XaLabel : public XaLibModel {

    private:

		void Dispatcher(const string &CalledEvent);

				
		void XaTranslationAddFrm();
		void XaTranslationAdd();

		//void XaLabelGen();
		
		void XaLabelAddFrm();
		void Create();
                void Read();
                void Delete();
                void Update();
		
		void XaLabelList();
		
		void XaLabelMod();
		
		void XaLabelFromFileAddFrm();
		void XaLabelFromFileAdd();
		
		void XaLabelInsertLabel(string NameLabel);
		
		void XaLabelFromXaDomainGen();
		
		void XaLabelInsertLabelFromXaDomain(string NameLabel,string TextLabel);

	protected:

	public:
                void XaLabelGen();
            
		XaLabel();
		~XaLabel();
};
#endif
