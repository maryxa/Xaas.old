

#ifndef XALIBSQL_H
#define XALIBSQL_H

#include <XaLibBase.h>
#include <XaLibDb.h>
#include <XaLibLog.h>

extern XaLibLog LOG;
extern XaSettings SETTINGS;

/**
 * @brief Abstraction layer for database interaction
 *
 * @details Database interaction:
 * this class implements Sql statements, the database connection is established from the controller. 
 *
 * @ref XaLidDb
 * @see XaLidController
 * 
 * 
 * @see http://www.xallegro.com
 * @author Alessandro Mariotti
*/

class XaLibSql : protected XaLibBase {

	private:

		typedef vector<string> VectorFields;
		typedef vector<string> VectorValues;

		typedef vector<string> ReturnedFields;

		typedef vector<string> WhereFields;
		typedef vector<string> WhereValues;

		typedef vector<string> OrderByFields;
		typedef vector<string> GroupByFields;

	protected:

	public:

		XaLibSql();
		~XaLibSql();

		/**
		* Adds new record to database.
		*
		* @param LibDb Active database connection
		* @param TableName Database Table Name
		* @param VectorFields vector<string> containing names of table fields
		* @param VectorValues vector<string> containing values of table fields
		* @return the inserted record ID
		*
		* Example Usage: INSERT INTO MyTable (name,description) VALUES ("Name", "Description");
		*
		* @code
		*
		* string Name=HTTP.GetHttpParam("Name");
		* string Description=HTTP.GetHttpParam("Description");
		* 
		* vector<string> VectorFields ={"name","description"}; 
		* vector<string> VectorValues ={Name,Description};
		*
		* int NextId=XaLibSql::Insert(DB_WRITE,"MyTable",VectorFields,VectorValues);
		* 
		* @endcode
		*
		*/
		static int Insert(XaLibDb& LibDb,string TableName,VectorFields VectorFields,VectorValues VectorValues);
		int InsertMulti(XaLibDb& LibDb,string TableName,VectorFields VectorFields,vector<vector<string> > VectorValues);
		static int Update(XaLibDb& LibDb,string TableName,VectorFields VectorFields,VectorValues VectorValues,WhereFields WhereFields,WhereValues WhereValues);
		
		static int Delete(XaLibDb& LibDb,string TableName, WhereFields WhereFields,WhereValues WhereValues);
		static void DeleteOne(XaLibDb& LibDb,string TableName,string RowId);
		static int DeleteOneLogic(XaLibDb& LibDb,string TableName,string RowId);
		static int DeleteOneLogicWithKey(XaLibDb& LibDb,string TableName,string RowId,string KeyTable,string KeyId);

		static DbResMap SelectOne(XaLibDb& LibDb,string TableName, int RowId);
		static DbResMap SelectOne(XaLibDb& LibDb,string TableName, int RowId,int Active, int Deleted);

		static DbResMap Select(XaLibDb& LibDb,const string& TableName,const ReturnedFields& ReturnedFields);
		static DbResMap Select(XaLibDb& LibDb,const string& TableName,const ReturnedFields& ReturnedFields,const WhereFields& WhereFields, const WhereValues& WhereValues);
		static DbResMap Select(XaLibDb& LibDb,string TableName,ReturnedFields ReturnedFields,WhereFields WhereFields, WhereValues WhereValues, OrderByFields OrderByFields);
		static DbResMap Select(XaLibDb& LibDb,string TableName,ReturnedFields ReturnedFields,WhereFields WhereFields, WhereValues WhereValues, OrderByFields OrderByFields, GroupByFields GroupByFields);

		static DbResMap FreeQuery(XaLibDb&LibDb,string SqlQry);
		static void FreeQueryNoRes(XaLibDb& LibDb,string SqlQry);

		//LOCKING AND TRANSACTION
		static void LockTable(XaLibDb& LibDb,string TableName);
		static void UnlockTable(XaLibDb& LibDb);

		static void TransactionStart(XaLibDb& LibDb);
		static void TransactionCommit(XaLibDb& LibDb);
		static void TransactionRollback(XaLibDb& LibDb);
};
#endif
