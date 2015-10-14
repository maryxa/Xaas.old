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
#include <XaLibGui.h>
//#include <XaLibWebSocket.h>



//SUPERGLOBALS VARIABLES

extern XaLibLog LOG;
extern XaLibHttp HTTP;
//extern XaLibDb DB_SESSION;
extern XaLibDb DB_READ;
extern XaLibDb DB_WRITE;
extern XaLibDb DB_LOG;

extern XaSession SESSION;
extern XaRequest REQUEST;
extern XaResponse RESPONSE;
extern XaSettings SETTINGS;

/**
 * @brief Parent Class for View actions
 *
 * @details Parent Class for View actions:
 * All action class inherit from this class
 *
 * @see XaLibBase
 * 
 * @see alex@xallegro.com
 * @author Alessandro Mariotti
*/

class XaLibAction : protected XaLibBase {

    private:

    protected:
        string NowTimeMysql;
	string TodayMysql;

        vector<string> XmlFiles;
        vector<string> XmlStrings;

        vector<string> XslFiles;
        vector<string> XslStrings;

        vector<string> XmlFields;
        vector<string> XmlValues;
	vector<string> XslParams;

        vector<string> OptionReturnedFields;
        vector<string> OptionWhereFields;
	vector<string> OptionWhereValues;
	vector<string> OptionOrderByFields;

        typedef map<int, map<string,string> > ParamFromDomMap;

        /**
        * Adds file to vector<string> XmlFiles\n
        * All files in the vector will be added in the generated Dom Object.\n
        * The search order for the file:\n
        * 1) Application Xml Directory SETTINGS["XmlDir"]\n
        * 2) Common shared Directory SETTINGS["SharedDir"]+"/xml/"\n
        * The 2 parameters: SharedDir and XmlDir are configurable in the configuration file\n
        * 
        * @param FilePath the name of the file
        * 
        * @return void
        *
        * @code
        * AddXmlFile("MyXml");
        * @endcode
        *
        */
        void AddXmlFile   (const string& FilePath);

        /**
        * 
        * Adds a well formed XML string to the vector<string> XmlStrings\n
        * All strings in the vector will be added in the generated Dom Object.\n
        * 
        * @param XmlString the XmlString
        * 
        * @return void
        *
        * @code
        * string xml="<name>MyName</name>";
        *
        * AddXmlString(xml);
        * @endcode
        *
        */
        void AddXmlString (const string& XmlString);

        /**
        * Adds file to the vector<string> XslFiles\n
        * All files in the vector will be added in the generated Dom Object.\n
        * The search order for the file:\n
        * 1) Application Xsl Directory SETTINGS["XslDir"]\n
        * 2) Common shared Directory SETTINGS["SharedDir"]+"/xsl/"\n
        * The 2 parameters: SharedDir and XslDir are configurable in the configuration file\n
        * 
        * @param FilePath the name of the file
        * 
        * @return void
        *
        * @code
        * AddXslFile("MyXsl");
        * @endcode
        *
        */
        void AddXslFile   (const string& FilePath);

        /**
        * 
        * Adds a well formed XSL string to the vector<string> XslStrings\n
        * All strings in the vector will be added in the generated Dom Object.\n
        * 
        * @param XslString the XslString
        * 
        * @return void
        *
        * @code
        * AddXmlString(xsl);
        * @endcode
        *
        */
        void AddXslString (const string& XslString);

        /**
        * Adds to the Vector vector<string> XslParams common variables to passe at the XSTL parser .\n
        * Variables as set as name and value and statically defined in the class\n
        * todo: move in a  configuration file\n
        * 
        * @return void
        *
        * @code
        * AddXslParamCommon();
        * @endcode
        *
        */
        void AddXslParamCommon();

        /**
        * Adds to the Vector vector<string> XslParams a variable .\n
        * Variables has set with name and value\n
        * 
        * @param ParamName the Variable Name
        * @param ParamValue the Variable Value
        * 
        * @return void
        *
        * @code
        * AddXslParam("name", "value");
        * @endcode
        *
        */
        void AddXslParam (const string& ParamName, const string& ParamValue);

        /**
        * Dispatch Event in the object\n
        * The Class Name is representing the Object and the Method name is representing the Event\n
        * 
        * @param CalledEvent the Called Event (class Method)
        * 
        * @return void
        *
        * @code
        * Dispatcher("EventName");
        * @endcode
        *
        */
        virtual void Dispatcher (const string &CalledEvent);

        /**
        * Selects the layout for the returned page\n
        * A layout is a collection of Xsl file, based on passed layout are added different files\n
        * 
        * @param LayoutType the layout name
        * 
        * @return void
        *
        * @code
        * SetLayout("Default");
        * @endcode
        *
        */
        void SetLayout (const string &LayoutType);

        /**
        * Builds the XML for the Back End Call\n
        * The general structure is :\n
        * @code
        * <WsData>
        *   <login>
        *       <token>[TOKEN]</token>
        *   </login>
        *   <operation>
        *       <object>XaUser</object>
        *       <event>Logout</event>
        *   </operation>
        *   <params>
        *       <p>
        *           <n></n>
        *           <v></v>
        *       </p>
        *   </params>
        * </WsData>
        * @endcode
        * 
        * @param Object Back End Object to call
        * @param Event Back End Event to call
        * @param ParamName Parameter Names to send with the Call
        * @param ParamValue Parameter Values to send with the Call
        * 
        * @return string
        *
        * @code
        * BuildBackEndCall("XaUser", "Logout",{},{};
        * @endcode
        *
        */
        string BuildBackEndCall(const string& Object, const string& Event,const vector <string>& ParamName,const vector <string>& ParamValue);
        string BuildBackEndCallLogin(const string& Username, const string& Password);
        string BuildBackEndCallBase();
        string BuildBackEndCallSectionOperation(const string& Object, const string& Event);
        string BuildBackEndCallSectionParams(const vector<string>& Names, const vector<string>& Values);

        /**
        * Redirects to the InfoPage .\n
        * To Use with classes that provide the Method GetResponse\n
        * @param ErrorType Type of Error
        * @return void
        *
        * @code
        * ErrorPage ("EventNotfound");
        * @endcode
        *
        */
        /*
        void ErrorPage (const string& ErrorType);
*/
        /**
        * Redirects to the InfoPage and return the control to the Controller.\n
        * To Use with classes that don't provide the Method GetResponse\n
        * @param ErrorType Type of Error
        * @return void
        *
        * @code
        * ErrorExit ("EventNotfound");
        * @endcode
        *
        */
/*
        void ErrorExit (const string& ErrorType);

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

        string EncryptParam(string ClearValue);
        string EncryptParam(int ClearValue);
        string DecryptParam(string EncryptedValue);
        string DecryptParamId(string EncryptedValue);


        void UpdateSessionWsLog (const string &XaSessionWsLog_ID,const string &LogData,const string &Response);

        string ComposeSearchCondition(string Value,string Field,string Type);



        void ResetRequest();
*/
    public:

		/**
		* Execute the Object Dispatcher\n
		* Execute the Object Dispatcher passing the Event Name\n
		* 
		* @return void
		*
		* @code
		* Execute("");
		* @endcode
		*
		*/
		void Execute();

		//void virtual GetResponse();

		XaLibAction ();
		virtual ~XaLibAction ();

};
#endif
