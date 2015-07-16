#ifndef XALIBMAIL_H
#define XALIBMAIL_H

#include <XaLibBase.h>
#include <XaLibLog.h>
#include <XaLibSocket.h>
#include <XaLibDom.h>

extern XaLibLog LOG;

class XaLibMail : public XaLibBase {

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
