#include <XaLibCrypto.h>

#include <XaLibBase.h>
#include <iomanip>

XaLibCrypto::XaLibCrypto() {
};

string XaLibCrypto::GetSha1(string WordToCrypt) {

	string WordToCryptStr=WordToCrypt;
	string WordCrypted;

	const char* WordToCryptChr=WordToCryptStr.c_str();
	int i;

	SHA_CTX sha;

	SHA1_Init(&sha); //Initializing

	SHA1_Update(&sha, WordToCryptChr, strlen(WordToCryptChr)); //Calculation

	unsigned char buffer_sha[20];

	SHA1_Final ( buffer_sha, &sha);//Insert in the buffer		
	
	
	for (i=0;i<20;i++) {
	
		int ia = (int)buffer_sha[i];
		
		//cout<<ia<<endl;
		std::stringstream ss;
		ss << setfill('0') << setw(2)<< hex<< ia;

		string result = ss.str();
		//cout<<result<<endl;

		WordCrypted.append(result);
	}

	return WordCrypted;

};

string XaLibCrypto::GetSha2(string WordToCrypt) {

	string WordToCryptStr=WordToCrypt;
	string WordCrypted;

	const char* WordToCryptChr=WordToCryptStr.c_str();
	int i;

	SHA256_CTX sha;

	SHA256_Init(&sha); //Initializing

	SHA256_Update(&sha, WordToCryptChr, strlen(WordToCryptChr)); //Calculation

	unsigned char buffer_sha[32];

	SHA256_Final ( buffer_sha, &sha);//Insert in the buffer

	for (i=0;i<32;i++) {
	
		int ia = (int)buffer_sha[i];
		std::stringstream ss;
		ss << setfill('0') << setw(2)<< hex<< ia;
		string result = ss.str();

		WordCrypted.append(result);
	}

	return WordCrypted;

};

string XaLibCrypto::AesEncrypt(string StringToEncrypt) {
	
	char* intext=XaLibBase::FromStringToCharArray(StringToEncrypt);

	unsigned char outbuf[StringToEncrypt.size()];

	int outlen;
	int tmplen;

	unsigned char key[] = {0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,'a','a','a','a','a','a','a','a','a','a','a','a'};
	//char intext[] = "12435";

	EVP_CIPHER_CTX ctx;
	EVP_CIPHER_CTX_init(&ctx);
	EVP_EncryptInit_ex(&ctx, EVP_aes_256_ecb(), NULL, key, NULL);

	if(!EVP_EncryptUpdate(&ctx, outbuf, &outlen, (unsigned char*)intext, strlen(intext))) {
		return 0;
	}

	if(!EVP_EncryptFinal_ex(&ctx, outbuf + outlen, &tmplen)) {
		return 0;
	}

	outlen += tmplen;

	EVP_CIPHER_CTX_cleanup(&ctx);

	//string EncryptedValue=XaLibBase::FromCharArrayToString(reinterpret_cast<char*>(outbuf));

	string EncryptedValue;

	for (int j=0;j<outlen;j++){
		string StringValue=XaLibBase::FromCharToString(outbuf[j]);
		EncryptedValue.append(StringValue);
	}

	//stringstream EncryptedValue;
	//EncryptedValue.write(reinterpret_cast<char*>(&outbuf),outlen);

	
	//cout<<EncryptedValue.str()<<endl;
		//cout<<sizeof(outbuf)<<endl;

	
	//cout<<StringToEncrypt<<"::"<<this->AesDecrypt(EncryptedValue)<<endl;
	//this->AesDecrypt(EncryptedValue);
	//outbuf[0]=0;
	//cout<<"ppppppppppippo  :"<<this->AesDecrypt(EncryptedValue)<<endl;
	return EncryptedValue;

};

