#ifndef XAOUUI_H
#define XAOUUI_H

#include <XaLibAction.h>

class XaOuUi : public XaLibAction {
	
    private:

        void Dispatcher(const string &CalledEvent);
        void Tree();
        void Explorer();

    protected:

    public:

        XaOuUi();
        ~XaOuUi();
};
#endif
