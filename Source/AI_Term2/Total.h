#include <iostream>			//각각의 소스 파일에서 사용될 class를 헤더에서 생성시킵니다.
#include <fstream>
#include <string>
#include <map>
#include <sstream>
#include <vector>
#include <set>
#include <time.h>

using namespace std;

class POS_tagger {
public:
	void run();
};

class Name_Entity_dic {
public:
	void print();
};

class Sementic_Database {
public:
	void run(map<string, vector<string>> &);
};

class DB_Result {
public:
	void print(map<string, vector<string>> &);
};

class Query_Analysis {
public:
	 string domain_str;		// Domain
	 string is_qna;			// 질문인지 명령문인지
	 set<string> pattern;	// Focus
public:
	string analyze(map<string, vector<string>> &, vector<pair<string, vector<string>>> &,map<string, string> &);
	void print(vector<pair<string, vector<string>>> &);

	 string get_domain();
	 string get_is_qna();
	 set<string> get_pattern();
};

class Domain_Classification {
public:
	void pattern_call(map<string, string> &, string);
	void pattern_insert(vector<pair<string, vector<string>>> &, map<string, string> &, set<string> &); 
};

class Domain_Analysis {
public:
	string analyze_domain(vector<pair<string, vector<string>>> &);
};

class Normalization {
public:
	map<string, vector<string>> s_map;
public:
	class Normalization(map<string, vector<string>> &sementic_map){
		s_map = sementic_map;
	}
public:
	void test_date(vector<pair<string, vector<string>>> &);
	void test_rdate(vector<pair<string, vector<string>>> &);
	void test_word(vector<pair<string, vector<string>>> &);
};

class Util {
public:
	void file_to_map(string, map<string, vector<string>> &);
	void file_to_map(string, map<string, string> &);
	void file_to_map(string, map<string, int> &);
	void file_to_map(string, string, map<string, vector<string>> &);
	void file_to_map(string , map<set<string>, string> &);
	string file_to_vector(string , vector<pair<string, vector<string>>> &, map<string, vector<string>> &, set<string> &, string &, string &, set<string>&);
	void file_to_vector(string, vector<pair<int, map<string, string>>> &);
	void file_to_vector(string, vector<string>&);
	void file_to_set(string, set<string> &);
};

class Find_Frame {
public:
	string fr_name;
	string fr_domain;
	string fr_is_qna;
	set<string> fr_focus;
	map<set<string>, string> frame_idx;
public:
	void finding_Frame(map<string, vector<string>> &, string , string , set<string> );
	void slot_insert(vector<pair<string, vector<string>>> &,map<string, vector<string>>&,map<string, string>&);
	void print_Frame(map<string, string>&);
};


class Database {
public:
	void call_DB(map<string, vector<pair<int, map<string, string>>>> &);
};

class Answer_Function {
public:
	string fr_name;
	string fr_domain;
	string fr_is_qna;
	set<string> fr_focus;
	map<set<string>, string> frame_idx;
	map<string, string> slot_map;
	map<string, vector<pair<int, map<string, string>>>> db_map;
	vector<pair<string, vector<string>>> query_map;
	vector<int> slot_1;
	vector<int> slot_2;
public:

	class Answer_Function(Find_Frame f, map<string, string> s,map<string, vector<pair<int, map<string, string>>>> db,vector<pair<string, vector<string>>> query ){
		fr_name = f.fr_name;
		fr_domain = f.fr_domain;
		fr_is_qna = f.fr_is_qna;
		fr_focus = f.fr_focus;
		frame_idx = f.frame_idx;
		slot_map = s;
		db_map = db;
		query_map = query;
		
	}

	void finding_Function();

	void db_check(vector<int>&, vector<int>&, string, vector<pair<int, map<string, string>>>&);
	void db_check(vector<int>&, vector<int>&, vector<int>&, string, string, vector<pair<int, map<string, string>>>&);

	void db_search(vector<int> &, vector<pair<int, map<string, string>>>&, string);
	void min_max_search(vector<int> &, vector<pair<int, map<string, string>>>&, string);

	void insert_answer(vector<int> &, vector<int> &);
	void insert_answer(vector<int> &, vector<int> &, vector<int> &);

	
	void	ask_temperature(vector<pair<int, map<string, string>>>);
	void	ask_weather_temperature(vector<pair<int, map<string, string>>>);
	void	ask_weather(vector<pair<int, map<string, string>>>);
	void	weather_search_location(vector<pair<int, map<string, string>>>);
	void	call_to_someone(vector<pair<int, map<string, string>>>);
	void	print_typed_number(vector<pair<int, map<string, string>>>);
	void	add_number(vector<pair<int, map<string, string>>>);
	void	del_number(vector<pair<int, map<string, string>>>);
	void	del_typed_number(vector<pair<int, map<string, string>>>);
	void	print_contact_number(vector<pair<int, map<string, string>>>);
	void	recieved_message(vector<pair<int, map<string, string>>>);
	void	recieved_name_message(vector<pair<int, map<string, string>>>);
	void	count_message(vector<pair<int, map<string, string>>>);
	void	count_name_message(vector<pair<int, map<string, string>>>);
	void	delete_from_name_message(vector<pair<int, map<string, string>>>);
	void	delete_from_message(vector<pair<int, map<string, string>>>);
	void	delete_message(vector<pair<int, map<string, string>>>);
	void	send_message(vector<pair<int, map<string, string>>>);
	void	temperature_compare_search_location(vector<pair<int, map<string, string>>>);
	void	temperature_min_max_search_location(vector<pair<int, map<string, string>>>);

	void response(vector<int> &, string, vector<pair<int, map<string, string>>>&, map<string, string>&);

	vector<int> set_slot1(vector<int> v){
		return slot_1=v;
	}
	vector<int> set_slot2(vector<int> v){
		return slot_2=v;
	}
};