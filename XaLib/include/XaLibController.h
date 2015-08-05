#ifndef XALIBCONTROLLER_H
#define XALIBCONTROLLER_H

#include <XaLibBase.h>

class XaLibController : protected XaLibBase {

	private:
	protected:

		int OnStartStatus=1;
		void OnStart(const string& ConfFile);

		void LoadXmlConfFile(string ConfFile);
		void StartLog();	
		void StartHttp();
		void StartDb();

		int  ProfileCalledObject(const string& CalledObject,const string& CalledEvent);

		virtual void SendResponse();
		virtual void DispatchWs();
		void Dispatch();

		virtual void ExecuteCalledObject();

		void SendHeaders(string& HeadersType) const;
		void SendLocationHeaders(string Location);

	public:

		void GetCall();
		void GetLayout();
		void GetServerInfo();
		void GetClientInfo();
		void GetWs();

		XaLibController();
		virtual ~XaLibController();
	
};
#endif