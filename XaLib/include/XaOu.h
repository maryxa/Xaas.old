#ifndef XAOU_H
#define XAOU_H

#include <XaLibModel.h>

class XaOu : public XaLibModel {

    private:		

        vector<string> PropsName;
        vector<string> PropsValue;
        vector<string> PropsType;

    protected:

    public:

        void Create();
        //int Read();
        //int Update();
        //int Delete();

        XaOu();
        ~XaOu();
};
#endif