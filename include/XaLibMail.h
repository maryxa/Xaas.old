#ifndef XALIBMAIL_H
#define XALIBMAIL_H

#include <string>
#include <map>
#include <vector>

#include <XaLibSocket.h>

using namespace std;

/*
	XaLibMail* LibMail=new XaLibMail();
	//LibMail->SendMailText("fastwebnet.it","smt.fastwebnet.it",587,"alessandro.mariotti@fastwebnet.it","Mar1c1ca","alessandro.mariotti@fastwebnet.it","alex@xallegro.com","Alessandro Fastweb","Alessandro XAllegro","oggetto della mail","testo di prova per invio mail",1);
	int check=LibMail->SendMailText("85.18.95.132",587,"fastwebnet.it","alessandro.mariotti@fastwebnet.it","Mar1c1ca","alessandro.mariotti@fastwebnet.it","alex@xallegro.com","Alessandro","Alessandro XAllegro","oggetto della mail","testo di prova per invio mail\r\n con a capo e i carattere ������?=!",1);
	
	if (check==1){

		cout<<"mail sent"<<endl;

	} else {

		cout<<"mail error"<<endl;
	}

	delete LibMail;
*/


class XaLibMail {

	private:
		//string XHtmlPage;
		//typedef vector<string> VectorFields;
		//typedef vector<string> VectorValues;
		int SendHeaderCommon(XaLibSocket* LibSocket,int SocketNumber,string LocalDomain,string AccountUsername,string AccountPassword,string MailFromAddress,string MailToAddress,string MailFromText,string MailToText,string MailSubject,int MailConfirmation);
	protected:

	public:

		XaLibMail();
		~XaLibMail();
		int SendSysMail(string MailConfXmlFilePath,string MailAccount,string MailToAddress,string MailToText,int MailConfirmation);
		int SendMailText(string SmtpServer,int SmtpServerPort,string LocalDomain,string AccountUsername,string AccountPassword,string MailFromAddress,string MailToAddress,string MailFromText,string MailToText,string MailSubject,string MailMessage,int MailConfirmation);
};
#endif
