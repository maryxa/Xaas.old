#ifndef XAOUOBJ_H
#define XAOUOBJ_H

#include <XaLibModel.h>

class XaOuObj : public XaLibModel {

    private:		

		vector<string> PropsName;
		vector<string> PropsValue;
		vector<string> PropsType;

	protected:

	public:

		int Create();
		//int Read();
		//int Update();
		//int Delete();

		XaOuObj();
		~XaOuObj();
};
#endif