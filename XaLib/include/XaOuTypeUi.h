#ifndef XAOUTYPEUI_H
#define XAOUTYPEUI_H

#include <XaLibAction.h>

class XaOuTypeUi : public XaLibAction {
	
    private:

        void Dispatcher(const string &CalledEvent);
        void CreateFrm();

    protected:

    public:
        XaOuTypeUi();
        ~XaOuTypeUi();
};
#endif