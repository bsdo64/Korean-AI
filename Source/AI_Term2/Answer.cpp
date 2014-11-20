#include "Total.h"

bool Answer::finding_script(string domain, string name, map<set<string>, string> &frame_idx){
	map<set<string>, string>::iterator it;

	for(it=frame_idx.begin(); it!=frame_idx.end(); it++){
		
		if(it->second==name){
			return true;
		} else if(it == frame_idx.end()){
			return false;
		} else{
			continue;
		}

	}
	return false;
}

bool Answer::db_check(map<string, string> &answer_map,string domain, map<string, string> &slot_map, map<string, vector<pair<int, map<string, string>>>> &db_map){
	

	map<string,string>::iterator slot_map_it;
	map<string, vector<pair<int, map<string, string>>>>::iterator it_db = db_map.begin();
	vector<pair<int, map<string, string>>>::iterator it_db2;
	map<string, string>::iterator db_map_it;

	int star = 0;
	string answerword = "";

	for(slot_map_it=slot_map.begin(); slot_map_it!=slot_map.end(); slot_map_it++){
		if(slot_map_it->first.substr(slot_map_it->first.length()-1,1)=="*"){
			answerword =slot_map_it->first.substr(0,slot_map_it->first.length()-1);
			star++;
		}
	}

	for(slot_map_it=slot_map.begin(); slot_map_it!=slot_map.end(); slot_map_it++){
		if(db_map.find(domain) != db_map.end()){
			it_db = db_map.find(domain);
			for(it_db2 = it_db->second.begin(); it_db2 != it_db->second.end(); it_db2++){
				db_map_it = it_db2->second.find(slot_map_it->first.substr(0,slot_map_it->first.length()-1));
				
				if(db_map_it != it_db2->second.end()){
					if(db_map_it->second==slot_map_it->second){
						answer_map.insert(pair<string, string>(slot_map_it->first,db_map_it->second));
					}
					if((slot_map.size()-star)==answer_map.size()) {
						db_map_it = it_db2->second.find(answerword.substr(0,answerword.length()-1));
						answer_map.insert(pair<string, string>(answerword, db_map_it->second));

						return true;

					}
				}

			}
			
			
		}
	
	}

	return "";

}

void Answer::insert_value(map<string, string> &){
}
void Answer::print_response(){
}
void Answer::print_nodb_response(string ){
}
