#ifndef XALIBTOKEN_H
#define XALIBTOKEN_H

#include <XaLibBase.h>
#include <XaLibDb.h>
#include <XaLibSql.h>
#include <XaLibTime.h>

extern XaLibLog LOG;
extern XaLibDb DB_SESSION;
extern XaSettings SETTINGS;
//extern XaRequest REQUEST;

class XaLibToken : protected XaLibBase {

	private:

		string GenerateToken();

	protected:

	public:
		
		int ValidateToken (const string& Token);
		string CreateToken (const int& XaUser_ID);
		
		XaLibToken();
		~XaLibToken();
};
#endif