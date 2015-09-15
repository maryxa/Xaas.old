#include <XaLibWebSocket.h>



//    Create an Internet Stream socket
	
  //  Create a sockaddr_in object stating the port number and the kind of connections to be accepted

    //Bind the socket to its port
    //Tell the socket to listen for incoming connections


//Wait for and accept an incoming connection request. The result of accept is a unix-level file descriptor; reads and writes on it are direct communications with the client
//Optionally fork a new subprocess to deal with this client. This leaves the original process free to immediately accept another client connection by looping back to the accept step
//Optionally create a C FILE* to allow higher-level i/o functions to be used
//Communicate with the client
//Close the connection to the client
//If communications are being carried out by a subprocess, then exit to terminate it
//If further connections are to be accepted, loop back to the accept step
//To terminate the server, close the original socket


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
	//#define _WIN32_WINNT 0x501

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

#include "XaLibBase.h"
#include "XaLibHttp.h"
#include "XaLibCrypto.h"

#endif

XaLibWebSocket::XaLibWebSocket(){

};
//OnOpen
//OnMessage
//OnClose

int XaLibWebSocket::SocketOpen(string ServerIp,int ServerPort){

	char* ServerIpChar=(char*)ServerIp.c_str();
	int ErrorStatus=1;

/*
 * Socket creation
 */

	#ifdef _WIN32
		//variable with WinSock primitives
		WSADATA data;

		//Variable for wsock32.dll version
		WORD p;
		p=MAKEWORD(2,0);

		//wsock32.dll Initialization
		WSAStartup(p,&data);

	#endif

	#ifdef _WIN32
		int SocketNumber=socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	#else
		int SocketNumber=socket(AF_INET, SOCK_STREAM,0);
	#endif

	if (SocketNumber<0) {
		ErrorStatus=0;
	}

/*
 * Service description creation
 */

	struct sockaddr_in sock_addr;

	//AF_INET=TCP
	sock_addr.sin_len = sizeof(sock_addr);
	sock_addr.sin_family=AF_INET;
	sock_addr.sin_port=htons(ServerPort);
	sock_addr.sin_addr.s_addr = inet_addr(ServerIpChar);

/*
*  Socket bind according to the sockaddr_in
*/

	int SocketBind = ::bind(SocketNumber, (struct sockaddr *) &sock_addr, sizeof(struct sockaddr));

	if (SocketBind<0) {
		ErrorStatus=0;
	}

/*
*  Start to Listen
*/
	int SocketListen = listen(SocketNumber, 3);
	
	if (SocketListen<0) {
		ErrorStatus=0;
	}

// Servers usually accept multiple clients, so a loop is used
	int session_number=0;

	while (1) {

		//cout<<"started a socket"<<endl;
	/*
	*  sockaddr for client information
	*/

		sockaddr_in client_info;
		unsigned int client_info_size = sizeof(client_info);

		// Step 6 use accept to wait for and accept the next client
		int session_socket = ::accept(SocketNumber, (struct sockaddr *) &client_info, &client_info_size);
/*
		if (session_socket<0) {

			if (errno==EINTR) continue;
			perror("accept");
			usleep(100000); 
			// Other errors are probably a reason to stop, but for a robust server
			// just give the error a chance to go away and try again
			continue; 
		}
*/
    session_number+=1;

    // At this point, a heavy-duty server would use fork to create a sub-process, and
    // let the sub-process deal with the client, so we can wait for other clients.

    // accept filled in the provided sockaddr_in with information on the client
    char * who_is_it = inet_ntoa(client_info.sin_addr);
   // printf("[connection %d accepted from %s]\n", session_number, who_is_it);

    /*Write on screen*/
	/*Read at most 100 chars from console into 'str' */

    // Step 7 (Optional) Create normal files for communication with the client
    //        Or just use read and write directly on the session_socket itself
    //FILE * r_connection=fdopen(session_socket, "r");
    //FILE * w_connection=fdopen(session_socket, "w");
		
		string InBuffer(2049, 0);
		int n = read(session_socket, &InBuffer[0],2048);
		cout<<InBuffer<<endl;

		string SecWebSocketKey=GetSecWebSocketKey(InBuffer);

		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"String Client:" +SecWebSocketKey);

		string Guid="258EAFA5-E914-47DA-95CA-C5AB0DC85B11";
		string SumString=SecWebSocketKey+Guid;

		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"String Sum:" +SumString);

		string ShaString=XaLibCrypto::GetSha1(SumString);
		
		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"String Sha:" +ShaString);
		
		XaLibChar LibChar;
		string SecWebSocketAccept=LibChar.B64EncodeHexString(ShaString);

		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"String B64:" +ShaString);

		string Message="HTTP/1.1 101 Switching Protocols\r\nUpgrade: websocket\r\nConnection: Upgrade\r\nSec-WebSocket-Accept: "+SecWebSocketAccept+"\r\n\r\n";
		//cout<<"Message: "+Message<<endl;

		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"HandShake:" +Message);

		const char *message=Message.c_str();
		write(session_socket , message , strlen(message));

		
		
	//string Message ="HTTP/1.1 101 Switching Protocols\r\nUpgrade: websocket\r\nConnection: Upgrade\r\nSec-WebSocket-Accept: "+SecWebSocketAccept+"\r\n\r\n";
	//
		
		
		
		
		//cout<<"String Sum: "+SumString;


		//LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"YYYYYYYYY"+FromCharArrayToString(*buffer));

		//string a="B37A4F2CC0624F1690F64606CF385945B2BEC4EA";

		//XaLibChar LibChar;
		//string c=LibChar.B64EncodeHexString(a);
		
		//cout<<c<<endl;
		

		//LAST
		//sha : b37a4f2cc0624f1690f64606cf385945b2bec4ea
		//SHA : B37A4F2CC0624F1690F64606CF385945B2BEC4EA
		//b64 : s3pPLMBiTxaQ9kYGzzhZRbK+xOo=

		//string SecWebSocketKey=XaLibCrypto::GetSha1(GetSecWebSocketKey(InBuffer)+GUID);

		
		
			//cout<<"client String: "+SecWebSocketKey<<endl;
		
		
		
		//cout<<"sum string: "+SecWebSocketKey<<endl;
		//cout<<"sha string: "+XaLibCrypto::GetSha1(SecWebSocketKey+GUID)<<endl;
		
		
		//XaLibChar LibChar;
		//string SecWebSocketAccept=LibChar.B64EncodeHexString(XaLibCrypto::GetSha1(SecWebSocketKey+GUID));
		
		//cout<<"b64: "+SecWebSocketAccept<<endl;
		

		//string pluto=FromStringToHex(SecWebSocketKey,0);
		//cout<<"Pluto: "+ pluto<<endl;

		//string papero="dGhlIHNhbXBsZSBub25jZQ==258EAFA5-E914-47DA-95CA-C5AB0DC85B11";
		//cout<<"papero: "+XaLibCrypto::GetSha1(papero)<<endl;

		//cout<<"Received: "+GetSecWebSocketKey(InBuffer)<<endl;

		//XaLibCrypto::GetSha1(dGhlIHNhbXBsZSBub25jZQ==258EAFA5-E914-47DA-95CA-C5AB0DC85B11);
		//XaLibChar LibChar;
		//string SecWebSocketAccept1 =LibChar.B64Encode(XaLibCrypto::GetSha1("dGhlIHNhbXBsZSBub25jZQ==258EAFA5-E914-47DA-95CA-C5AB0DC85B11"));

		//cout<<"example: " +SecWebSocketAccept1<<endl;

		//XaLibChar LibChar;
		//string SecWebSocketAccept =LibChar.B64Encode(SecWebSocketKey);

		//cout<<"key:"+SecWebSocketAccept<<endl;

		//printf("%s", *buffer);

		//cout<<"numero di n:"+FromIntToString(n)<<endl;

	 //cout<<*buffer<<endl;

    // Step 8 Deal with the client

		
		
		//string key=HTTP.GetSecWebSocketKey();

		
		//cout<<key<<endl;
		
	//	Sec-WebSocket-Key+GUID
	//	poi sha1
	//	base 64
		
		
	//	messo in Sec-WebSocket-Accept
		
		//string SecWebSocketAccept;
		
		//string Message="HTTP/1.1 101 Switching Protocols\r\nUpgrade: websocket\r\nConnection: Upgrade\r\nSec-WebSocket-Accept: "+SecWebSocketAccept+"\r\n\r\n";
		//cout<<"Message: "+Message<<endl;
		
		//write(session_socket , message , strlen(message));

	//string Message ="HTTP/1.1 101 Switching Protocols\r\nUpgrade: websocket\r\nConnection: Upgrade\r\nSec-WebSocket-Accept: "+SecWebSocketAccept+"\r\n\r\n";
	//const char *message=Message.c_str();
	
	//cout<<Message<<endl;
	
	/*
	"Upgrade: websocket  \r\n"
	"Connection: Upgrade \r\n"
	"Sec-WebSocket-Accept: s3pPLMBiTxaQ9kYGzzhZRbK+xOo= \r\n \r\n";
	*/
	
	
	
	
    //Send some messages to the client
    //message = "Greetings! I am your connection handler\n";
     
    //message = "Now type something and i shall repeat what you type \n";
