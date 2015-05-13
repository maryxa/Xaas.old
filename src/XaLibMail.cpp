#include <XaLibMail.h>

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>
#include <new>
#include <map>
#include <stdio.h>

#include <libxml/tree.h>

#include <XaLibChar.h>
#include <XaLibSocket.h>
#include <XaLibDom.h>


using namespace std;

XaLibMail::XaLibMail(){

};

int XaLibMail::SendSysMail(string MailConfXmlFilePath,string MailAccount,string MailToAddress,string MailToText,int MailConfirmation){

XaLibDom* LibDom=new XaLibDom();

	xmlDocPtr XmlDomDoc;
	XmlDomDoc=LibDom->DomFromFile(MailConfXmlFilePath);

		string XPathExprBase="/Mails/"+MailAccount+"/";
		
		string SmtpServer=LibDom->GetElementValueByXPath(XmlDomDoc,XPathExprBase+"SmtpServer");
		
		string SmtpServerPortString=LibDom->GetElementValueByXPath(XmlDomDoc,XPathExprBase+"SmtpServerPort");
		int SmtpServerPort = atoi(SmtpServerPortString.c_str());
		
		string LocalDomain=LibDom->GetElementValueByXPath(XmlDomDoc,XPathExprBase+"LocalDomain");
		string AccountUsername=LibDom->GetElementValueByXPath(XmlDomDoc,XPathExprBase+"AccountUsername");
		string AccountPassword=LibDom->GetElementValueByXPath(XmlDomDoc,XPathExprBase+"AccountPassword");
		string MailFromAddress=LibDom->GetElementValueByXPath(XmlDomDoc,XPathExprBase+"MailFromAddress");
		string MailFromText=LibDom->GetElementValueByXPath(XmlDomDoc,XPathExprBase+"MailFromText");
		string MailSubject=LibDom->GetElementValueByXPath(XmlDomDoc,XPathExprBase+"MailSubject");
		string MailMessage=LibDom->GetElementValueByXPath(XmlDomDoc,XPathExprBase+"MailMessage");

delete LibDom;



int check=this->SendMailText(SmtpServer,SmtpServerPort,LocalDomain,AccountUsername,AccountPassword,MailFromAddress,MailToAddress,MailFromText,MailToText,MailSubject,MailMessage,MailConfirmation);

return check;
};


int XaLibMail::SendMailText(string SmtpServer,int SmtpServerPort,string LocalDomain,string AccountUsername,string AccountPassword,string MailFromAddress,string MailToAddress,string MailFromText,string MailToText,string MailSubject,string MailMessage,int MailConfirmation){

	string ProtocolEnter="\r\n";

	string message;
	string response;
	
	XaLibSocket* LibSocket=new XaLibSocket();

	int SocketNumber=LibSocket->SocketOpen(SmtpServer,SmtpServerPort);
	response=LibSocket->SocketReceive(SocketNumber,3);
	
	if (response=="220"){
			
		int StatusHeaderCommon=this->SendHeaderCommon(LibSocket,SocketNumber,LocalDomain,AccountUsername,AccountPassword,MailFromAddress,MailToAddress,MailFromText,MailToText,MailSubject,MailConfirmation);
		//cout<<StatusHeaderCommon<<endl;
		
		if (StatusHeaderCommon==1){

			message=LibSocket->SocketSend(SocketNumber,ProtocolEnter);
			message=LibSocket->SocketSend(SocketNumber,MailMessage);

			//cout<<message<<endl;
	
			message=LibSocket->SocketSend(SocketNumber,ProtocolEnter);
			//message=LibSocket->SocketSend(SocketNumber,ProtocolEnter);

			message=LibSocket->SocketSend(SocketNumber,".");
			message=LibSocket->SocketSend(SocketNumber,ProtocolEnter);

			response=LibSocket->SocketReceive(SocketNumber,3);
			//cout<<response<<endl;
			
			message=LibSocket->SocketSend(SocketNumber,"QUIT");
			message=LibSocket->SocketSend(SocketNumber,ProtocolEnter);
			response=LibSocket->SocketReceive(SocketNumber,3);
			
			if (response=="221"){

				return 1;

			} else {
				
				return 0;
			}
			//cout<<response<<endl;
			/*
			message=LibSocket->SocketSend(SocketNumber,ProtocolEnter);
			response=LibSocket->SocketReceive(SocketNumber,0);
			cout<<response<<endl;
*/
		} else {
			return 0;
		}
		
			
	} else {

		return 0;
	}

LibSocket->SocketShutdown(SocketNumber);
LibSocket->SocketClose(SocketNumber);
delete LibSocket;

return 1;
};

