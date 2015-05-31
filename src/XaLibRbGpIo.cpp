#include <XaLibRbGpIo.h>

#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#ifdef _WIN32
#else
	#include <termios.h>
#endif

/*
std::string cmd = "sudo chmod a+x file";
int r = system(cmd.c_str());
*/

XaLibRbGpIo::XaLibRbGpIo() {

};

#ifdef _WIN32

#else

XaLibRbGpIo::XaLibRbGpIo(const int GpIoNumber[],const int GpIoDirection[],const int GpIoValue[]){

		this->GpIoExport(GpIoNumber[0]);
		this->GpIoExport(GpIoNumber[1]);
		this->GpIoExport(GpIoNumber[2]);

		this->GpIoSetDirection(GpIoNumber[0],GpIoDirection[0]);
		this->GpIoSetDirection(GpIoNumber[1],GpIoDirection[1]);
		this->GpIoSetDirection(GpIoNumber[2],GpIoDirection[2]);

		this->GpIoSetValue(GpIoNumber[0],GpIoValue[0]);
		this->GpIoSetValue(GpIoNumber[1],GpIoValue[1]);
		this->GpIoSetValue(GpIoNumber[2],GpIoValue[2]);

		usleep(500000);

		this->GpIoSetValue(GpIoNumber[0],0);
		this->GpIoSetValue(GpIoNumber[1],0);
		this->GpIoSetValue(GpIoNumber[2],0);

		usleep(500000);

		this->GpIoUnexport(GpIoNumber[0]);
		this->GpIoUnexport(GpIoNumber[1]);
		this->GpIoUnexport(GpIoNumber[2]);
}

XaLibRbGpIo::XaLibRbGpIo(const int& GpIoNumber,const string& GpIoDirection,const int& GpIoValue){
/*
		this->GpIoExport(GpIoNumber[0]);
		this->GpIoExport(GpIoNumber[1]);
		this->GpIoExport(GpIoNumber[2]);

		this->GpIoSetDirection(GpIoNumber[0],GpIoDirection[0]);
		this->GpIoSetDirection(GpIoNumber[1],GpIoDirection[1]);
		this->GpIoSetDirection(GpIoNumber[2],GpIoDirection[2]);

		this->GpIoSetValue(GpIoNumber[0],GpIoValue[0]);
		this->GpIoSetValue(GpIoNumber[1],GpIoValue[1]);
		this->GpIoSetValue(GpIoNumber[2],GpIoValue[2]);

		usleep(500000);

		this->GpIoSetValue(GpIoNumber[0],"0");
		this->GpIoSetValue(GpIoNumber[1],"0");
		this->GpIoSetValue(GpIoNumber[2],"0");

		usleep(500000);

		this->GpIoUnexport(GpIoNumber[0]);
		this->GpIoUnexport(GpIoNumber[1]);
		this->GpIoUnexport(GpIoNumber[2]);
 */
}

XaLibRbGpIo::GpIoSet(const int& GpIoNumber,const string& GpIoDirection,const int& GpIoValue){
/*
		this->GpIoExport(GpIoNumber[0]);
		this->GpIoExport(GpIoNumber[1]);
		this->GpIoExport(GpIoNumber[2]);

		this->GpIoSetDirection(GpIoNumber[0],GpIoDirection[0]);
		this->GpIoSetDirection(GpIoNumber[1],GpIoDirection[1]);
		this->GpIoSetDirection(GpIoNumber[2],GpIoDirection[2]);

		this->GpIoSetValue(GpIoNumber[0],GpIoValue[0]);
		this->GpIoSetValue(GpIoNumber[1],GpIoValue[1]);
		this->GpIoSetValue(GpIoNumber[2],GpIoValue[2]);

		usleep(500000);

		this->GpIoSetValue(GpIoNumber[0],"0");
		this->GpIoSetValue(GpIoNumber[1],"0");
		this->GpIoSetValue(GpIoNumber[2],"0");

		usleep(500000);

		this->GpIoUnexport(GpIoNumber[0]);
		this->GpIoUnexport(GpIoNumber[1]);
		this->GpIoUnexport(GpIoNumber[2]);
 */
}

int XaLibRbGpIo::GpIoExport(const int& GpIoNumber) {

	char buf[11]; 

	int fd = open("/sys/class/gpio/export", O_WRONLY);

	sprintf(buf, "%d", GpIoNumber); 

	write(fd, buf, strlen(buf));

	close(fd);
    return 1;
}
 
int XaLibRbGpIo::GpIoUnexport(const int& GpIoNumber) {

    string UnexportFile = "/sys/class/gpio/unexport";
    ofstream UnexportStream(UnexportFile.c_str());
    //if (UnexportStream < 0){
      //  cout << " OPERATION FAILED: Unable to unexport GPIO"<< GpIoNumber <<" ."<< endl;
        //return 0;
    //}
 
    UnexportStream << GpIoNumber;
    UnexportStream.close();

    return 1;
}
 
int XaLibRbGpIo::GpIoSetDirection(const int& GpIoNumber,const int& GpIoDirection) {
 
    string DirectionFile ="/sys/class/gpio/gpio" + FromIntToString(GpIoNumber) + "/direction";
    ofstream DirectionStream(DirectionFile.c_str());

		//if (DirectionStream < 0){
          //  cout << " OPERATION FAILED: Unable to set direction of GPIO"<< GpIoNumber <<" ."<< endl;
            //return 0;
        //}
 
        DirectionStream << GpIoDirection;
        DirectionStream.close();
        return 1;
}
 
int XaLibRbGpIo::GpIoSetValue(const int& GpIoNumber,const int& GpIoValue) {
	
	int ReturnValue=-1;
    string GpIoValueFile = "/sys/class/gpio/gpio" + FromIntToString(GpIoNumber) + "/value";
    ofstream GpIoValueStream(GpIoValueFile.c_str());

	
	if (GpIoValueStream.is_open()){

		GpIoValueStream << GpIoValue ;
		
		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Set Value From GpIo -> Number: " +FromIntToString(GpIoNumber)+ " :: "+ "Value: " +FromIntToString(GpIoValue));
		ReturnValue=1;
		
	} else {
		
		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Error Setting Value From GpIo -> Number: " +FromIntToString(GpIoNumber)+ " :: "+ "Value: " +FromIntToString(GpIoValue));
		ReturnValue=-1;

	}

	GpIoValueStream.close();
	return ReturnValue;
}
 
string XaLibRbGpIo::GpIoGetValue(const int& GpIoNumber){
 
	string GpIoValue;
	string GpIoValueFile = "/sys/class/gpio/gpio" + FromIntToString(GpIoNumber) + "/value";
	ifstream GpIoValueStream(GpIoValueFile.c_str());

	if (GpIoValueStream.is_open()){
		
		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Get Value From GpIo -> Number: " +FromIntToString(GpIoNumber)+ " :: "+ "Value: " +GpIoValue);
		GpIoValueStream >> GpIoValue;

	} else {
	
		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Error Getting Value From GpIo -> Number: " +FromIntToString(GpIoNumber));
		GpIoValue="-1";
	}

	GpIoValueStream.close();
	return GpIoValue;
};
#endif

XaLibRbGpIo::~XaLibRbGpIo() {
}