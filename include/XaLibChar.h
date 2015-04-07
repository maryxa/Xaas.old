#ifndef XALIBCHAR_H
#define XALIBCHAR_H

#include <XaLibBase.h>

using namespace std;

class XaLibChar : protected XaLibBase {

	private:

		static inline bool is_base64(unsigned char c);

	protected:

	public:

		XaLibChar();
		~XaLibChar();

		string ClearMultiByteChars(string StringToClear);
		string ClearXmlEntitiesBasic(string StringToClear);
		string ClearXmlFrimm(string StringToClear);
		string ClearSqlEntities(string StringToClear);
		string RemovePlus(string StringToDecode);
		string imgBase64RemPlus(string StringToDecode);
		string UrlDecode(string StringToDecode);
		string UrlEncode(string StringToEncode);
		string B64Decode(string StringToDecode);
		string B64Encode(string StringToEncode);
		string B64Encode(char * CharToEncode, int size);
		string RemoveRwNamespace(string StringToDecode);
		string RemoveRwNamespaceHotelSearch(string StringToDecode);
		string RemoveCarriageReturn(string StringToDecode);
		string RemoveNewLine(string StringToDecode);
		string RemoveNs(string StringToDecode);
		string RemoveEmptyspace(string StringToDecode);
		string RemoveSpaceChar(string StringToDecode);
		string UnclearToNormalChar(string StringToDecode);
        string ClearCarriageReturn(string StringToClear);
        string ClearChars(string StringToClear);
        string ClearFrimmDesc(string StringToClear);
        int CountCharOccurrences(string String, string Char);
        string UnclearAmpersand(string StringToUnClear);
};
#endif
