#ifndef XAADDRESSPHONEUI_H
#define XAADDRESSPHONEUI_H

#include <XaLibAction.h>

class XaAddressPhoneUi : public XaLibAction {
	
    private:

        void Dispatcher(const string &CalledEvent);
        void CreateFrm();
        void Create();
        void List();

    protected:

    public:
        XaAddressPhoneUi();
        ~XaAddressPhoneUi();
};
#endif