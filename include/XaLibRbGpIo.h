#ifndef XALIBRBGPIO_H
#define XALIBRBGPIO_H

#include <XaLibBase.h>
#include <XaLibLog.h>

extern XaLibLog LOG;

class XaLibRbGpIo : protected XaLibBase {

	public:

		XaLibRbGpIo();
		~XaLibRbGpIo();

		string GpIoGetValue(const int& GpIoNumber);
		int GpIoSet(const int& GpIoNumber,const string& GpIoDirection,const int& GpIoValue);

	protected:

	private:

		int GpIoExport(const int& GpIoNumber);
    	int GpIoUnexport(const int& GpIoNumber);
    	int GpIoSetDirection(const int& GpIoNumber,const string& GpIoDirection);
    	int GpIoSetValue(const int& GpIoNumber,const int& GpIoValue);
};
 
#endif