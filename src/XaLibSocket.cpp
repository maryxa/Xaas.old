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
    
	//char *sendbuf = "sendir,1:3,1,37764,1,1,8,34,8,50,8,29,8,108,8,50,8,50,8,45,8,34,8,497,8,34,8,29,8,29,8,29,8,29,8,108,8,29,8,29,8,3057,8,34,8,50,8,29,8,108,8,50,8,50,8,45,8,34,8,497,8,34,8,71,8,71\r\n";
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
	/*
	int argc;
	char* argv0;
	char* argv1="192.168.1.130";

	   //-----------------------------------------
    // Declare and initialize variables
    WSADATA wsaData = {0};
    int iResult = 0;

    DWORD dwRetval;

    struct sockaddr_in saGNI;
    char hostname[NI_MAXHOST];
    char servInfo[NI_MAXSERV];
    u_short port = 27015;

    // Validate the parameters
    if (argc != 2) {
        printf("usage: %s IPv4 address\n", argv0);
        printf("  to return hostname\n");
        printf("       %s 127.0.0.1\n", argv0);
        //return 1;
    }
    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed: %d\n", iResult);
        //return 1;
    }
    //-----------------------------------------
    // Set up sockaddr_in structure which is passed
    // to the getnameinfo function
    saGNI.sin_family = AF_INET;
    saGNI.sin_addr.s_addr = inet_addr(argv1);
    saGNI.sin_port = htons(port);

    //-----------------------------------------
    // Call getnameinfo
    dwRetval = getnameinfo((struct sockaddr *) &saGNI,
                           sizeof (struct sockaddr),
                           hostname,
                           NI_MAXHOST, servInfo, NI_MAXSERV, NI_NUMERICSERV);

    if (dwRetval != 0) {
        printf("getnameinfo failed with error # %ld\n", WSAGetLastError());
        //return 1;
    } else {
        printf("getnameinfo returned hostname = %s\n", hostname);
        //return 0;
    }
 
--------------------------
CONFIGURAZIONE WIFI
	int argc=3;
	char* argv1;
	char* argv2=(char*)"192.168.1.13";
	char* argv3=(char*)"80";

    WSADATA wsaData;
    int iResult;
    INT iRetval;

    DWORD dwRetval;

    int i = 1;
    
    struct addrinfo *result = NULL;
    struct addrinfo *ptr = NULL;
    struct addrinfo hints;

    struct sockaddr_in  *sockaddr_ipv4;
//    struct sockaddr_in6 *sockaddr_ipv6;
    LPSOCKADDR sockaddr_ip;

    char ipstringbuffer[46];
    DWORD ipbufferlength = 46;



    // Validate the parameters
    if (argc != 3) {
        printf("usage: %s <hostname> <servicename>\n", argv1);
        printf("getaddrinfo provides protocol-independent translation\n");
        printf("   from an ANSI host name to an IP address\n");
        printf("%s example usage\n", argv1);
        printf("   %s www.contoso.com 0\n", argv1);
        //return 1;
    }

    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed: %d\n", iResult);
        //return 1;
    }

    //--------------------------------
    // Setup the hints address info structure
    // which is passed to the getaddrinfo() function
    ZeroMemory( &hints, sizeof(hints) );
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    printf("Calling getaddrinfo with following parameters:\n");
    printf("\tnodename = %s\n", argv2);
    printf("\tservname (or port) = %s\n\n", argv3);
    
//--------------------------------
// Call getaddrinfo(). If the call succeeds,
// the result variable will hold a linked list
// of addrinfo structures containing response
// information
    dwRetval = getaddrinfo(argv2, argv3, &hints, &result);
    if ( dwRetval != 0 ) {
        printf("getaddrinfo failed with error: %d\n", dwRetval);
        WSACleanup();
        //return 1;
    }

    printf("getaddrinfo returned success\n");
    
    // Retrieve each address and print out the hex bytes
    for(ptr=result; ptr != NULL ;ptr=ptr->ai_next) {

        printf("getaddrinfo response %d\n", i++);
        printf("\tFlags: 0x%x\n", ptr->ai_flags);
        printf("\tFamily: ");
        switch (ptr->ai_family) {
            case AF_UNSPEC:
                printf("Unspecified\n");
                break;
            case AF_INET:
                printf("AF_INET (IPv4)\n");
                sockaddr_ipv4 = (struct sockaddr_in *) ptr->ai_addr;
                printf("\tIPv4 address %s\n",
                    inet_ntoa(sockaddr_ipv4->sin_addr) );
                break;
            case AF_INET6:
                printf("AF_INET6 (IPv6)\n");
                // the InetNtop function is available on Windows Vista and later
                // sockaddr_ipv6 = (struct sockaddr_in6 *) ptr->ai_addr;
                // printf("\tIPv6 address %s\n",
                //    InetNtop(AF_INET6, &sockaddr_ipv6->sin6_addr, ipstringbuffer, 46) );
                
                // We use WSAAddressToString since it is supported on Windows XP and later
                sockaddr_ip = (LPSOCKADDR) ptr->ai_addr;
                // The buffer length is changed by each call to WSAAddresstoString
                // So we need to set it for each iteration through the loop for safety
                ipbufferlength = 46;
                iRetval = WSAAddressToString(sockaddr_ip, (DWORD) ptr->ai_addrlen, NULL, 
                    ipstringbuffer, &ipbufferlength );
                if (iRetval)
                    printf("WSAAddressToString failed with %u\n", WSAGetLastError() );
                else    
                    printf("\tIPv6 address %s\n", ipstringbuffer);
                break;
            case AF_NETBIOS:
                printf("AF_NETBIOS (NetBIOS)\n");
                break;
            default:
                printf("Other %ld\n", ptr->ai_family);
                break;
        }
        printf("\tSocket type: ");
        switch (ptr->ai_socktype) {
            case 0:
                printf("Unspecified\n");
                break;
            case SOCK_STREAM:
                printf("SOCK_STREAM (stream)\n");
                break;
            case SOCK_DGRAM:
                printf("SOCK_DGRAM (datagram) \n");
                break;
            case SOCK_RAW:
                printf("SOCK_RAW (raw) \n");
                break;
            case SOCK_RDM:
                printf("SOCK_RDM (reliable message datagram)\n");
                break;
            case SOCK_SEQPACKET:
                printf("SOCK_SEQPACKET (pseudo-stream packet)\n");
                break;
            default:
                printf("Other %ld\n", ptr->ai_socktype);
                break;
        }
        printf("\tProtocol: ");
        switch (ptr->ai_protocol) {
            case 0:
                printf("Unspecified\n");
                break;
            case IPPROTO_TCP:
                printf("IPPROTO_TCP (TCP)\n");
                break;
            case IPPROTO_UDP:
                printf("IPPROTO_UDP (UDP) \n");
                break;
            default:
                printf("Other %ld\n", ptr->ai_protocol);
                break;
        }
        printf("\tLength of this sockaddr: %d\n", ptr->ai_addrlen);
        printf("\tCanonical name: %s\n", ptr->ai_canonname);
    }

    freeaddrinfo(result);
    WSACleanup();

	-------------------
	WSADATA wsaData;
    int iResult;

    DWORD dwError;
    int i = 0;

    struct hostent *remoteHost;
    char *host_name;
    struct in_addr addr;

    char **pAlias;
    
     // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed: %d\n", iResult);
    }
	
	string hostname="AppleTv";
    host_name = (char*)hostname.c_str();
    
		printf("Calling gethostbyname with %s\n", host_name);
		remoteHost = gethostbyname(host_name);

    if (remoteHost == NULL) {
        dwError = WSAGetLastError();
        if (dwError != 0) {
            if (dwError == WSAHOST_NOT_FOUND) {
                printf("Host not found\n");
                //return 1;
            } else if (dwError == WSANO_DATA) {
                printf("No data record found\n");
                //return 1;
            } else {
                printf("Function failed with error: %ld\n", dwError);
                //return 1;
            }
        }
    } else {

        printf("Function returned:\n");
        printf("\tOfficial name: %s\n", remoteHost->h_name);
        for (pAlias = remoteHost->h_aliases; *pAlias != 0; pAlias++) {
            printf("\tAlternate name #%d: %s\n", ++i, *pAlias);
        }
        printf("\tAddress type: ");
        switch (remoteHost->h_addrtype) {
        case AF_INET:
            printf("AF_INET\n");
            break;
        case AF_NETBIOS:
            printf("AF_NETBIOS\n");
            break;
        default:
            printf(" %d\n", remoteHost->h_addrtype);
            break;
        }
        printf("\tAddress length: %d\n", remoteHost->h_length);

        i = 0;
        if (remoteHost->h_addrtype == AF_INET)
        {
            while (remoteHost->h_addr_list[i] != 0) {
                addr.s_addr = *(u_long *) remoteHost->h_addr_list[i++];
                printf("\tIP Address #%d: %s\n", i, inet_ntoa(addr));
            }
        }
        else if (remoteHost->h_addrtype == AF_NETBIOS) {
            printf("NETBIOS address was returned\n");

        }
    }
    */
};

void XaLibSocket::MakeArpTable () {

};


XaLibSocket::~XaLibSocket(){
};
