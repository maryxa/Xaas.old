#include <XaLibSocket.h>

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>
#include <new>
#include <map>
#include <stdio.h>

#ifdef _WIN32

	#pragma comment(lib, "Ws2_32.lib")
	#define _WIN32_WINNT 0x501

	#include <winsock2.h>
	#include <windows.h>
	#include <Ws2tcpip.h>
	#include <ws2tcpip.h>

#else

	#include <sys/types.h>
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <netdb.h>
	#include <arpa/inet.h>
	#include <netinet/ip.h>

#endif

using namespace std;

XaLibSocket::XaLibSocket(){

};

int XaLibSocket::SocketOpen(string ServerIp,int ServerPort){

	char* ServerIpChar=(char*)ServerIp.c_str();
	int err=0;

//cout<<sendbuf<<endl;

	#ifdef _WIN32
		//VARIABILE CHE CONTIENE LE PRIMITIVE DI WINSOCK
		WSADATA data;
		//VARIABILE CHE CONTIENE LA VERSIONE DI wsock32.dll
		WORD p;
		p=MAKEWORD(2,0);
		//INIZIALIZZAZIONE DELLE wsock32.dll
		err=WSAStartup(p,&data);
	#endif

	#ifdef _WIN32
		int SocketNumber=socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	#else
		int SocketNumber=socket(AF_INET, SOCK_STREAM,0);
	#endif

	struct sockaddr_in sock_addr;

	//AF_INET=TCP
	sock_addr.sin_family=AF_INET;
	sock_addr.sin_port=htons(ServerPort);
	sock_addr.sin_addr.s_addr = inet_addr(ServerIpChar);

	err=connect(SocketNumber,(struct sockaddr*)&sock_addr,sizeof(struct sockaddr));
	cout<<err<<endl;
	//-1 NON APRE
	//0 APRE

return SocketNumber;
};

string XaLibSocket::SocketSend(int SocketNumber,string Command){

	int iResult;

	//#define DEFAULT_BUFLEN 256
	//int recvbuflen = DEFAULT_BUFLEN;
	//char recvbuf[DEFAULT_BUFLEN] = "";

	char* sendbuf=(char*)Command.c_str();

	iResult = send(SocketNumber,sendbuf,(int)strlen(sendbuf),0);

    if (iResult == -1) {

		this->SocketClose(SocketNumber);
		return "Socket Error Sending";

    } else {
		return Command;
    }
};

string XaLibSocket::SocketReceive(int SocketNumber,int ResponseLength){

	int iResult;

	#define DEFAULT_BUFLEN 256
	int recvbuflen = DEFAULT_BUFLEN;
	char recvbuf[DEFAULT_BUFLEN] = "";

		iResult = recv(SocketNumber, recvbuf, recvbuflen, 0);

    	if ( iResult > 0 ){

			string RecvBufString="";
			int j;

			if (ResponseLength!=0){
			
				for (j=0;j<ResponseLength;j++){
					
					char rec=(char)recvbuf[j];
					RecvBufString.push_back(rec);

				}	
				
			} else {
	
				for (j=0;j<DEFAULT_BUFLEN;j++){

					char rec=(char)recvbuf[j];
					RecvBufString.push_back(rec);
				}
			}

			//cout<<"char:"<<recvbuf<<endl;
			//cout<<"string:"<<RecvBufString<<endl;

			return RecvBufString;

    	} else {
			
			#ifdef _WIN32
    	    	wprintf(L"recv failed with error: %d\n", WSAGetLastError());
        	#endif

        	return "Socket Error Receiving";
    	}

};

void XaLibSocket::SocketShutdown(int SocketNumber){

	int iResult;
	#ifdef _WIN32
		iResult = shutdown(SocketNumber, SD_SEND);
	#else
		iResult = shutdown(SocketNumber, SHUT_WR);
	#endif


    if (iResult == -1) {

		this->SocketClose(SocketNumber);
    	
    	#ifdef _WIN32
			wprintf(L"shutdown failed with error: %d\n", WSAGetLastError());
        	WSACleanup();
    	#endif

    }
};

