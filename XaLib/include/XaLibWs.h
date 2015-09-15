#ifndef XALIBWS_H
#define XALIBWS_H

#include <XaLibSql.h>

//extern XaSettings SETTINGS;
//extern XaRequest REQUEST;
//extern XaResponse RESPONSE;


/**
 * @brief Web Services Implementation
 *
 * @details Web Services Implementation:
 * Manage the Web Service life cycle 
 *
 * @see XaLibBase
 * @see XaLibControllerBackEnd
 * 
 * @see http://www.xallegro.com
 * @author Alessandro Mariotti - alex@xallegro.com
*/

class XaLibWs : protected XaLibBase {

    private:

		string ReqType={""};
		string Encoding={""};
		string Encryption={""};

		
		string ConsumerId={""};
		string ConsumerKey={""};
		//string ConsumerName={""};
	
		string ResType={""};
		string Data={""};

		string Username={""};
		string Password={""};
		string Token={""};

		string Object={""};
		string Event={""};

		map <int, map<string,string> > Params;

		/**
		* Check the required parameter for a standard Web Service Call\n
		* The required parameter for a standard Web Service Call are:\n
		* Data
		* ReqType
		* Encoding
		* Encryption
		* ConsumerId
		* ResType
		*
		* @return Void
		*
		*/
		void CheckRequired();
		void GetEncodedData();
		void GetConsumerKey();
		void GetDecryptedData();

		void ExtractData();

	protected:

	public:

		void Setup();
		
		string GetObject();
		string GetEvent();
		string GetUsername();
		string GetPassword();
		string GetToken();
		string GetResType();

		map <int, map<string,string> > GetParams();

		int CheckCaller(const string &CallerName,const string &CallerKey);
		XaLibWs();
		~XaLibWs();
};
#endif