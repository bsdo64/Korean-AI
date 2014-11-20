#include "Total.h"

void Database::call_DB(map<string, vector<pair<int, map<string, string>>>> &db_map) {

	vector<pair<int, map<string, string>>> db;

	
	Util ut;

	ut.file_to_vector("./db/Weather.txt", db);
	db_map.insert(pair<string, vector<pair<int, map<string, string>>>>("Weather", db));
	db.clear();

	ut.file_to_vector("./db/Temperature.txt", db);
	db_map.insert(pair<string, vector<pair<int, map<string, string>>>>("Temperature", db));
	db.clear();

	ut.file_to_vector("./db/Contact.txt", db);
	db_map.insert(pair<string, vector<pair<int, map<string, string>>>>("Contact", db));
	db.clear();

	ut.file_to_vector("./db/Message.txt", db);
	db_map.insert(pair<string, vector<pair<int, map<string, string>>>>("Message", db));
	db.clear();


}