//    write(session_socket , message , strlen(message));
		
	/*
	const char *msg;
	
	msg ="HTTP/1.1 101 Switching Protocols  \r\n \
	Upgrade: websocket  \r\n \
	Connection: Upgrade \r\n \
	Sec-WebSocket-Accept: s3pPLMBiTxaQ9kYGzzhZRbK+xOo= \r\n \r\n";

	
	std::cout << "send()ing message..."  << std::endl;
	
	int len;
	ssize_t bytes_sent;
	len = strlen(msg);
	bytes_sent = write(session_socket, msg, len);

	cout << "sent: " + FromIntToString(bytes_sent)<<endl;
*/	
    //fprintf(w_connection, Response, who_is_it);

    // Step 9 When finished send all lingering transmissions and close the connection.
    //fflush(w_connection);
    //fclose(w_connection);
//    fclose(r_connection);   
    //close(session_socket);
  
	//cout<<"numero socket"+FromIntToString(session_number)<<endl;
 }
	
return SocketNumber;
};


string XaLibWebSocket::GetSecWebSocketKey(const string& Headers) {

unsigned SecWebSocketKeyStart=Headers.find("Sec-WebSocket-Key:");

	//LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Start:" +FromIntToString(SecWebSocketKeyStart));

//unsigned SecWebSocketKeyEnd=Headers.find("\n",SecWebSocketKeyStart+18);

	//LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"End:" +FromIntToString(SecWebSocketKeyEnd));


string SecWebSocketKey = Headers.substr(SecWebSocketKeyStart+19,24);

		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Catted:" +SecWebSocketKey);

return XaLibChar::ClearSpace(SecWebSocketKey);

};

string XaLibWebSocket::SocketSend(int SocketNumber,string Command){

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

string XaLibWebSocket::SocketReceive(int SocketNumber,int ResponseLength){

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

void XaLibWebSocket::SocketShutdown(int SocketNumber){

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

void XaLibWebSocket::SocketClose(int SocketNumber) {

	int iResult=0;

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

XaLibWebSocket::~XaLibWebSocket(){
};
