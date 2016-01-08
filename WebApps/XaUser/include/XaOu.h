#ifndef XAOU_H
#define XAOU_H

#include <XaLibModel.h>

class XaOu : public XaLibModel {

    private:		

        //vector<string> PropsName;
        //vector<string> PropsValue;
        //vector<string> PropsType;

        void Create();
        void ListAsOptions();
        void Tree();
 
        //int Read();
        //int Update();
        //int Delete();

    protected:

    public:

        void Dispatcher (const string &CalledEvent);
        

        XaOu();
        ~XaOu();
};
#endif