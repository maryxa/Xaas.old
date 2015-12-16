#ifndef XAADDRESSGEOTYPE_H
#define XAADDRESSGEOTYPE_H

#include <XaLibModel.h>

class XaAddressGeoType : public XaLibModel {

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

        XaAddressGeoType();
        ~XaAddressGeoType();
};
#endif