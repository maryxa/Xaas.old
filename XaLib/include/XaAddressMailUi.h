#ifndef XAADDRESSMAILUI_H
#define XAADDRESSMAILUI_H

#include <XaLibAction.h>

class XaAddressMailUi : public XaLibAction {
	
    private:

        void Dispatcher(const string &CalledEvent);
        void CreateFrm();
        void Create();
        void List();

    protected:

    public:
        XaAddressMailUi();
        ~XaAddressMailUi();
};
#endif