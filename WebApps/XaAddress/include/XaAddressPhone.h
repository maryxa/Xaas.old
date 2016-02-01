#ifndef XAADDRESSPHONE_H
#define XAADDRESSPHONE_H

#include <XaLibModel.h>

class XaAddressPhone : public XaLibModel {

    private:		

        //vector<string> PropsName;
        //vector<string> PropsValue;
        //vector<string> PropsType;
        
        void Create();
        void Read();
        void Update();
        void Delete();
        void List();

    protected:

    public:

        void Dispatcher (const string &CalledEvent);

        XaAddressPhone();
        ~XaAddressPhone();
};
#endif