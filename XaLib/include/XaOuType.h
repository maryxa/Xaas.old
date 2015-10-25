#ifndef XAOUTYPE_H
#define XAOUTYPE_H

#include <XaLibModel.h>

class XaOuType : public XaLibModel {

    private:		

        //vector<string> PropsName;
        //vector<string> PropsValue;
        //vector<string> PropsType;
        
        void Create();
        void Read();
        void Update();
        void Delete();

    protected:

    public:

        void Dispatcher (const string &CalledEvent);
      
        //int Read();
        //int Update();
        //int Delete();

        XaOuType();
        ~XaOuType();
};
#endif