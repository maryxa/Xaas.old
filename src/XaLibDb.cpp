#include <XaLibDb.h>
#include <XaLibBase.h>
#include "XaLibChar.h"

/**
* Instannce of XaLibDb
* @param ParamsConfiguration - ParamsConfigurationMap - System Configuration
* @param LibLog - XaLibLog* - log Library
* @param MyLogFile - ofstream* - log stream file
* @param DbType - int - 1:=write 2:=read 3:=session
* @see
* @return void
*/

XaLibDb::XaLibDb(){
};

void XaLibDb::Connect(int DbType) {

    if (DbType==1){
		
		this->ActiveConnection=1;

		const char* DbHost=SETTINGS["DbWriteHost"].c_str();
		const char* DbDatabase=SETTINGS["DbWriteDatabase"].c_str();
		const char* DbUser=SETTINGS["DbWriteUser"].c_str();
		const char* DbPassword=SETTINGS["DbWritePassword"].c_str();

        unsigned int DbPort=atoi(SETTINGS["DbWritePort"].c_str());
            
        ConnWrite = mysql_init(NULL);

        if (mysql_real_connect(ConnWrite, DbHost, DbUser, DbPassword, DbDatabase, DbPort, NULL, 0)==NULL){

            LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Database Write Connection Problem->"+SETTINGS["DbWriteDatabase"]+" at->" + SETTINGS["DbWriteHost"]);

			XaLibBase::SendHtmlHeaders();
            printf("Error %u: %s\n", mysql_errno(ConnWrite), mysql_error(ConnWrite));
			cout<< "Database Session Connection Problem->"+SETTINGS["DbWriteDatabase"]+" at->" + SETTINGS["DbWriteHost"]<<endl;
			
        } else {

            LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Database Write Connection -> "+SETTINGS["DbWriteDatabase"]+" at->" + SETTINGS["DbWriteHost"]);
        }
        
    } else if (DbType==2){
    
		this->ActiveConnection=2;

		const char* DbHost=SETTINGS["DbReadHost"].c_str();
		const char* DbDatabase=SETTINGS["DbReadDatabase"].c_str();
		const char* DbUser=SETTINGS["DbReadUser"].c_str();
		const char* DbPassword=SETTINGS["DbReadPassword"].c_str();

        unsigned int DbPort=atoi(SETTINGS["DbReadPort"].c_str());

        ConnRead = mysql_init(NULL);

        if (mysql_real_connect(ConnRead, DbHost, DbUser, DbPassword, DbDatabase, DbPort, NULL, 0)==NULL){

            LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Database Read Connection Problem->"+SETTINGS["DbReadDatabase"]+" at->" + SETTINGS["DbReadHost"]);
			
			XaLibBase::SendHtmlHeaders();
            printf("Error %u: %s\n", mysql_errno(ConnRead), mysql_error(ConnRead));	
			cout<< "Database Session Connection Problem->"+SETTINGS["DbReadDatabase"]+" at->" + SETTINGS["DbReadHost"]<<endl;
			
        } else {

            LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Database Read Connection -> "+SETTINGS["DbReadDatabase"]+" at->" + SETTINGS["DbReadHost"]);
        }

    } else if (DbType==3){
        
		this->ActiveConnection=3;

		const char* DbHost=SETTINGS["DbSessionHost"].c_str();
		const char* DbDatabase=SETTINGS["DbSessionDatabase"].c_str();
		const char* DbUser=SETTINGS["DbSessionUser"].c_str();
		const char* DbPassword=SETTINGS["DbSessionPassword"].c_str();

        unsigned int DbPort=atoi(SETTINGS["DbSessionPort"].c_str());

        ConnSession = mysql_init(NULL);

        if (mysql_real_connect(ConnSession, DbHost, DbUser, DbPassword, DbDatabase, DbPort, NULL, 0)==NULL){

            LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Database Session Connection Problem->"+SETTINGS["DbSessionDatabase"]+" at->" + SETTINGS["DbSessionHost"]);

			XaLibBase::SendHtmlHeaders();
			printf("Error %u: %s\n", mysql_errno(ConnSession), mysql_error(ConnSession));	
			cout<< "Database Session Connection Problem->"+SETTINGS["DbSessionDatabase"]+" at->" + SETTINGS["DbSessionHost"]<<endl;

        } else {

            LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Database Session Connection -> "+SETTINGS["DbSessionDatabase"]+" at->" + SETTINGS["DbSessionHost"]);
        }
    
    } else {

        LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"DbType is not valid");

    }

};

int XaLibDb::ExInsert(string SqlQry) {

	string qry=SqlQry;
	const char *cstr = qry.c_str();

	if (this->ActiveConnection==1){

		mysql_query(ConnWrite,"set character_set_server='utf8'");
		mysql_query(ConnWrite,"SET NAMES 'utf8'");
		mysql_query(ConnWrite, cstr);

		return mysql_insert_id(ConnWrite);

	} else if(this->ActiveConnection==3){

		mysql_query(ConnSession,"set character_set_server='utf8'");
		mysql_query(ConnSession,"SET NAMES 'utf8'");
		mysql_query(ConnSession, cstr);

		return mysql_insert_id(ConnSession);

	} else {

		return 0;
	}

};

