#include <XaLibToken.h>
#include <XaLibCrypto.h>

XaLibToken::XaLibToken(){
};

int XaLibToken::ValidateToken(const string& Token) {

	DbResMap DbRes=XaLibSql::FreeQuery(DB_SESSION,"SELECT XaUser_ID FROM XaUserToken WHERE token=\""+Token+"\"");

	if (DbRes.size()!=0){

		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"TOKEN Is valid for XaUser_ID-> "+ DbRes[0]["XaUser_ID"]);
		return atoi(DbRes[0]["XaUser_ID"].c_str());

	} else {

		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"TOKEN Is Not Valid");
		throw 52;
	}
};

int XaLibToken::CheckUserToken(const int& XaUser_ID) {

	DbResMap DbRes=XaLibSql::FreeQuery(DB_SESSION,"SELECT id  FROM XaUserToken WHERE XaUser_ID=\""+to_string(XaUser_ID)+"\"");

	if (DbRes.size()!=0){

		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"TOKEN Is valid for XaUser_ID-> "+ DbRes[0]["XaUser_ID"]);
		return DbRes[0]["XaUser_ID"];

	} else {

		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"TOKEN Is Not Valid");
		return 0;
	}
};

/* TESTARE IL CASO DI TOKEN DUPLICATO */
string XaLibToken::CreateToken(const int& XaUser_ID) {

	string Token=GenerateToken();

	XaLibSql LibSql;
	LibSql.LockTable(DB_SESSION,"XaUserToken");
	DbResMap DbRes=LibSql.FreeQuery(DB_SESSION,"SELECT id FROM XaUserToken WHERE token=\""+Token+"\"");

	//VERIFING DOES NOT EXIST IN THE DATABASE
	if (DbRes.size()!=0){

		LibSql.UnlockTable(DB_SESSION);
		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"TOKEN -> Generated Token Already Exists");
		
		this->CreateToken(XaUser_ID);

		//mettere un limite al numero tentativi xon un contatore privato

	} else {

		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"TOKEN -> Generated Token Is Valid");

		vector<string> VectorFields {"XaUser_ID","token","status"};
		vector<string> VectorValues{FromIntToString(XaUser_ID),Token,"1"};

		int NextId=LibSql.Insert(DB_SESSION,"XaUserToken",VectorFields,VectorValues);
		LibSql.UnlockTable(DB_SESSION);

		if (NextId==0){

			LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"TOKEN Error Inserting a new TOKEN into database");
			throw 51;

		} else {

			LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"TOKEN -> Inserted a new Token into Database" + XaLibBase::FromIntToString(NextId));
		}	
	}

	return Token;
};

string XaLibToken::GenerateToken(){

	mt19937_64 generator (chrono::system_clock::now().time_since_epoch().count());
	string MtSring=to_string(generator());

	LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"TOKEN Generated Mersenne Key ->"+ MtSring);

	string SeedString=MtSring+SESSION.ClientIp;

	LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"TOKEN Generated Browser Signature ->"+ SeedString);

	return XaLibCrypto::GetSha1(SeedString);;
};

XaLibToken::~XaLibToken(){
};