#ifndef XAOUTYPE_H
#define XAOUTYPE_H

#include <XaLibModel.h>

class XaOuType : public XaLibModel {

    private:
		
		void GetList();


	protected:
	

	public:

		void Dispatcher (const string &CalledEvent);

		XaOuType();
		~XaOuType();
};
#endif