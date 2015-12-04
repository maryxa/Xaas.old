#ifndef XAADDRESSMAIL_H
#define XAADDRESSMAIL_H

#include <XaLibModel.h>

class XaAddressMail : public XaLibModel {

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

        XaAddressMail();
        ~XaAddressMail();
};
#endif