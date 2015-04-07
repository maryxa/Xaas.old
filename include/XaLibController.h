#ifndef XALIBCONTROLLER_H
#define XALIBCONTROLLER_H

#include <XaLibBase.h>

class XaLibController : protected XaLibBase {

	private:
	protected:

		void LoadXmlConfFile(string ConfFile);
		void StartLog();
		void StartHttp();

		int  ProfileCalledObject(const string& CalledObject,const string& CalledEvent);

		virtual void SendResponse();
		virtual void DispatchWs();
		void Dispatch();

		virtual void ExecuteCalledObject();

		void SendHeaders(string& HeadersType) const;
		void SendLocationHeaders(string Location);

	public:

		void GetCall();
		void GetClientInfo();
		void GetWs();

		XaLibController();
		virtual ~XaLibController();
		void StartDb();
};
#endif