int XaLibDb::ExUpdate(string SqlQry) {

	string qry=SqlQry;
	const char *cstr = qry.c_str();
		
	if (this->ActiveConnection==1){

		mysql_query(ConnWrite,"set character_set_server='utf8'");
		mysql_query(ConnWrite,"SET NAMES 'utf8'");
		mysql_query(ConnWrite, cstr);

		return 1;

	} else if(this->ActiveConnection==3){

		mysql_query(ConnSession,"set character_set_server='utf8'");
		mysql_query(ConnSession,"SET NAMES 'utf8'");
		mysql_query(ConnSession, cstr);

		return 1;

	} else {

		return 0;
	}

};

int XaLibDb::ExDelete(string SqlQry) {

	string qry=SqlQry;
	const char *cstr = qry.c_str();
		
	if (this->ActiveConnection==1){

		mysql_query(ConnWrite,"set character_set_server='utf8'");
		mysql_query(ConnWrite,"SET NAMES 'utf8'");
		mysql_query(ConnWrite, cstr);

		return 1;

	} else if(this->ActiveConnection==3){

		mysql_query(ConnSession,"set character_set_server='utf8'");
		mysql_query(ConnSession,"SET NAMES 'utf8'");
		mysql_query(ConnSession, cstr);

		return 1;

	} else {

		return 0;
	}

};

XaLibDb::DbResMap XaLibDb::ExSelect(string SqlQry) {

	LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Executing Sql Query-> " + SqlQry);

	DbResMap DbRes;
	MYSQL_RES *result;

	string qry=SqlQry;
	const char *cstr = qry.c_str();

		if (this->ActiveConnection==2){

			mysql_query(ConnRead,"set character_set_server='utf8'");
			mysql_query(ConnRead,"SET NAMES 'utf8'");

			if (mysql_query(ConnRead, cstr)!=0){

				string log=qry.c_str();

				LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"ERROR Sql Query-> " + log);

				XaLibBase::SendHtmlHeaders();
				printf("Error %u: %s\n", mysql_errno(ConnSession), mysql_error(ConnSession));
				cout<< "Error occurred during execution Query-> " + log<<endl;

				DbRes.clear();
				return DbRes;

			} else {
			
				result = mysql_store_result(ConnRead);
				DbRes=this->RetrieveRows(result);
				return DbRes;
			}

		} else if(this->ActiveConnection==3){

			mysql_query(ConnSession,"set character_set_server='utf8'");
			mysql_query(ConnSession,"SET NAMES 'utf8'");

			if (mysql_query(ConnSession, cstr)!=0){

				string log=qry.c_str();

				LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Error Sql Query-> " + log);

				XaLibBase::SendHtmlHeaders();				

				printf("Error %u: %s\n", mysql_errno(ConnSession), mysql_error(ConnSession));
				cout<< "Error occurred during execution Query-> " + log<<endl;

				DbRes.clear();
				return DbRes;

			} else {

				result = mysql_store_result(ConnSession);
				DbRes=this->RetrieveRows(result);
				return DbRes;
			}

		} else {
		
			DbRes.clear();
			return DbRes;
		}
};

XaLibDb::DbResMap XaLibDb::RetrieveRows(MYSQL_RES *DbResult) {

	DbResMap DbRes;

	MYSQL_RES *result=DbResult;
	MYSQL_ROW row;
	MYSQL_FIELD *field;
	vector<string> DbResultFieldName;

		unsigned int i = 0;

		while((field = mysql_fetch_field(result))) {

			DbResultFieldName.push_back(field->name);
		}

		//int numrows = mysql_num_rows(result);
		int numfields = mysql_num_fields(result);

		XaLibChar* LibChar=new XaLibChar();
		int j=0;
		while((row = mysql_fetch_row(result))) {

			for(i = 0; i < numfields; i++){

				string val="";

				if (row[i]==NULL){
					val = "";
				} else {
					val = LibChar->ClearXmlEntitiesBasic(row[i]);
					//val = row[i];
				}

				DbRes[j][DbResultFieldName.at(i)]=val;

			}
			j++;
		}

		return DbRes;
};

int XaLibDb::ExSystemQry(string SqlQry) {

	string qry=SqlQry;
	const char *cstr = qry.c_str();

	if (this->ActiveConnection==1){

		mysql_query(ConnWrite,"set character_set_server='utf8'");
		mysql_query(ConnWrite,"SET NAMES 'utf8'");
		mysql_query(ConnWrite, cstr);

	} else if(this->ActiveConnection==2){

		mysql_query(ConnRead,"set character_set_server='utf8'");
		mysql_query(ConnRead,"SET NAMES 'utf8'");
		mysql_query(ConnRead, cstr);

	} else if(this->ActiveConnection==3){
	
		mysql_query(ConnSession,"set character_set_server='utf8'");
		mysql_query(ConnSession,"SET NAMES 'utf8'");
		mysql_query(ConnSession, cstr);
	}

	return 1;

};

XaLibDb::~XaLibDb() {

	#ifdef _WIN32

	#else

	#endif
};