int XaLibMail::SendHeaderCommon(XaLibSocket* LibSocket, int SocketNumber,string LocalDomain,string AccountUsername,string AccountPassword,string MailFromAddress,string MailToAddress,string MailFromText,string MailToText,string MailSubject,int MailConfirmation){

	string ProtocolEnter="\r\n";
	string message;
	string response;


	//2 VOLTE INVIO: ESPERIENZA PRATICA
	message=LibSocket->SocketSend(SocketNumber,ProtocolEnter);
	response=LibSocket->SocketReceive(SocketNumber,3);
			
	message=LibSocket->SocketSend(SocketNumber,ProtocolEnter);
	response=LibSocket->SocketReceive(SocketNumber,3);

	if (response=="500"){
		
		string ProtocolEhlo="EHLO ";
		ProtocolEhlo.append(LocalDomain);
		ProtocolEhlo.append(ProtocolEnter);
	
		message=LibSocket->SocketSend(SocketNumber,ProtocolEhlo);
		response=LibSocket->SocketReceive(SocketNumber,3);

		if (response=="250"){

			string ProtocolAuthLogin="AUTH LOGIN";
			ProtocolAuthLogin.append(ProtocolEnter);

			message=LibSocket->SocketSend(SocketNumber,ProtocolAuthLogin);
			response=LibSocket->SocketReceive(SocketNumber,3);
			
			if (response=="334"){

				XaLibChar* LibChar=new XaLibChar();
					string AccountUsernameB64 = LibChar->B64Encode(AccountUsername);
					string AccountPasswordB64 = LibChar->B64Encode(AccountPassword);
				delete LibChar;

				string ProtocolAccountUsernameB64=AccountUsernameB64;
				ProtocolAccountUsernameB64.append(ProtocolEnter);

				string ProtocolAccountPasswordB64=AccountPasswordB64;
				ProtocolAccountPasswordB64.append(ProtocolEnter);

				message=LibSocket->SocketSend(SocketNumber,ProtocolAccountUsernameB64);
				response=LibSocket->SocketReceive(SocketNumber,3);

				message=LibSocket->SocketSend(SocketNumber,ProtocolAccountPasswordB64);
				response=LibSocket->SocketReceive(SocketNumber,3);

				if (response=="235"){
					
					string ProtocolMailFrom="MAIL FROM: <";
					ProtocolMailFrom.append(MailFromAddress);
					ProtocolMailFrom.append(">");
					ProtocolMailFrom.append(ProtocolEnter);
					
					message=LibSocket->SocketSend(SocketNumber,ProtocolMailFrom);
					response=LibSocket->SocketReceive(SocketNumber,3);
					
					if (response=="250"){
						
						string ProtocolRcptTo="RCPT TO: <";
						ProtocolRcptTo.append(MailToAddress);
						ProtocolRcptTo.append(">");

						if (MailConfirmation==1){
							ProtocolRcptTo.append(" NOTIFY=success,failure");
						}
						
						ProtocolRcptTo.append(ProtocolEnter);
						
						message=LibSocket->SocketSend(SocketNumber,ProtocolRcptTo);
						response=LibSocket->SocketReceive(SocketNumber,3);

						if (response=="250"){

							string ProtocolData="DATA";
							ProtocolData.append(ProtocolEnter);
	
							message=LibSocket->SocketSend(SocketNumber,ProtocolData);
							response=LibSocket->SocketReceive(SocketNumber,3);
						
							if(response=="354"){

								string ProtocolDataFrom="from:";
								ProtocolDataFrom.append("\"");
								ProtocolDataFrom.append(MailFromText);
								ProtocolDataFrom.append("\"");
								ProtocolDataFrom.append("<");
								ProtocolDataFrom.append(MailFromAddress);
								ProtocolDataFrom.append(">");
								ProtocolDataFrom.append(ProtocolEnter);
								//cout<<ProtocolDataFrom<<endl;

								message=LibSocket->SocketSend(SocketNumber,ProtocolDataFrom);
								//response=LibSocket->SocketReceive(SocketNumber,3);
								
								//cout<<"MESSAGE : "<<message<<endl;
								
								string ProtocolDataTo="to:";
								ProtocolDataTo.append("\"");
								ProtocolDataTo.append(MailToText);
								ProtocolDataTo.append("\"");
								ProtocolDataTo.append("<");
								ProtocolDataTo.append(MailToAddress);
								ProtocolDataTo.append(">");
								ProtocolDataTo.append(ProtocolEnter);

								message=LibSocket->SocketSend(SocketNumber,ProtocolDataTo);
								//cout<<"MESSAGE : "<<message<<endl;

								string ProtocolDataSubject="subject:";
								ProtocolDataSubject.append(MailSubject);
								ProtocolDataSubject.append(ProtocolEnter);

								//cout<<ProtocolDataSubject<<endl;
								message=LibSocket->SocketSend(SocketNumber,ProtocolDataSubject);
								
								//cout<<"MESSAGE : "<<message<<endl;

								message=LibSocket->SocketSend(SocketNumber,ProtocolEnter);

								return 1;
								//cout<<"RESPONSE: "<<response<<endl;
								//cout<<"##########"<<endl;
							
							} else {
								
								return 0;
							}
							
						} else {

							return 0;
						}		

					} else {
					
						return 0;
					}


				} else if (response=="535"){

					cout<<"invalid smtp username or password"<<endl;
					return 0;

				} else {

					return 0;
				}

			} else {

				return 0;
			}

		} else {

			return 0;
		}

	} else {

		return 0;
	}

};

XaLibMail::~XaLibMail(){
};