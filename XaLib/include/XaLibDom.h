#ifndef XALIBDOM_H
#define XALIBDOM_H

#include <XaLibBase.h>
#include <XaLibLog.h>
#include <XaLibChar.h>

extern XaLibLog LOG;

class XaLibDom : protected XaLibBase {

	private:
		
		typedef vector<string> VectorXPathExpr;
		typedef vector<string> VectorXPathValue;
		
        typedef vector<string> VectorXmlFilePath;
        typedef vector<string> VectorXmlString;
        
		xmlXPathContextPtr xpathCtx; 
    	xmlXPathObjectPtr xpathObj;
		
		typedef map<int, map<string,string> > ParamFromDomMap;
		ParamFromDomMap ParamFromDom;
		
		typedef vector<string> VectorKey;
		
		void UpdateValue(xmlDocPtr XmlDomDoc, const xmlChar* xpathExpr, const xmlChar* value);
		void UpdateXpathNodes(xmlNodeSetPtr nodes, const xmlChar* value);
		
	public:

		XaLibDom();
		~XaLibDom();

		xmlDocPtr DomFromFile(string XmlFilePath);
		static xmlDocPtr DomFromString(string XmlString);
        static xmlDocPtr DomFromStringAndFile(const VectorXmlFilePath& XmlFiles,const VectorXmlString& XmlStrings,const int& AddRootTag);

		string StringFromDom(xmlDocPtr XmlDomDoc);

		string GetRootValue(xmlDocPtr XmlDomDoc);
		static string GetElementValueByXPath(xmlDocPtr XmlDomDoc,string XPathExpr);

		string GetNumRowByXPath(xmlDocPtr XmlDomDoc,string XPathExpr);
		int GetNumRowByXPathInt(xmlDocPtr XmlDomDoc,string XPathExpr);

		ParamFromDomMap MapParamFromDom       (xmlDocPtr XmlDomDoc, VectorKey VectorKey, string SearchStartTag, string RecursiveTag);
		ParamFromDomMap MapParamFromDomByXPath(xmlDocPtr XmlDomDoc, VectorKey VectorKey, string XPathExpr, string SearchStartTag, string RecursiveTag);

		void ParseParamFromDom (xmlDocPtr doc, xmlNodePtr cur, VectorKey VectorKey,int counter);

		

		void UpdateElementValueByXPath(xmlDocPtr XmlDomDoc, VectorXPathExpr XPathExpr, VectorXPathValue XPathValue);

		void AddAddressElementByXPath(xmlDocPtr XmlDomDoc, string XPathExpr, string Id, string Type,string Value);
		void AddDeviceElementByXPath(xmlDocPtr XmlDomDoc, string XPathExpr, string Id, string Active);
		void AddDateElementByXPath(xmlDocPtr XmlDomDoc, string XPathExpr, string Value);
		void AddOptionElementByXPath (xmlDocPtr XmlDomDoc, string XPathExpr, string OptionLabel, string OptionValue);
		void AddValueElementByXPath(xmlDocPtr XmlDomDoc, string XPathExpr, string ValueValue);
		void AddOrgTreeOu(xmlDocPtr XmlDomDoc, string XPathExpr, string OuId, string OuName, string XaUserType_ID);
		void AddOrgTreeUser(xmlDocPtr XmlDomDoc, string XPathExpr, string OuId, string OuName);
		void AddOrgTreeUser(xmlDocPtr XmlDomDoc, string XPathExpr, string OuId, string OuName, string Department,string JobTitle);

		/*
		void AddElementValueByXPath(xmlDocPtr XmlDomDoc, VectorXPathExpr XPathExpr, VectorXPathValue XPathValue);
		void __AddValue(xmlDocPtr XmlDomDoc, const xmlChar* xpathExpr, const xmlChar* value);
		void __AddXpathNodes(xmlNodeSetPtr nodes, const xmlChar* value);
		*/
	protected:

};
#endif
