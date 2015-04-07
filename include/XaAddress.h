#ifndef XAADDRESS_H
#define XAADDRESS_H

#include <XaLibAction.h>

class XaAddress : public XaLibAction {

    private:

		//void XaAddressAddFrm();
		void Dispatcher(string CalledEvent);


		void XaAddressGeoAddFrm();
		void XaAddressGeoAdd();
		void XaAddressGeoModFrm();
		void XaAddressGeoList();
		void XaAddressGeoDel();

		void XaAddressPhoneAddFrm();
		void XaAddressPhoneAdd();
		void XaAddressPhoneModFrm();
		void XaAddressPhoneList();
		void XaAddressPhoneDel();

		void XaAddressMailAddFrm();
		void XaAddressMailAdd();
		void XaAddressMailModFrm();
		void XaAddressMailList();
		void XaAddressMailDel();

	protected:

	public:

		XaAddress();
		~XaAddress();

		void AddXaAddressPhoneOptionsByDb(XaLibDom* LibDom,xmlDocPtr XmlDomDoc,string XPathExpr,string XaTable,string XaField_ID,string Language);

};
#endif
