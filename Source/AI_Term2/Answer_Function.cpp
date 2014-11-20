#include "Total.h"

void Answer_Function::finding_Function(){

	map<string, vector<pair<int, map<string, string>>>> ::iterator it_map;

	//db_index�� fr_name�� ���� db �����ϱ�
	Util ut;
	map<string, string> db_index;
	ut.file_to_map("./db/Index.txt", db_index);
	map<string, string>::iterator idx_iter;
	idx_iter = db_index.find(fr_name);
	if(idx_iter == db_index.end()){
		cout << "focus������ �����մϴ� ������ �ٽ� �Է����ּ���" << endl;	//focus �˻� ����
		return; 
	}

	it_map = db_map.find(idx_iter->second);

	if(it_map== db_map.end()){
		cout << "������ �����մϴ�. ������ �ٽ� �Է����ּ���" << endl;	//focus->name �˻� ���� (ex_ local, forcast => ask_weather)
		return;
	}

	if(fr_name == "ask_temperature"){
		ask_temperature(it_map->second);
	} else if(fr_name == "ask_weather_temperature"){
		ask_weather_temperature(it_map->second);
	} else if(fr_name == "ask_weather"){
		ask_weather(it_map->second);
	} else if(fr_name == "weather_search_location"){
		weather_search_location(it_map->second);
	} else if(fr_name == "call_to_someone"){
		call_to_someone(it_map->second);
	} else if(fr_name == "print_typed_number"){
		print_typed_number(it_map->second);
	} else if(fr_name == "add_number"){
		add_number(it_map->second);
	} else if(fr_name == "del_number"){
		del_number(it_map->second);
	} else if(fr_name == "del_typed_number"){
		del_typed_number(it_map->second);
	} else if(fr_name == "print_contact_number"){
		print_contact_number(it_map->second);
	} else if(fr_name == "recieved_message"){
		recieved_message(it_map->second);
	} else if(fr_name == "recieved_name_message"){
		recieved_name_message(it_map->second);
	} else if(fr_name == "count_message"){
		count_message(it_map->second);
	} else if(fr_name == "count_name_message"){
		count_name_message(it_map->second);
	} else if(fr_name == "delete_from_name_message"){
		delete_from_name_message(it_map->second);
	} else if(fr_name == "delete_from_message"){
		delete_from_message(it_map->second);
	} else if(fr_name == "delete_message"){
		delete_message(it_map->second);
	} else if(fr_name == "send_message"){
		send_message(it_map->second);
	} else if(fr_name == "temperature_compare_search_location"){
		temperature_compare_search_location(it_map->second);
	} else if(fr_name == "temperature_min_max_search_location"){
		temperature_min_max_search_location(it_map->second);
	} 

}

