#ifndef XALIBTOKEN_H
#define XALIBTOKEN_H

#include <XaLibBase.h>
#include <XaLibDb.h>
#include <XaLibSql.h>
#include <XaLibTime.h>

extern XaLibLog LOG;
extern XaLibDb DB_SESSION;
extern XaSettings SETTINGS;
extern XaSession SESSION;

//extern XaRequest REQUEST;

class XaLibToken : protected XaLibBase {

	private:

		string GenerateToken();

	protected:

	public:
		
		static int ValidateToken (const string& Token);
		
		/**
		* Check if the User already has valid Token and asks Log In\n
		* During a Login this method check if the user already has a Valid Token\n
		* If the User already has a Valid Token the old one will be overrided\n
		* 
		* @param XaUser_ID the correspondent user id for the account
		* 
		* @return int the corrisponding User Token table ID
		*
		* @code
		* int TableId=CheckUserToken(XY);
		* @endcode
		*
		*/
		static int CheckUserToken(const int& XaUser_ID);

		string CreateToken (const int& XaUser_ID);
		
		XaLibToken();
		~XaLibToken();
};
#endif