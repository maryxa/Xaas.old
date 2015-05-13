#ifndef XALIBMAIL_H
#define XALIBMAIL_H

#include <string>
#include <map>
#include <vector>

#include <XaLibSocket.h>

using namespace std;

class XaLibMail {

	private:
		int SendHeaderCommon(XaLibSocket* LibSocket,int SocketNumber,string LocalDomain,string AccountUsername,string AccountPassword,string MailFromAddress,string MailToAddress,string MailFromText,string MailToText,string MailSubject,int MailConfirmation);
	protected:

	public:

		XaLibMail();
		~XaLibMail();
		int SendSysMail(string MailConfXmlFilePath,string MailAccount,string MailToAddress,string MailToText,int MailConfirmation);
		int SendMailText(string SmtpServer,int SmtpServerPort,string LocalDomain,string AccountUsername,string AccountPassword,string MailFromAddress,string MailToAddress,string MailFromText,string MailToText,string MailSubject,string MailMessage,int MailConfirmation);
};
#endif
