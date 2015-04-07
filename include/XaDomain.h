#ifndef XADOMAIN_H
#define XADOMAIN_H

#include <XaLibAction.h>

using namespace std;

class XaDomain : public XaLibAction {

    private:

		void Dispatcher(string CalledEvent);

		void XaDomainRowAddFrm();
		void XaDomainRowAdd();

		void XaDomainList();

		void XaDomainAddFrm();
		void XaDomainAdd();

		void AddOptionsAllDomain(XaLibDom* LibDom,xmlDocPtr XmlDomDoc,string XPathExpr);

	protected:

	public:

		XaDomain();
		~XaDomain();
};
#endif
