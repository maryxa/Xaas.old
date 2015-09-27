#ifndef XALIBMODEL_H
#define XALIBMODEL_H

#include <XaLibBase.h>
#include <XaLibChar.h>
#include <XaLibHttp.h>
#include <XaLibLog.h>
#include <XaLibDb.h>
#include <XaLibDom.h>
#include <XaLibSql.h>
#include <XaLibCrypto.h>

//SUPERGLOBALS VARIABLES

/*
 0 = non disattivabile
 1 = attivo
 2 = disattivo
 3 = eliminato
 */

extern XaLibLog LOG;
extern XaLibHttp HTTP;
extern XaLibDb DB_SESSION;
extern XaLibDb DB_READ;
extern XaLibDb DB_WRITE;
extern XaLibDb DB_LOG;

extern XaRequest REQUEST;
extern XaResponse RESPONSE;
extern XaSettings SETTINGS;

class XaLibModel : protected XaLibBase {

	private:

	protected:

		string DbTable;
		vector <string> Fields;
		vector <string> Values;

		vector<string> ReturnedFields;
		vector<string> WhereFields;
		vector<string> WhereValues;
		vector<string> OrderByFields;
		vector<string> GroupByFields;

		int Limit=0;

		void ResetPoperites ();

		virtual void Dispatcher (const string &CalledEvent)=0;

		string BuildXml(DbResMap& ResMap,const string& Container,const string& GroupBy);

    public:

		virtual int Create();
		virtual XaLibBase::DbResMap Read();

		void Execute();

		XaLibModel ();
		virtual ~XaLibModel ();
};
#endif
