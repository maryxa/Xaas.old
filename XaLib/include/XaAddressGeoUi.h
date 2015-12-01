#ifndef XAADDRESSGEOUI_H
#define XAADDRESSGEOUI_H

#include <XaLibAction.h>

class XaAddressGeoUi : public XaLibAction {
	
    private:

        void Dispatcher(const string &CalledEvent);
        void CreateFrm();
        void Create();
        void List();

    protected:

    public:
        XaAddressGeoUi();
        ~XaAddressGeoUi();
};
#endif