#ifndef XALIBCRYPTO_H
#define XALIBCRYPTO_H

#include <XaLibBase.h>
#include <XaLibLog.h>


#if OPENSSL_VERSION_NUMBER >= 0x0090808fL
#define LIBSSH2_AES_CTR 0
#else
#define LIBSSH2_AES_CTR 1
#endif

extern XaLibLog LOG;
extern XaSettings SETTINGS;

class XaLibCrypto : protected XaLibBase {

	private:

	protected:

	public:

		XaLibCrypto();
		~XaLibCrypto();

		string GetSha1(string WordToCrypt);
		string GetSha2(string WordToCrypt);

		string AesEncrypt(string StringToEncrypt);
		string AesDecrypt(string EncryptedValue);
		string AesEncryptCtr(string StringToEncrypt, string EncryptionKey, string EncryptionIV);
		string AesDecryptCtr(string EncryptedValue, string EncryptionKey, string EncryptionIV);
};
#endif
