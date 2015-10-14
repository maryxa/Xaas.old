#ifndef XALIBSESSION_H
#define XALIBSESSION_H

#include <XaLibBase.h>
#include <XaLibDb.h>
#include <XaLibSql.h>
#include <XaLibTime.h>

extern XaLibLog LOG;
extern XaLibDb DB_SESSION;
extern XaSettings SETTINGS;
extern XaRequest REQUEST;
extern XaSession SESSION;

class XaLibSession : protected XaLibBase {

	private:

        //string GenerateSessionId(int SessionIdLength);

        int GenerateSessionId();
		
	int SessionStart();
        int SessionValidate(const string& SessionId);
        string RemoveCookie();
		
        int SetSessionDbEntry(const string &SessionId,const string &SessionKey) const;
	void GenerateCookie();

	protected:

	public:
            XaLibSession();
            ~XaLibSession();

            int ManageSession(const string& SessionId);
            string SessionDestroy();

            int SetParameter(const string& SessionId, string ParamName, string ParamValue);
		string GetParameter(const string& SessionId, string ParamName);
		//int GetSessionUserId(XaLibDb* LibDbSession,string SessionId);
};
#endif