#ifndef XALIBSOCKET_H
#define XALIBSOCKET_H

#include <XaLibSocket.h>
#include <XaLibBase.h>
#include <XaLibLog.h>

/*
	XaLibSocket* LibSocket=new XaLibSocket();
	
	LibSocket->SocketOpen("192.168.1.6",80);
	delete LibSocket;
*/

extern XaLibLog LOG;
extern XaSettings SETTINGS;

class XaLibSocket : protected XaLibBase  {

	private:
		//string XHtmlPage;
		//typedef vector<string> VectorFields;
		//typedef vector<string> VectorValues

	protected:

	public:

		XaLibSocket();
		~XaLibSocket();

		void SendTcpCommand(string IpAddress,int TcpPort,string Command);

		int SocketOpen(string ServerIp,int ServerPort);
		string SocketSend(int SocketNumber,string Command);
		string SocketReceive(int SocketNumber,int ResponseLength);
		void SocketShutdown(int SocketNumber);
		void SocketClose(int SocketNumber);

		int SystemPing(const string &target,const int &count);

};
#endif
