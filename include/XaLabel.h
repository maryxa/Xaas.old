#ifndef XALABEL_H
#define XALABEL_H

#include <XaLibAction.h>

class XaLabel : public XaLibAction {

    private:

		void Dispatcher(const string &CalledEvent);

				
		void XaTranslationAddFrm();
		void XaTranslationAdd();

		void XaLabelGen();
		
		void XaLabelAddFrm();
		void XaLabelAdd();
		
		void XaLabelList();
		
		void XaLabelMod();
		
		void XaLabelFromFileAddFrm();
		void XaLabelFromFileAdd();
		
		void XaLabelInsertLabel(string NameLabel);
		
		void XaLabelFromXaDomainGen();
		
		void XaLabelInsertLabelFromXaDomain(string NameLabel,string TextLabel);

	protected:

	public:

		XaLabel();
		~XaLabel();
};
#endif
