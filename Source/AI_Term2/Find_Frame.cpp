#include "Total.h"

using namespace std;

void Find_Frame::finding_Frame(map<string, vector<string>>&slot_data, string domain, string is_qna, set<string> pattern){

	Util ut;
	ut.file_to_map("frame\\Index.txt", frame_idx);

	fr_domain = domain;	//domain
	fr_focus = pattern;	//focus
	fr_is_qna = is_qna;	//is_qna

	map<set<string>,string>::iterator it;

	it = frame_idx.find(fr_focus);
	if(it != frame_idx.end())
		fr_name = it->second;
	else {
		//focus 정보 부족
	}


	ut.file_to_map("frame\\" + fr_name + ".txt", slot_data);


};



void Find_Frame::slot_insert(vector<pair<string, vector<string>>> &query_map,map<string, vector<string>>&slot_data,map<string, string>&slot_map){

	vector<pair<string, vector<string>>>::iterator query_it;
	vector<string>::iterator slot_it2;
	map<string, vector<string>>::iterator slot_it;

	for(slot_it= slot_data.begin(); slot_it!= slot_data.end(); slot_it++){
		char i = '1';

		for(query_it=query_map.begin(); query_it!= query_map.end(); query_it++){
			if(query_it->second[1] == slot_it->first){
				slot_it2 = slot_it->second.begin();

				if(slot_it2[1]=="*"){
					slot_map.insert(pair<string, string>(slot_it->first+i+"*", query_it->first));
					i++;
				} else {
					slot_map.insert(pair<string, string>(slot_it->first+i, query_it->first));
					i++;
				}
			}
		}
		if(slot_it->second[1]!="*"){
			slot_map.insert(pair<string, string>(slot_it->first+'1', "EMPTY"));
		}
	}
};

void Find_Frame::print_Frame(map<string, string>& slot_map){

	ofstream ofs;
	ofs.open("frame\\slot_result\\frame.txt");
	
	ofs << "Name : " << fr_name << endl;
	ofs << "Domain : " << fr_domain << endl;

	set<string>::iterator set_it;
	ofs << "Focus : ";
	for(set_it=fr_focus.begin(); set_it!=fr_focus.end(); set_it++){
		 ofs << *set_it << " ";
	}
	ofs << endl << endl;	// Focus : Local Forcast

	map<string, string>::iterator map_it;
	ofs << "Slot" << endl;
	for(map_it=slot_map.begin(); map_it!= slot_map.end(); map_it++){
		ofs << "\t" << map_it->first << " : " << map_it->second << endl;
	}
	

}