string XaLibCrypto::AesDecrypt(string EncryptedValue) {
	int outlen;
	int tmplen;

	int EncryptedValueSize=EncryptedValue.size();
	//cout<<EncryptedValueSize<<endl;
	
	char intext[EncryptedValueSize+1];
	
	for(int k=0;k<EncryptedValueSize;k++){
	
		intext[k]=EncryptedValue[k];
	}
	//cout<<intext<<endl;
	intext[EncryptedValueSize+1]='\0';
	//char* intext=XaLibBase::FromStringToCharArray(EncryptedValue);
	unsigned char key[] = {0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,'a','a','a','a','a','a','a','a','a','a','a','a'};

    unsigned char outbuf[EncryptedValue.size()];

    EVP_CIPHER_CTX ctx;
    EVP_CIPHER_CTX_init(&ctx);

	
	
    EVP_DecryptInit_ex(&ctx,EVP_aes_256_ecb(),NULL,key,NULL);
	
	EVP_CIPHER_CTX_set_padding(&ctx,0);
	EVP_DecryptUpdate(&ctx,outbuf, &outlen,(unsigned char*)intext,EncryptedValueSize+1);

    EVP_DecryptFinal_ex(&ctx,outbuf +outlen, &tmplen);
	outlen += tmplen;

	EVP_CIPHER_CTX_cleanup(&ctx);

    //Just to be nice, we'll add a zero at the end of the decrypted string
    //outbuf[outlen+tmplen] = 0;
	string DecryptedValue;

	for (int j=0;j<outlen;j++){
		string StringValue=XaLibBase::FromCharToString(outbuf[j]);
		DecryptedValue.append(StringValue);
	}
	//cout<<intext<<"::"<<EncryptedValue<<"::"<<DecryptedValue<<endl;
	//string DecryptedValue=XaLibBase::FromCharArrayToString(reinterpret_cast<char*>(outbuf));

	outbuf[0]=0;

	return DecryptedValue;

};



string XaLibCrypto::AesEncryptCtr(string StringToEncrypt, string EncryptionKey, string EncryptionIV) {
	
#ifdef __APPLE__

	return "";
	
#elif __MACH__

	return "";

#else

	char* intext=XaLibBase::FromStringToCharArray(StringToEncrypt);

	unsigned char outbuf[strlen(intext)];

	int outlen;
	int tmplen;

	unsigned char key[32];
	for (int i=0; i<32; i++) {
		key[i]=XaLibBase::FromHexStringToUnsignedInt(EncryptionKey.substr(2*i,2));
	}
	unsigned char iv[16];
	for (int i=0; i<16; i++) {
		iv[i]=XaLibBase::FromHexStringToUnsignedInt(EncryptionIV.substr(2*i,2));
	}

	EVP_CIPHER_CTX ctx;
	EVP_CIPHER_CTX_init(&ctx);
	EVP_EncryptInit_ex(&ctx, EVP_aes_256_ctr(), NULL, key, iv);

	if(!EVP_EncryptUpdate(&ctx, outbuf, &outlen, (unsigned char*)intext, strlen(intext))) {
		return 0;
	}

	if(!EVP_EncryptFinal_ex(&ctx, outbuf + outlen, &tmplen)) {
		return 0;
	}

	outlen += tmplen;

	EVP_CIPHER_CTX_cleanup(&ctx);

	string EncryptedValue;

	for (int j=0;j<outlen;j++){
		string StringValue=XaLibBase::FromCharToString(outbuf[j]);
		EncryptedValue.append(StringValue);
	}

	return EncryptedValue;

#endif
};

string XaLibCrypto::AesDecryptCtr(string EncryptedValue, string EncryptionKey, string EncryptionIV) {

#ifdef __APPLE__

	return "";
	
#elif __MACH__

	return "";

#else

	int outlen;
	int tmplen;

	int EncryptedValueSize=EncryptedValue.size();

	char intext[EncryptedValueSize+1];
	
	for(int k=0;k<EncryptedValueSize;k++){
		intext[k]=EncryptedValue[k];
	}
	intext[EncryptedValueSize+1]='\0';

	unsigned char key[32];
	for (int i=0; i<32; i++) {
		key[i]=XaLibBase::FromHexStringToUnsignedInt(EncryptionKey.substr(2*i,2));
	}
	unsigned char iv[16];
	for (int i=0; i<16; i++) {
		iv[i]=XaLibBase::FromHexStringToUnsignedInt(EncryptionIV.substr(2*i,2));
	}

    unsigned char outbuf[EncryptedValue.size()];

    EVP_CIPHER_CTX ctx;
    EVP_CIPHER_CTX_init(&ctx);

    EVP_DecryptInit_ex(&ctx,EVP_aes_256_ctr(),NULL,key,iv);
	EVP_DecryptUpdate(&ctx,outbuf, &outlen,(unsigned char*)intext,EncryptedValueSize+1);

    EVP_DecryptFinal_ex(&ctx,outbuf +outlen, &tmplen);
	outlen += tmplen;

	EVP_CIPHER_CTX_cleanup(&ctx);

    //Just to be nice, we'll add a zero at the end of the decrypted string
    //outbuf[outlen+tmplen] = 0;
	string DecryptedValue;

	for (int j=0;j<outlen;j++){
		string StringValue=XaLibBase::FromCharToString(outbuf[j]);
		DecryptedValue.append(StringValue);
	}

	outbuf[0]=0;

//	Log.LibLOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"decrypted string : "+DecryptedValue );
	
	return DecryptedValue;
#endif

};

XaLibCrypto::~XaLibCrypto() {

};