#ifndef XAADDRESSGEO_H
#define XAADDRESSGEO_H

#include <XaLibModel.h>

class XaAddressGeo : public XaLibModel {

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

        XaAddressGeo();
        ~XaAddressGeo();
};
#endif