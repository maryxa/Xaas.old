#ifndef XALIBACTION_H
#define XALIBACTION_H

#include <XaLibBase.h>
#include <XaLibHttp.h>
#include <XaLibConfig.h>
#include <XaLibLog.h>
#include <XaLibDb.h>
#include <XaLibDom.h>
#include <XaLibXsl.h>
#include <XaLibSql.h>
#include <XaLibChar.h>
#include <XaLibCrypto.h>
#include <XaLibSession.h>
#include <XaLibMail.h>
#include <XaLibTime.h>
#include <XaLibCurl.h>


//SUPERGLOBALS VARIABLES

extern XaLibLog LOG;
extern XaLibHttp HTTP;
//extern XaLibDb DB_SESSION;
extern XaLibDb DB_READ;
extern XaLibDb DB_WRITE;
extern XaLibSession SESSION;
extern XaRequest REQUEST;
extern XaResponse RESPONSE;
extern XaSettings SETTINGS;

class XaLibAction : protected XaLibBase {

	private:

    protected:
		string NowTimeMysql;
		string TodayMysql;

        typedef vector<string> VectorFilePaths;
        typedef vector<string> VectorStrings;

        VectorFilePaths XmlFilePaths;
        VectorStrings   XmlStrings;

        VectorFilePaths XslFilePaths;
        VectorStrings   XslStrings;

		typedef vector<string> VectorXmlFields;
        typedef vector<string> VectorXmlValues;

		VectorXmlFields XmlFields;
		VectorXmlValues XmlValues;

		vector<string> OptionReturnedFields;
		vector<string> OptionWhereFields;
		vector<string> OptionWhereValues;
		vector<string> OptionOrderByFields;

		typedef map<int, map<string,string> > ParamFromDomMap;

		void AddXmlPath   (string FilePath);
		void AddXmlString (string XmlString);
		void AddXslPath   (string FilePath);
		void AddXslString (string XslString);

		void   AddOptionsByDb                      (XaLibDom* LibDom,xmlDocPtr XmlDomDoc,string TableName,string XPathExpr);
		void   AddOptionsByDb                      (XaLibDom* LibDom,xmlDocPtr XmlDomDoc,string TableName,string XPathExpr,string OptionValueField,string OptionLabelField);
		void   AddOptionsByDbWithCondition         (XaLibDom* LibDom,xmlDocPtr XmlDomDoc,string TableName,string XPathExpr,string Condition);
		void   AddOptionsByDomain                  (XaLibDom* LibDom,xmlDocPtr XmlDomDoc,string XaDomain,string XPathExpr);
		void   AddOptionsByDomainAndUser           (XaLibDom* LibDom,xmlDocPtr XmlDomDoc,string XaDomain,string StrUserId, string XPathExpr);
		void   AddOptionsByDomainWithDescription   (XaLibDom* LibDom,xmlDocPtr XmlDomDoc,string XaDomain,string XPathExpr);
		void   AddOptionsByVectors                 (XaLibDom* LibDom,xmlDocPtr XmlDomDoc,string XPathExpr);
		void   AddValuesByDb                       (XaLibDom* LibDom,xmlDocPtr XmlDomDoc,string TableName,string XPathExpr);
		string SelectDbItem                        (string ID,string TableName);
		string SelectDomainItem                    (string XaDomain_ID);
        int    SelectDomainItemIdFromName          (string domain, string name);
		string SelectUserItem		               (string XaUser_ID);

		string HttpParamValidation (string ParamName, string ParamValue, string DataType, string Required, string Dimension, string Domain, string DefaultValue);
		void ErrorExit(string ErrorPage,string ErrorCode);

		string EncryptParam(string ClearValue);
		string EncryptParam(int ClearValue);
		string DecryptParam(string EncryptedValue);
		string DecryptParamId(string EncryptedValue);

		void SetLayout (const string &LayoutType);
		void UpdateSessionWsLog (const string &XaSessionWsLog_ID,const string &LogData,const string &Response);

		string ComposeSearchCondition(string Value,string Field,string Type);

		virtual void Dispatcher (const string &CalledEvent);

		void ResetRequest();

    public:

		void virtual GetResponse();

		XaLibAction ();
		virtual ~XaLibAction ();

};
#endif
