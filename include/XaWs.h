#ifndef XAWS_H
#define XAWS_H

#include <XaLibAction.h>

extern XaSettings SETTINGS;
extern XaRequest REQUEST;
extern XaResponse RESPONSE;

class XaWs : public XaLibAction {

    private:

		void Dispatcher(const string &CalledEvent);

		void List();

	protected:

	public:
		
		int CheckCaller(const string &CallerName,const string &CallerKey);
		XaWs();
		~XaWs();
};
#endif