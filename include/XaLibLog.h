#ifndef XALIBLOG_H
#define XALIBLOG_H

#include <string>
#include <map>
#include <vector>
#include <pthread.h>
#include <memory>

using namespace std;

class XaLibLog {

	private:

		string SysLogLevel;
		string IpAddress;

		void Rotate();
		//static void *WriteFile(void*);

	protected:

	public:

		XaLibLog();
		~XaLibLog();

		void Init(string SysLogLevelConf);
		void SetIpAddress(string &_IpAddress);

		void Write(string LogMessageLevel, const char* ClassName, const char* MethodName,int LineNumber,string LogMessage);

		//void WriteFile (string MyLogString,string LogMessageLevel,mutex *m);
		void WriteFile (string MyLogString,string LogMessageLevel);

		
		void Close();

};
#endif