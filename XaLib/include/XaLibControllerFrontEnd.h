#ifndef XALIBCONTROLLERFRONTEND_H
#define XALIBCONTROLLERFRONTEND_H

#include <XaLibController.h>

/**
 * @brief Base Class for Controllrs
 *
 * @details Base Class for Controllrs:\n
 * 
 * Any Application Controller will extend from this class
 *
 * @see alex@xallegro.com
 * @author Alessandro Mariotti
*/
class XaLibControllerFrontEnd : protected XaLibController {

	private:
	protected:

		/**
		* @brief Environment initialization.
		* @details Initialization of Super Global Variable
		* @see XaLibBase
		* @see XaLibAction
		* 
		* @param ConFile Configuration File - Relative or absolute path
		* @return Void
		*
		* Example Usage: in derived Controller Class
		*
		* @code
		*
		* int main(void){
		*
		*	string ConfigurationFile {"../config/XAllegro.xml"};
		*	unique_ptr<FILE, int(*)(FILE*)> fp(fopen(ConfigurationFile.c_str(), "r"), fclose);
		*
		*	if (fp) {
		*
		*		unique_ptr<Controller> ControllerObj (new Controller(ConfigurationFile.c_str()));
		*
		*	} else {
		*		...
		*	}
		*
		*	return 0;
		* };

		* Controller::Controller(string ConfFile) {
		* 
		*	OnStart(ConfFile);
		*	...
		* 
		* } 
		* @endcode
		*
		*/
		void OnStart(const string& ConfFile);
		void SendResponse();
		
//		int OnStartStatus=1;
//		void OnStart(const string& ConfFile);
//
//		void LoadXmlConfFile(string ConfFile);
//		void StartLog();	
//		void StartHttp();
//		void StartDb();

//		int  ProfileCalledObject(const string& CalledObject,const string& CalledEvent);

//		virtual void SendResponse();
//		virtual void DispatchWs();
//		void Dispatch();

//		virtual void ExecuteCalledObject();

//		void SendHeaders(string& HeadersType) const;
//		void SendLocationHeaders(string Location);

	public:

//		void GetCall();
//		void GetLayout();
//		void GetServerInfo();
//		void GetClientInfo();
//		void GetWs();

		XaLibControllerFrontEnd();
		virtual ~XaLibControllerFrontEnd();
	
};
#endif