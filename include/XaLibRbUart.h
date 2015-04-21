#ifndef XALIBRUART_H
#define XALIBRUART_H

#include <XaLibBase.h>
#include <XaLibLog.h>

extern XaLibLog LOG;

class XaLibRbUart : public XaLibBase {

	public:
		XaLibRbUart();

		string Send(const string &MsgString);

		~XaLibRbUart();

	protected:

	private:
};
 
#endif
