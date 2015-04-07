#include <XaLibLog.h>

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <random>
#include <chrono>

#include <XaLibTime.h>

extern unique_ptr<ofstream> MY_LOG_FILE;
mutex m;

XaLibLog::XaLibLog(){
};

/**
* Instance of ofstream 
* @param LogFilePath - string - complete log file path
* @param SysLogLevelConf - string - log level indicated in conf file - 0:nothing 1:all 2:error only
* @see 
* @return MyLogFile - ofstream
*/

void XaLibLog::Init(string SysLogLevelConf){
	
	this->SysLogLevel=SysLogLevelConf;
}

//LIVELLI DI LOG: 0=NIENTE 1=TUTTO 2=SOLO ERR
void XaLibLog::Write(string LogMessageLevel,const char* ClassName,const char* MethodName,int LineNumber,string LogMessage){

	
	if (this->SysLogLevel=="0"){

	} else {

		unique_ptr<XaLibTime> LibTimeLocal(new XaLibTime());
		string LogTime=LibTimeLocal->GetDateTimeIsoComplete();

		stringstream LineNumberStringStream;
		LineNumberStringStream << LineNumber;
		string LineNumberString= LineNumberStringStream.str();

		string MyLogString="["+LogMessageLevel+"]["+LogTime+"]["+IpAddress+ "]["+ClassName +"]["+LineNumberString+"]["+MethodName+"]["+LogMessage+"]";

		
	
		WriteFile(MyLogString,LogMessageLevel);
	
	}
};

//void XaLibLog::WriteFile (string MyLogString,string LogMessageLevel,mutex *m){
	
void XaLibLog::WriteFile (string MyLogString,string LogMessageLevel){

	if (this->SysLogLevel=="1"){		

		m.lock();
		*MY_LOG_FILE<<MyLogString<<endl;
		m.unlock();

	} else if (this->SysLogLevel=="2" && LogMessageLevel=="ERR"){

		m.lock();
		*MY_LOG_FILE<<MyLogString<<endl;
		m.unlock();

	}

};

void XaLibLog::SetIpAddress(string &_IpAddress){

	this->IpAddress=_IpAddress;
};

void XaLibLog::Rotate(){

};

void XaLibLog::Close(){

	MY_LOG_FILE->close();
};

XaLibLog::~XaLibLog(){
};