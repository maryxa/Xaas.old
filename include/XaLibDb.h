#ifndef XALIBDB_H
#define XALIBDB_H

#include <XaLibBase.h>

#ifdef _WIN32
	#include <winsock2.h>
#endif

#include <XaLibLog.h>
#include <mysql.h>

extern XaLibLog LOG;
extern XaSettings SETTINGS;

class XaLibDb : private XaLibBase {

	private:
		//DbResMap DbRes;
		//XaLibBase::ParamsMap ParamsConfigurationDb;
		/*
		XaLibLog* LibLogDb;
		ofstream* MyLogFileDb;
		*/

		MYSQL* ConnWrite;
        MYSQL* ConnRead;
        MYSQL* ConnSession;

		int ActiveConnection;

		XaLibDb* LibDbSession;
		XaLibDb* LibDbRead;
		XaLibDb* LibDbWrite;

		

	protected:

	public:

		XaLibDb();
		~XaLibDb();

		void Connect(int DbType);

		int ExInsert(string SqlQry);
		int ExUpdate(string SqlQry);
		int ExDelete(string SqlQry);
		DbResMap ExSelect(string SqlQry);
		DbResMap RetrieveRows(MYSQL_RES *DbResult); 

        int ExSystemQry(string SqlQry);
		//DbResMap ExSelectSession(string SqlQry);
		//int ExInsertSession(string SqlQry);
};
#endif