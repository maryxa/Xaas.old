#ifndef XALIBWEBSOCKET_H
#define XALIBWEBSOCKET_H

#include <XaLibBase.h>
#include <XaLibLog.h>
#include <XaLibHttp.h>
#include <XaLibChar.h>

/*
	XaLibSocket* LibSocket=new XaLibSocket();
	
	LibSocket->SocketOpen("192.168.1.6",80);
	delete LibSocket;
*/

extern XaLibLog LOG;
extern XaLibHttp HTTP;
extern XaSettings SETTINGS;

class XaLibWebSocket : protected XaLibBase  {

	private:
		//string XHtmlPage;
		//typedef vector<string> VectorFields;
		//typedef vector<string> VectorValues

		string GetSecWebSocketKey(const string& Headers);

	protected:

	public:

		XaLibWebSocket();
		~XaLibWebSocket();

		int SocketOpen(string ServerIp,int ServerPort);
		string SocketSend(int SocketNumber,string Command);
		string SocketReceive(int SocketNumber,int ResponseLength);
		void SocketShutdown(int SocketNumber);
		void SocketClose(int SocketNumber);

};
#endif
