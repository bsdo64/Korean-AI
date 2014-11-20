#include "Total.h"

using namespace std;

string Domain_Analysis::analyze_domain(vector<pair<string, vector<string>>> &q) {
	
	map<string, string> domain_map;
	string domain_str;

	Util ut;
	ut.file_to_map("pattern\\Domain.txt", domain_map);

	vector<pair<string, vector<string>>>::iterator it;
	map<string, string>::iterator itm;

	for(it = q.begin(); it != q.end(); it++){
		itm=domain_map.find((*it).second[1]);

		if(itm != domain_map.end()){
			domain_str = (*itm).second;
		}
	}

	return domain_str;
}				//domain이 어떤 정보를 갖고 있는지 불러오는 과정