void Answer_Function::response(vector<int> &answer, string fr_name, vector<pair<int, map<string, string>>>&db, map<string, string>&slot_map){
	
	string domain_file[] = {"Min_max", "Action", "After", "Before", "Call", "Compare", "Conjunction", "Count", "Etc", 
		"Location", "From", "Message", "Name", "Obj", "Phone_number", "City", "Add", "Delete", "All",
		"Phone_type", "Send", "Temperature", "Time", "To", "Weather", "Month", "Day", "Year", "Until"};			//��ü�� �νı� ���� ���� �Ϸ� �� ���ϵ��� domain_file�̶�� array�� �����մϴ�

	vector<int>::iterator it_ans_index;
	map<string, string>::iterator it_slot;
	vector<pair<int, map<string, string>>>::iterator it_db;
	map<string, string>::iterator it_db2;
	map<string, string>::iterator it_check;
	vector<string>::iterator it_ans;

	vector<string> answer_word;
	vector<string> answer_word2;

	string year = "";
	string month ="";
	string day = "";

	//Not �亯 �˻� - 1. EMPTY�� ���� ���
	for(it_slot=slot_map.begin(); it_slot!=slot_map.end(); it_slot++){
		if(it_slot->second=="EMPTY"){
			fr_name = fr_name+"_not";
		}
	}
	//				- 2. answer�� ���� ���
	if((answer.size()==0 && (slot_1.size()!=0 && slot_2.size()!=0)) 
		|| (answer.size()==0 && (slot_1.size()!=0))
		|| (answer.size()==0 && (slot_2.size()!=0))) {

		cout << "Matching �Ǵ� " +fr_domain+ "������ �������� �ʽ��ϴ�" << endl;
		return ;

	}
	

	//���� �м�
	Util ut;
	ut.file_to_vector("./response/"+fr_name+".txt", answer_word);
	

	//���� �ܾ Answer �Է�
	for(it_ans_index=answer.begin(); it_ans_index!=answer.end(); it_ans_index++){
		answer_word2 = answer_word;
		
		//	Date �˻� �� ��ȯ
		it_db2 = db[*it_ans_index].second.find("Date");
		if(db[*it_ans_index].second.end()!=it_db2){
			string date = it_db2->second;
			int date_int = stoi(date);
			year = to_string(date_int/10000);
			month = to_string((date_int%10000)/100);
			day = to_string(date_int%100);
			
		}

		//�ܾ� ��ȯ
		for(int j=0; j<answer_word2.size(); j++){
			
			//�ܾ� �ǹ� �˻� �� �Է�
			for(int i=0; i< (sizeof(domain_file)/sizeof(domain_file[0])) ; i++){
				int pos = answer_word2[j].find(domain_file[i]);
				int len = domain_file[i].size();
				if(pos>=0){
					string mean = domain_file[i];
					it_db2 = db[*it_ans_index].second.find(mean);
					
					if(mean=="Year"){
						answer_word2[j].replace(pos,len, year);
					}else if(mean=="Month"){
						answer_word2[j].replace(pos,len, month);
					}else if(mean=="Day"){
						answer_word2[j].replace(pos,len, day);
					} else {
						answer_word2[j].replace(pos,len,it_db2->second);
					}
				}
			}

		} 

		for(int i=0; i<answer_word2.size(); i++){
			cout << answer_word2[i] << " ";
		}
		cout << endl;
	}


}

void	Answer_Function::ask_temperature(vector<pair<int, map<string, string>>> db){

	//��ǥ �˻� -> ���� ��Ʈ�� �Է�
	
	//��ǥ x ask_temperature = 2
	vector<int> v_city;
	vector<int> v_date;
	vector<int> answer;
	db_check(v_date,v_city, answer, "Date","City",db);
	//DB �˻� �Ϸ�!!!


	//-----------------------------------------------------------------------
	//�Լ��� ��� ��� �����
	Answer_Function::insert_answer(v_date, v_city, answer);	//������ ����

	//�߰� ��� ���͸�

	//-----------------------------------------------------------------------
	Answer_Function::response(answer, fr_name, db, slot_map);

	//Cmdâ�� ����ϱ�

}
void	Answer_Function::ask_weather_temperature(vector<pair<int, map<string, string>>> db){
	
	//��ǥ �˻� -> ���� ��Ʈ�� �Է�
	
	//��ǥ x ask_weather_temperature = 2
	vector<int> v_city;
	vector<int> v_date;
	vector<int> answer;
	db_check(v_date,v_city, answer, "Date","City",db);
	//DB �˻� �Ϸ�!!!

	//-----------------------------------------------------------------------
	//�Լ��� ��� ��� �����
	Answer_Function::insert_answer(v_date, v_city, answer);	//������ ����

	//�߰� ��� ���͸�

	//-----------------------------------------------------------------------
	Answer_Function::response(answer, fr_name, db, slot_map);
	//Cmdâ�� ����ϱ�
}

