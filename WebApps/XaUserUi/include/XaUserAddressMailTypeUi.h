#ifndef XAUSERADDRESSMAILTYPEUI_H
#define XAUSERADDRESSMAILTYPEUI_H

#include <XaLibAction.h>

class XaUserAddressMailTypeUi : public XaLibAction {
	
    private:
        void Dispatcher(const string &CalledEvent);
        void CreateFrm();
        void Create();
        
        void ListAsOptions();

	void UpdateFrm();
	void Update();

    protected:

    public:

        XaUserAddressMailTypeUi();
        ~XaUserAddressMailTypeUi();
};
#endif