void XaLibSocket::SocketClose(int SocketNumber){
	int iResult;
	#ifdef _WIN32
		iResult = closesocket(SocketNumber);
	#endif
    
	if (iResult == -1) {

		#ifdef _WIN32
        	wprintf(L"close failed with error: %d\n", WSAGetLastError());
        	WSACleanup();
		#endif
    }

	#ifdef _WIN32
    	WSACleanup();
	#endif

};

void XaLibSocket::SendTcpCommand(string IpAddress,int TcpPort,string Command){

	#define DEFAULT_BUFLEN 256

	int recvbuflen = DEFAULT_BUFLEN;
    
	char* sendbuf=(char*)Command.c_str();
	char recvbuf[DEFAULT_BUFLEN] = "";

	char* IpAddressChar=(char*)IpAddress.c_str();

	int iResult;
	int err=0;

//cout<<sendbuf<<endl;

#ifdef _WIN32

	//VARIABILE CHE CONTIENE LE PRIMITIVE DI WINSOCK
	WSADATA data;

	//VARIABILE CHE CONTIENE LA VERSIONE DI wsock32.dll
	WORD p;
	p=MAKEWORD(2,0);
	
	//INIZIALIZZAZIONE DELLE wsock32.dll
	err=WSAStartup(p,&data);

#endif


#ifdef _WIN32
	int sock=socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
#else
	int sock=socket(AF_INET, SOCK_STREAM,0);
#endif

	struct sockaddr_in sock_addr;

	//AF_INET=TCP
	sock_addr.sin_family=AF_INET;
	sock_addr.sin_port=htons(TcpPort);
	sock_addr.sin_addr.s_addr = inet_addr(IpAddressChar);
/*
sock_addr.sin_addr.S_un.S_un_b.s_b1=192; // indico l'indirizzo IP
sock_addr.sin_addr.S_un.S_un_b.s_b2=168;
sock_addr.sin_addr.S_un.S_un_b.s_b3=1;
sock_addr.sin_addr.S_un.S_un_b.s_b4=16;
*/

	err=connect(sock,(struct sockaddr*)&sock_addr,sizeof(struct sockaddr));

	iResult = send(sock,sendbuf,(int)strlen(sendbuf),0);

    if (iResult == -1) {

		#ifdef _WIN32
			wprintf(L"send failed with error: %d\n", WSAGetLastError());
			closesocket(sock);
        	WSACleanup();
        #endif
    }

	//printf("Bytes Sent: %d\n", iResult);

	iResult = recv(sock, recvbuf, recvbuflen, 0);

    if ( iResult > 0 ){

		//wprintf(L"Bytes received: %d\n", iResult);

    } else if ( iResult == 0 ){

		//wprintf(L"Connection closed\n");

    } else { 
		#ifdef _WIN32
    	    wprintf(L"recv failed with error: %d\n", WSAGetLastError());
        #endif
    }


	#ifdef _WIN32
		iResult = shutdown(sock, SD_SEND);
	#else
		iResult = shutdown(sock, SHUT_WR);
	#endif


    if (iResult == -1) {
    	
    	#ifdef _WIN32
    	 	closesocket(sock);
    		wprintf(L"shutdown failed with error: %d\n", WSAGetLastError());
        	WSACleanup();
    	#endif

    }

    // close the socket
    #ifdef _WIN32
    	iResult = closesocket(sock);
    #endif
    if (iResult == -1) {

		#ifdef _WIN32
        	wprintf(L"close failed with error: %d\n", WSAGetLastError());
        	WSACleanup();
		#endif
    }
	
	#ifdef _WIN32
    	WSACleanup();
	#endif

};

void XaLibSocket::GetHostByName(){
};

void XaLibSocket::MakeArpTable () {

};


XaLibSocket::~XaLibSocket(){
};
