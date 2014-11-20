#include "Total.h"

using namespace std;

void Sementic_Database::run(map<string, vector<string>> &m) {
	string domain_file[] = {"Min_max", "Action", "After", "Before", "Call", "Compare", "Conjunction", "Count", "Etc", 
		"Location", "From", "Message", "Name", "Obj", "Phone_number", "City", "Add", "Delete", "All",
		"Phone_type", "Send", "Temperature", "Time", "To", "Weather", "Month", "Day", "Year", "Until"};			//개체명 인식기 사전 구축 완료 된 파일들을 domain_file이라는 array에 저장합니다

	for(int i=0; i< (sizeof(domain_file)/sizeof(domain_file[0])) ; i++){
		
		string s1 = "dic\\";
		
		Util ut;
		ut.file_to_map(s1 + domain_file[i]+".txt", domain_file[i], m);

	}
}