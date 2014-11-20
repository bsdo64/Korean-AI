#include "Total.h"

using namespace std;

void Domain_Classification::pattern_call(map<string, string> &p, string domain) {

	string s1 = "pattern\\";

	Util ut;
	ut.file_to_map(s1 + domain + ".txt", p);

}					//pattern을 구분하는 최소한의 정보를 불러옴

void Domain_Classification::pattern_insert(vector<pair<string, vector<string>>> &q, map<string, string> &p, set<string> &s) {
	
	vector<pair<string, vector<string>>>::iterator it;
	map<string, string>::iterator it_map;

	for(it = q.begin(); it != q.end(); it++) {
				
		it_map = p.find((*it).second[1]);
				
		if(it_map != p.end()) {
			s.insert((*it_map).second);
			(*it).second.push_back((*it_map).second);
		}
		else {
			(*it).second.push_back("");
		}
	}
}					//pattern들을 query_map에 추가하는 과정
