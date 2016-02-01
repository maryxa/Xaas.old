#ifndef XAADDRESSPHONECODE_H
#define XAADDRESSPHONECODE_H

#include <XaLibModel.h>

class XaAddressPhoneCode : public XaLibModel {

    private:		

        //vector<string> PropsName;
        //vector<string> PropsValue;
        //vector<string> PropsType;
        
        void Create();
        void Read();
        void Update();
        void Delete();
        void List();
        void ListAsOptions();

    protected:

    public:

        void Dispatcher (const string &CalledEvent);

        XaAddressPhoneCode();
        ~XaAddressPhoneCode();
};
#endif