void	Answer_Function::ask_weather(vector<pair<int, map<string, string>>> db){

	
	//��ǥ �˻� -> ���� ��Ʈ�� �Է�
	
	//��ǥ x ask_weather = 2
	vector<int> v_city;
	vector<int> v_date;
	vector<int> answer;
	db_check(v_date,v_city, answer, "Date","City",db);
	//DB �˻� �Ϸ�!!!


	//-----------------------------------------------------------------------
	//�Լ��� ��� ��� �����
	Answer_Function::insert_answer(v_date, v_city, answer);	//������ ����

	//�߰� ��� ���͸�

	//-----------------------------------------------------------------------

	Answer_Function::response(answer, fr_name, db, slot_map);
	//Cmdâ�� ����ϱ�

}

	
void	Answer_Function::weather_search_location(vector<pair<int, map<string, string>>> db){
	
	//��ǥ �˻� -> ���� ��Ʈ�� �Է�
	
	//��ǥ x weather_search_location = 2
	vector<int> v_weather;
	vector<int> v_date;
	vector<int> answer;
	db_check(v_date,v_weather, answer, "Date","Weather",db);
	//DB �˻� �Ϸ�!!!


	//-----------------------------------------------------------------------
	//�Լ��� ��� ��� �����
	Answer_Function::insert_answer(v_date, v_weather, answer);	//������ ����

	//�߰� ��� ���͸�

	//-----------------------------------------------------------------------
	Answer_Function::response(answer, fr_name, db, slot_map);
	//Cmdâ�� ����ϱ�

}
void	Answer_Function::call_to_someone(vector<pair<int, map<string, string>>> db){
	
	//��ǥ �˻� -> ���� ��Ʈ�� �Է�
	
	//��ǥ x call_to_someone = 1
	vector<int> v_name;
	vector<int> answer;
	db_check(v_name, answer, "Name",db);
	//DB �˻� �Ϸ�!!!


	//-----------------------------------------------------------------------
	//�Լ��� ��� ��� �����
	Answer_Function::insert_answer(v_name, answer);	//������ ����

	//�߰� ��� ���͸�
	set<string> s;
	for(int i=0; i<v_name.size(); i++){
		s.insert(db.at(v_name[i]).second.find("Name")->second);
		if(s.size()>1){
			cout << "�θ� �̻󿡰� ��ȭ�� �� �� �����ϴ�." << endl;
			return;
		}
	}

	//-----------------------------------------------------------------------
	Answer_Function::response(answer, fr_name, db, slot_map);
	//Cmdâ�� ����ϱ�

}
void	Answer_Function::print_typed_number(vector<pair<int, map<string, string>>> db){
		//��ǥ �˻� -> ���� ��Ʈ�� �Է�
	
	//��ǥ x print_typed_number = 2
	vector<int> v_name;
	vector<int> v_phone_type;
	vector<int> answer;
	db_check(v_name,v_phone_type, answer, "Name","Phone_type",db);
	//DB �˻� �Ϸ�!!!


	//-----------------------------------------------------------------------
	//�Լ��� ��� ��� �����
	Answer_Function::insert_answer(v_name, v_phone_type, answer);	//������ ����

	//�߰� ��� ���͸�

	//-----------------------------------------------------------------------
	Answer_Function::response(answer, fr_name, db, slot_map);
	//Cmdâ�� ����ϱ�

}
void	Answer_Function::add_number(vector<pair<int, map<string, string>>> db){
			//��ǥ �˻� -> ���� ��Ʈ�� �Է�
	
	//��ǥ x add_number = 2
	vector<int> v_name;
	vector<int> v_phone_type;
	vector<int> answer;
	db_check(v_name,v_phone_type, answer, "Name","Phone_type",db);
	//DB �˻� �Ϸ�!!!


	//-----------------------------------------------------------------------
	//�Լ��� ��� ��� �����
	Answer_Function::insert_answer(v_name, v_phone_type, answer);	//������ ����

	//�߰� ��� ���͸�

	//-----------------------------------------------------------------------
	Answer_Function::response(answer, fr_name, db, slot_map);
	//Cmdâ�� ����ϱ�
}
void	Answer_Function::del_number(vector<pair<int, map<string, string>>> db){
			//��ǥ �˻� -> ���� ��Ʈ�� �Է�
	
	//��ǥ x del_number = 1
	vector<int> v_name;
	vector<int> answer;
	db_check(v_name, answer, "Name",db);
	//DB �˻� �Ϸ�!!!


	//-----------------------------------------------------------------------
	//�Լ��� ��� ��� �����
	Answer_Function::insert_answer(v_name, answer);	//������ ����

	//�߰� ��� ���͸�

	//-----------------------------------------------------------------------
	Answer_Function::response(answer, fr_name, db, slot_map);
	//Cmdâ�� ����ϱ�
}
void	Answer_Function::del_typed_number(vector<pair<int, map<string, string>>> db){
	//��ǥ �˻� -> ���� ��Ʈ�� �Է�
	
	//��ǥ x del_typed_number = 2
	vector<int> v_name;
	vector<int> v_phone_type;
	vector<int> answer;
	db_check(v_name,v_phone_type, answer, "Name","Phone_type",db);
	//DB �˻� �Ϸ�!!!


	//-----------------------------------------------------------------------
	//�Լ��� ��� ��� �����
	Answer_Function::insert_answer(v_name, v_phone_type, answer);	//������ ����

	//�߰� ��� ���͸�

	//-----------------------------------------------------------------------
	Answer_Function::response(answer, fr_name, db, slot_map);
	//Cmdâ�� ����ϱ�
}
void	Answer_Function::print_contact_number(vector<pair<int, map<string, string>>> db){
	//��ǥ �˻� -> ���� ��Ʈ�� �Է�
	
	//��ǥ x print_contact_number = 1
	vector<int> v_name;
	vector<int> answer;
	db_check(v_name, answer, "Name",db);
	//DB �˻� �Ϸ�!!!


	//-----------------------------------------------------------------------
	//�Լ��� ��� ��� �����
	Answer_Function::insert_answer(v_name, answer);	//������ ����

	//�߰� ��� ���͸�

	//-----------------------------------------------------------------------
	Answer_Function::response(answer, fr_name, db, slot_map);
	//Cmdâ�� ����ϱ�
}
void	Answer_Function::recieved_message(vector<pair<int, map<string, string>>> db){
	//��ǥ �˻� -> ���� ��Ʈ�� �Է�
	
	//��ǥ x recieved_message = 1
	vector<int> v_date;
	vector<int> answer;
	db_check(v_date, answer, "Date",db);
	//DB �˻� �Ϸ�!!!


	//-----------------------------------------------------------------------
	//�Լ��� ��� ��� �����
	Answer_Function::insert_answer(v_date, answer);	//������ ����

	//�߰� ��� ���͸�


	//-----------------------------------------------------------------------
	Answer_Function::response(answer, fr_name, db, slot_map);
	//Cmdâ�� ����ϱ�
}
void	Answer_Function::recieved_name_message(vector<pair<int, map<string, string>>> db){
	//��ǥ �˻� -> ���� ��Ʈ�� �Է�
	
	//��ǥ x recieved_name_message = 2
	vector<int> v_date;
	vector<int> v_name;
	vector<int> answer;
	db_check(v_date,v_name, answer, "Date","Name",db);
	//DB �˻� �Ϸ�!!!


	//-----------------------------------------------------------------------
	//�Լ��� ��� ��� �����
	Answer_Function::insert_answer(v_date, v_name, answer);	//������ ����

	//�߰� ��� ���͸�

	//-----------------------------------------------------------------------
	Answer_Function::response(answer, fr_name, db, slot_map);
	//Cmdâ�� ����ϱ�
}
void	Answer_Function::count_message(vector<pair<int, map<string, string>>> db){
	//��ǥ �˻� -> ���� ��Ʈ�� �Է�
	
	//��ǥ x count_message = 1
	vector<int> v_date;
	vector<int> answer;
	db_check(v_date, answer, "Date",db);
	v_date.size();
	//DB �˻� �Ϸ�!!!


	//-----------------------------------------------------------------------
	//�Լ��� ��� ��� �����
	Answer_Function::insert_answer(v_date, answer);	//������ ����

	//�߰� ��� ���͸�

	//-----------------------------------------------------------------------
	Answer_Function::response(answer, fr_name, db, slot_map);
	//Cmdâ�� ����ϱ�
}
void	Answer_Function::count_name_message(vector<pair<int, map<string, string>>> db){
	//��ǥ �˻� -> ���� ��Ʈ�� �Է�
	
	//��ǥ x count_name_message = 2
	vector<int> v_date;
	vector<int> v_name;
	vector<int> answer;
	db_check(v_date,v_name, answer, "Date","Name",db);
	//DB �˻� �Ϸ�!!!


	//-----------------------------------------------------------------------
	//�Լ��� ��� ��� �����
	Answer_Function::insert_answer(v_date, v_name, answer);	//������ ����

	//�߰� ��� ���͸�


	//-----------------------------------------------------------------------
	Answer_Function::response(answer, fr_name, db, slot_map);
	//Cmdâ�� ����ϱ�
}
void	Answer_Function::delete_from_name_message(vector<pair<int, map<string, string>>> db){
	//��ǥ �˻� -> ���� ��Ʈ�� �Է�
	
	//��ǥ x delete_from_message = 2
	vector<int> v_date;
	vector<int> v_name;
	vector<int> answer;
	db_check(v_date,v_name, answer, "Date","Name",db);
	//DB �˻� �Ϸ�!!!


	//-----------------------------------------------------------------------
	//�Լ��� ��� ��� �����
	Answer_Function::insert_answer(v_date, v_name, answer);	//������ ����

	//�߰� ��� ���͸�

	//-----------------------------------------------------------------------
	Answer_Function::response(answer, fr_name, db, slot_map);
	//Cmdâ�� ����ϱ�
}
void	Answer_Function::delete_message(vector<pair<int, map<string, string>>> db){
	//��ǥ �˻� -> ���� ��Ʈ�� �Է�
	
	//��ǥ x delete_message = 1
	int row_num = db.size();
	//DB �˻� �Ϸ�!!!

	//-----------------------------------------------------------------------
	//�Լ��� ��� ��� �����
	to_string(row_num);
	//-----------------------------------------------------------------------
	
	//cout << "�޼��� " + row_num + "���� ��� �����Ͽ����ϴ�." << endl;
	//Cmdâ�� ����ϱ�
	
}
void	Answer_Function::delete_from_message(vector<pair<int, map<string, string>>> db){
	//��ǥ �˻� -> ���� ��Ʈ�� �Է�
	
	//��ǥ x delete_from_message = 1
	vector<int> v_date;
	vector<int> answer;
	db_check(v_date, answer, "Date",db);
	//DB �˻� �Ϸ�!!!


	//-----------------------------------------------------------------------
	//�Լ��� ��� ��� �����
	Answer_Function::insert_answer(v_date, answer);	//������ ����

	//�߰� ��� ���͸�

	//-----------------------------------------------------------------------
	Answer_Function::response(answer, fr_name, db, slot_map);
	//Cmdâ�� ����ϱ�
}
void	Answer_Function::send_message(vector<pair<int, map<string, string>>> db){
	//��ǥ �˻� -> ���� ��Ʈ�� �Է�
	
	//��ǥ x send_message = 1
	vector<int> v_name;
	vector<int> answer;
	db_check(v_name, answer, "Name",db);
	//DB �˻� �Ϸ�!!!


	//-----------------------------------------------------------------------
	//�Լ��� ��� ��� �����
	Answer_Function::insert_answer(v_name, answer);	//������ ����

	//�߰� ��� ���͸�

	//-----------------------------------------------------------------------
	Answer_Function::response(answer, fr_name, db, slot_map);
	//Cmdâ�� ����ϱ�
}
void	Answer_Function::temperature_compare_search_location(vector<pair<int, map<string, string>>> db){
	//��ǥ �˻� -> ���� ��Ʈ�� �Է�
	
	//��ǥ x temperature_compare_search_location = 2
	vector<int> v_date;
	vector<int> v_temp;
	vector<int> answer;
	db_check(v_date, answer, "Date", db);	//��¥
	db_check(v_temp, answer, "Temperature", db);	//�µ�
	string compare = slot_map.find("Compare1*")->second;
	db_search(v_temp, db, compare);	//compare
	//DB �˻� �Ϸ�!!!

	//-----------------------------------------------------------------------
	//�Լ��� ��� ��� �����	��¥, �µ�, compare,
	Answer_Function::insert_answer(v_date, v_temp, answer);	//������ ����

	//�߰� ��� ���͸�

	//-----------------------------------------------------------------------
	Answer_Function::response(answer, fr_name, db, slot_map);
	//Cmdâ�� ����ϱ�
}
void	Answer_Function::temperature_min_max_search_location(vector<pair<int, map<string, string>>> db){
	//��ǥ �˻� -> ���� ��Ʈ�� �Է�
	
	//��ǥ x temperature_min_max_search_location = 2
	vector<int> v_date;
	vector<int> answer;
	db_check(v_date, answer, "Date",db);
	string compare = slot_map.find("Compare1*")->second;
	min_max_search(v_date, db, compare);
	//DB �˻� �Ϸ�!!!

	//-----------------------------------------------------------------------
	//�Լ��� ��� ��� �����
	Answer_Function::insert_answer(v_date, answer);	//������ ����

	//�߰� ��� ���͸�

	//-----------------------------------------------------------------------
	Answer_Function::response(answer, fr_name, db, slot_map);
	//Cmdâ�� ����ϱ�
}

