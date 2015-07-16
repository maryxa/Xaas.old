#include <XaLibBase.h>

#include <string>
#include <cstring>
#include <map>
#include <vector>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <stdio.h>
#include <fstream>
#include <stdexcept>
#include <new>
#include <algorithm>
#include <time.h>
#include <assert.h>
#include <thread>
#include <future>
#include <unistd.h>
#include <iomanip>
#include <memory>

#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>

#include <openssl/sha.h>
#include <openssl/aes.h>
#include <openssl/evp.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <openssl/rand.h>
#include <openssl/conf.h>

using namespace std;

XaLibBase::XaLibBase(){

};

string XaLibBase::FromIntToString(int IntValue){

	return to_string(IntValue);
};

int XaLibBase::FromStringToInt(string StringValue){

	return atoi(StringValue.c_str());
};

unsigned int XaLibBase::FromHexStringToUnsignedInt(string StringValue){
	
	unsigned int IntValue;   
	std::stringstream ss;
	ss << std::hex << StringValue;
	ss >> IntValue;

	return IntValue;
};

string XaLibBase::FromFloatToString(float FloatValue){

	return to_string(FloatValue);
};

float XaLibBase::FromStringToFloat(string StringValue){

	return atof(StringValue.c_str());
};


string XaLibBase::FromDoubleToString(double DoubleValue){

	return to_string(DoubleValue);
};

double XaLibBase::FromStringToDouble(string StringValue){

	return atof(StringValue.c_str());
};

string XaLibBase::FromCharToString(char CharValue){
	
	stringstream ssStream;
	ssStream << CharValue;
	string StringValue = ssStream.str();

	return StringValue;
};

string XaLibBase::FromCharArrayToString(char CharValue[]){
	
	string StringValue(CharValue);

	return StringValue;
};

char* XaLibBase::FromStringToCharArray(string StringValue){

	int StringSize=StringValue.size();

	char* CharValue = new char[StringSize+1];
	
	for (int i=0;i<=StringSize;i++) {
		CharValue[i]=StringValue[i];
	}

	return CharValue;
};

string XaLibBase::FromStringToHex(string StringValue){

	stringstream str;
	str << StringValue;

	string HexValue;
	str >> hex >> HexValue;
	return HexValue;
};

int XaLibBase::FromCharToInt(char CharValue){

	int IntValue= CharValue-48;

	return IntValue;
}

void XaLibBase::SendHtmlHeaders(){

	cout<< "Content-Type: text/html; charset=utf-8\n\n";
};

XaLibBase::~XaLibBase(){
};
