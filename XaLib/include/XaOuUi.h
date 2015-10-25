#ifndef XAOU_H
#define XAOU_H

#include <XaLibAction.h>

class XaOu : public XaLibAction {
	
    private:

		void Dispatcher(const string &CalledEvent);
		void Tree();
		void Explorer();

	protected:

	public:

		XaOu();
		~XaOu();
};
#endif