void Answer_Function::insert_answer(vector<int> &slot1, vector<int> &answer){
	vector<int>::iterator vit1;
	for(vit1=slot1.begin(); vit1!=slot1.end(); vit1++){
		answer.push_back(*vit1);
	}
}
void Answer_Function::insert_answer(vector<int> &slot1,vector<int> &slot2, vector<int> &answer){
	vector<int>::iterator vit1;
	vector<int>::iterator vit2;
	for(vit1=slot1.begin(); vit1!=slot1.end(); vit1++){
		for(vit2=slot2.begin(); vit2!=slot2.end(); vit2++){
			if(*vit1 == *vit2){
				answer.push_back(*vit1);
			}
		}
	}
}

void Answer_Function::db_check(vector<int> &db_slot1, vector<int> &db_slot2, vector<int> &answer, string val1, string val2, vector<pair<int, map<string, string>>>& db){
	
	vector<pair<int, map<string, string>>>::iterator iter;	//db iter
	map<string, string>::iterator iter2;	//db��iter

	map<string, string>::iterator it;

	vector<string> it_vec;
	set<string>::iterator it_set;

	vector<string> db_slot1_val;
	vector<string> db_slot2_val;

	char val1_number = '0';
	char val2_number = '0';

	//Until �˻�
	bool until_b = false;
	vector<pair<string, vector<string>>>::iterator query_it;
	for(query_it=query_map.begin(); query_it!= query_map.end(); query_it++){
		if(query_it->second[1] == "Until")
			until_b = true;
	}

	//val1����� ���� DB�˻�
	if(until_b && val1=="Date"){
		int until_num = stoi(slot_map.find("Date1")->second);
		set<string> s;
		for(iter=db.begin(); iter!=db.end(); iter++){
			iter2 = iter->second.find("Date");
			int compair_num = stoi(iter2->second);
			if(until_num >= compair_num){
				s.insert(iter2->second);
			}
		}
		for(it_set=s.begin(); it_set!=s.end(); it_set++){
			db_slot1_val.push_back(*it_set);
		}
	} else {
		for(it=slot_map.begin(); it!=slot_map.end(); it++){
			val1_number++;
			it = slot_map.find(val1+val1_number);
			if(it == slot_map.end()) {
				val1_number--;
				break;
			}else {
				db_slot1_val.push_back(it->second);
			}
		}	//val1 ���� ã��
	}


	if(until_b && val2=="Date"){
		int until_num = stoi(slot_map.find("Date1")->second);
		set<string> s;
		for(iter=db.begin(); iter!=db.end(); iter++){
			iter2 = iter->second.find("Date");
			int compair_num = stoi(iter2->second);
			if(until_num >= compair_num){
				s.insert(iter2->second);
			}
		}
		for(it_set=s.begin(); it_set!=s.end(); it_set++){
			db_slot2_val.push_back(*it_set);
		}
	} else {
		for(it=slot_map.begin(); it!=slot_map.end(); it++){
			val2_number++;
			it = slot_map.find(val2+val2_number);
			if(it == slot_map.end()) {
				val2_number--;
				break;
			}else {
				db_slot2_val.push_back(it->second);
			}
		}	//val2 ���� ã��
	}
	
	


	
	for(iter=db.begin(); iter!=db.end(); iter++){

		for(iter2 = iter->second.begin(); iter2!=iter->second.end(); iter2++){

			for(int j=0; j<db_slot1_val.size(); j++){
				if(iter2->second == db_slot1_val[j]){
					db_slot1.push_back(iter->first);
				}
			}
		}
	}
	//db�� val1 üũ


	for(iter=db.begin(); iter!=db.end(); iter++){
		
		for(iter2 = iter->second.begin(); iter2!=iter->second.end(); iter2++){

			for(int j=0; j<db_slot2_val.size(); j++){
				if(iter2->second == db_slot2_val[j]){
					db_slot2.push_back(iter->first);
				}
			}
		}
	}
	//db�� val2 üũ

	set_slot1(db_slot1);
	set_slot2(db_slot1);

	if(db_slot1.size()==0){
		cout << "�������� "+val1+"�� ã�� �� �����ϴ�.("+val1+"�� ���� ������)" << endl;
		return ;
	} else if(db_slot2.size()==0){
		cout << "�������� "+val2+"�� ã�� �� �����ϴ�.("+val1+"�� ���� ������)" << endl;
		return ;
	}
	//db�� ���� �ִ��� Ȯ��


}
void Answer_Function::db_check(vector<int> &db_slot1, vector<int> &answer, string val1, vector<pair<int, map<string, string>>>&db){
	
	vector<pair<int, map<string, string>>>::iterator iter;
	map<string, string>::iterator iter2;
	
	map<string, string>::iterator it;

	set<string>::iterator it_set;

	vector<string> db_slot1_val;

	char val1_number = '0';

	
	//Until �˻�
	bool until_b = false;
	vector<pair<string, vector<string>>>::iterator query_it;
	for(query_it=query_map.begin(); query_it!= query_map.end(); query_it++){
		if(query_it->second[1] == "Until")
			until_b = true;
	}

	//val1����� ���� DB�˻�
	if(until_b && val1=="Date"){
		int until_num = stoi(slot_map.find("Date1")->second);
		set<string> s;
		for(iter=db.begin(); iter!=db.end(); iter++){
			iter2 = iter->second.find("Date");
			int compair_num = stoi(iter2->second);
			if(until_num >= compair_num){
				s.insert(iter2->second);
			}
		}
		for(it_set=s.begin(); it_set!=s.end(); it_set++){
			db_slot1_val.push_back(*it_set);
		}
	} else {
		for(it=slot_map.begin(); it!=slot_map.end(); it++){
			val1_number++;
			it = slot_map.find(val1+val1_number);
			if(it == slot_map.end()) {
				val1_number--;
				break;
			}else {
				db_slot1_val.push_back(it->second);
			}
		}	//val1 ���� ã��
	}


	for(iter=db.begin(); iter!=db.end(); iter++){

		for(iter2 = iter->second.begin(); iter2!=iter->second.end(); iter2++){

			for(int j=0; j<db_slot1_val.size(); j++){
				if(iter2->second == db_slot1_val[j]){
					db_slot1.push_back(iter->first);
				}
			}
		}
	}
	//db�� val1 üũ
	
	set_slot1(db_slot1);

	if(db_slot1.size()==0){
		cout << "�������� "+val1+"�� ã�� �� �����ϴ�.("+val1+"�� ���� ������)" << endl;
		return;
	}
	//db�� ���� �ִ��� Ȯ��

}

