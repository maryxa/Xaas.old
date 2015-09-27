#include <XaLibError.h>

XaLibError::XaLibError(){
};

string XaLibError::GetError(const int& ErrorCode) {

	Setup();
	return XaErrors[ErrorCode];
};

void XaLibError::Setup() {

	
	/*
	 * Log - http - 
	 */
	
	
	XaErrors[21]={"LOG Unable to open Log file"};
	XaErrors[22]={"DB Unable to Connect SESSION DB"};
	XaErrors[23]={"DB Unable to Connect WRITE DB"};
	XaErrors[24]={"DB Unable to Connect READ DB"};
	XaErrors[25]={"DB Unable to Connect LOG DB"};

	XaErrors[41]={"Event Is empty"};
	XaErrors[42]={"EventNotFound"};

	XaErrors[45]={"User Does Not Exist Or Password Is Wrong"};
	XaErrors[46]={"User Is Not Unique"};
	XaErrors[47]={"Username Or Password Is Empty"};

	/*
	 * Security
	 */
	XaErrors[51]={"TOKEN Error Inserting a new TOKEN into database"};
	XaErrors[52]={"TOKEN is not valid"};
	XaErrors[53]={""};
	XaErrors[54]={""};

	/*
	 * Web Services
	 */
	XaErrors[101]={"WS Requested Without XmlData Parameter"};
	XaErrors[102]={"WS Requested Without ReqType Parameter"};
	XaErrors[103]={"WS Requested Without Encoding Parameter"};
	XaErrors[104]={"WS Requested Without Encryption Parameter"};
	XaErrors[105]={"WS Requested Without ConsumerId Parameter"};
	XaErrors[106]={"WS Requested Without ResType Parameter"};

	XaErrors[107]={"WS Requested Encrypted But No Encoded"};
	XaErrors[108]={};//GetEncodedData
	XaErrors[109]={"WS Requested Encoding Is Not Supported"};
	XaErrors[110]={"WS ConsumerId Is Invalid"};
	XaErrors[111]={""};//GetDecryptedData
	XaErrors[112]={"WS Username Is Empty"};
	XaErrors[113]={"WS Password Is Empty"};
	XaErrors[114]={"WS Object Is Empty"};
	XaErrors[115]={"WS Event Is Empty"};
	XaErrors[116]={"WS Number of Parameters is 0"};
	XaErrors[117]={"WS Object Is Not XaUser But Token is Empty"};
	XaErrors[118]={"WS Event Is Not Login But Token is Empty"};
	XaErrors[119]={"WS Called Object Does Not Exist"};
	XaErrors[120]={""};
	XaErrors[121]={""};
	XaErrors[122]={""};
	XaErrors[123]={""};

	/*
	 * Model
	 */
	XaErrors[201]={"BackEnd Call Type Is Not Supported"};

	/*Front End Errors*/
	XaErrors[611]={"Called Object Does Not Exist"};

	XaErrors[621]={"Event Is empty"};

	XaErrors[701]={"CURL Error Performing Request"};

};

XaLibError::~XaLibError(){
};