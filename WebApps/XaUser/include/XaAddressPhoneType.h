#ifndef XAADDRESSPHONETYPE_H
#define XAADDRESSPHONETYPE_H

#include <XaLibModel.h>

class XaAddressPhoneType : public XaLibModel {

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

        XaAddressPhoneType();
        ~XaAddressPhoneType();
};
#endif