void Answer_Function::db_search(vector<int> &db_slot1, vector<pair<int, map<string, string>>> &db, string compare){
	vector<pair<int, map<string,string>>>::iterator db_it;
	map<string, string>::iterator db_it2;
	vector<int>::iterator answer_it;
	

	if(db_slot1.size()>0){		//db_slot1 �� �˻�
		db_it2 = db.at(db_slot1[0]).second.find("Temperature");
		string temp = db_it2->second;
		int temperature = stoi(temp);

		db_slot1.clear();


		if(compare=="�̻�"){
			for(db_it=db.begin(); db_it!=db.end(); db_it++){

				for(db_it2 = db_it->second.begin(); db_it2!=db_it->second.end(); db_it2++){
					if(db_it2->first == "Temperature"){
						if(temperature <= stoi(db_it2->second)){ //������ �µ��� DB�� �µ� ��
							db_slot1.push_back(db_it->first);	//�µ� ���� �� �϶� Input
						} else {
							//�� �� ���� �϶�
						}
					} else {
						//�µ� �׸��� �ƴ� ���
					}
				}
			}

		} else if(compare=="��"){
			for(db_it=db.begin(); db_it!=db.end(); db_it++){

				for(db_it2 = db_it->second.begin(); db_it2!=db_it->second.end(); db_it2++){
					if(db_it2->first == "Temperature"){
						if(temperature < stoi(db_it2->second)){ //������ �µ��� DB�� �µ� ��
							db_slot1.push_back(db_it->first);	//�µ� ���� �� �϶� Input
						} else {
							//�� �� ���� �϶�
						}
					} else {
						//�µ� �׸��� �ƴ� ���
					}
				}
			}
		} else if(compare=="����"){
			for(db_it=db.begin(); db_it!=db.end(); db_it++){

				for(db_it2 = db_it->second.begin(); db_it2!=db_it->second.end(); db_it2++){
					if(db_it2->first == "Temperature"){
						if(temperature >= stoi(db_it2->second)){ //������ �µ��� DB�� �µ� ��
							db_slot1.push_back(db_it->first);	//�µ� ���� �� �϶� Input
						} else {
							//�� �� ���� �϶�
						}
					} else {
						//�µ� �׸��� �ƴ� ���
					}
				}
			}
		} else if(compare=="��"){
			for(db_it=db.begin(); db_it!=db.end(); db_it++){

				for(db_it2 = db_it->second.begin(); db_it2!=db_it->second.end(); db_it2++){
					if(db_it2->first == "Temperature"){
						if(temperature > stoi(db_it2->second)){ //������ �µ��� DB�� �µ� ��
							db_slot1.push_back(db_it->first);	//�µ� ���� �� �϶� Input
						} else {
							//�� �� ���� �϶�
						}
					} else {
						//�µ� �׸��� �ƴ� ���
					}
				}
			}
		}
	} else {
	}
}
void Answer_Function::min_max_search(vector<int> &db_slot1, vector<pair<int, map<string, string>>> &db, string compare){
	vector<pair<int, map<string,string>>>::iterator db_it;
	map<string, string>::iterator db_it2;

	vector<int>::iterator slot1_it;
	vector<int>::iterator slot2_it;
	
	multimap<int, int>::iterator it_map;
	multimap<int, int> temp_map;

	for(slot1_it=db_slot1.begin(); slot1_it!=db_slot1.end(); slot1_it++){
		int index = db.at(*slot1_it).first;
		db_it2 = db.at(*slot1_it).second.find("Temperature");
		int temp = stoi(db_it2->second);
		temp_map.insert(pair<int, int>(temp, index));
	}

	if(db_slot1.size()>0){
		db_slot1.clear();

		if(compare=="��"){
			int max = (--temp_map.end())->first;
			
			for(it_map=temp_map.begin(); it_map!=temp_map.end(); it_map++){
				if(it_map->first == max){
					db_slot1.push_back(it_map->second);
				}
			}

		} else if(compare=="��"){
			int min = temp_map.begin()->first;

			for(it_map=temp_map.begin(); it_map!=temp_map.end(); it_map++){
				if(it_map->first == min){
					db_slot1.push_back(it_map->second);
				}
			}

		}
	} else {
		//db_slot1����� 0�϶�-> ����ó�� �ڷ� �ѱ�
	}
}