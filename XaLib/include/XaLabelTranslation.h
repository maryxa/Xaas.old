#ifndef XALABELTRANSLATION_H
#define XALABELTRANSLATION_H

#include <XaLibModel.h>

class XaLabelTranslation : public XaLibModel {

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

        XaLabelTranslation();
        ~XaLabelTranslation();
};
#endif