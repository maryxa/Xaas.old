#ifndef XAADDRESSMAILTYPE_H
#define XAADDRESSMAILTYPE_H

#include <XaLibModel.h>

class XaAddressMailType : public XaLibModel {

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

        XaAddressMailType();
        ~XaAddressMailType();
};
#endif