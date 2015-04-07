#ifndef XALIBSQL_H
#define XALIBSQL_H

#include <XaLibBase.h>
#include <XaLibDb.h>
#include <XaLibChar.h>

extern XaLibLog LOG;
extern XaSettings SETTINGS;

class XaLibSql : protected XaLibBase {

	private:
		//shared_ptr<XaLibLog> LibLog;
		//XaLibLog* LocalLibLog;
		//ofstream* LocalMyLogFile;

		typedef map<string, string> ParamsConfigurationMap;
		ParamsConfigurationMap LocalParamsConfiguration;

		typedef vector<string> VectorFields;
		typedef vector<string> VectorValues;

		typedef vector<string> ReturnedFields;

		typedef vector<string> WhereFields;
		typedef vector<string> WhereValues;

		typedef vector<string> OrderByFields;

		typedef vector<string> GroupByFields;

		//typedef vector<string> VectorRowIds;

		
	protected:

	public:

		XaLibSql();
		
		~XaLibSql();

		int Insert(XaLibDb& LibDb,string TableName,VectorFields VectorFields,VectorValues VectorValues);
		int InsertMulti(XaLibDb& LibDb,string TableName,VectorFields VectorFields,vector<vector<string> > VectorValues);
		int Update(XaLibDb& LibDb,string TableName,VectorFields VectorFields,VectorValues VectorValues,WhereFields WhereFields,WhereValues WhereValues);
		
		int Delete(XaLibDb& LibDb,string TableName, WhereFields WhereFields,WhereValues WhereValues);
		void DeleteOne(XaLibDb& LibDb,string TableName,string RowId);
		int DeleteOneLogic(XaLibDb& LibDb,string TableName,string RowId);
		int DeleteOneLogicWithKey(XaLibDb& LibDb,string TableName,string RowId,string KeyTable,string KeyId);

		DbResMap SelectOne(XaLibDb& LibDb,string TableName, int RowId);
		DbResMap SelectOne(XaLibDb& LibDb,string TableName, int RowId,int Active, int Deleted);

		DbResMap Select(XaLibDb& LibDb,string TableName,ReturnedFields ReturnedFields,WhereFields WhereFields, WhereValues WhereValues);
		DbResMap Select(XaLibDb& LibDb,string TableName,ReturnedFields ReturnedFields,WhereFields WhereFields, WhereValues WhereValues, OrderByFields OrderByFields);
		DbResMap Select(XaLibDb& LibDb,string TableName,ReturnedFields ReturnedFields,WhereFields WhereFields, WhereValues WhereValues, OrderByFields OrderByFields, GroupByFields GroupByFields);

		DbResMap FreeQuery(XaLibDb&LibDb,string SqlQry);
		void FreeQueryNoRes(XaLibDb& LibDb,string SqlQry);

		//LOCKING AND TRANSACTION
		void LockTable(XaLibDb& LibDb,string TableName);
		void UnlockTable(XaLibDb& LibDb);

		void TransactionStart(XaLibDb& LibDb);
		void TransactionCommit(XaLibDb& LibDb);
		void TransactionRollback(XaLibDb& LibDb);
};
#endif
