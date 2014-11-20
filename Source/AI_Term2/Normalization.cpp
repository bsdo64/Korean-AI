#include "Total.h"

using namespace std;

void Normalization::test_date(vector<pair<string, vector<string>>> &q) {
	
	string year[3] = {"2012년", "2013년", "2014년"};
	string month[12] = {"1월", "2월", "3월", "4월", "5월", "6월", "7월", "8월", "9월", "10월", "11월", "12월"};
	string day[31] = {"1일", "2일", "3일", "4일", "5일", "6일", "7일", "8일", "9일", "10일",
						"11일", "12일", "13일", "14일", "15일", "16일", "17일", "18일", "19일", "20일",
						"21일", "22일", "23일", "24일", "25일", "26일", "27일", "28일", "29일", "30일", "31일"};

	time_t timer;
	struct tm today;

	timer = time(NULL);
	localtime_s(&today, &timer);

	int y=0, m=0, d=0;

	vector<pair<string, vector<string>>>::iterator it;

	for(it=q.begin(); it != q.end(); it++) {
		for(int i=0; i<sizeof(month)/sizeof(month[0]); i++) {
			if(it->first == month[i]) 
				m=(i+1);
		}
		for(int i=0; i<sizeof(year)/sizeof(year[0]); i++) {
			if(it->first == year[i])
				y=(i+2012);
		}
		for(int i=0; i<sizeof(day)/sizeof(day[0]); i++) {
			if(it->first == day[i])
				d=(i+1);
		}
		if(m != 0 && d != 0) {
			if(y == 0) {						//질문에 연도가 입력되지 않은 경우
				it = q.erase(it); it--;
				it = q.erase(it);				//ex)10월 17일 이라고 입력된 경우 10월, 17일 두 개의 iterator를 삭제

				y=today.tm_year+1900;
				y=y*10000;
				m=m*100;

				int date = y+m+d;				//20131017 과 같은 형태로 나타내기 위함

				vector<string> v;
				v.push_back("n");
				v.push_back("Date");
				v.push_back("");

				stringstream ss;
				ss << date;
				
				q.insert(it, 1, pair<string, vector<string>>(ss.str(), v));		//iterator를 추가함으로서 20131017과 같은 형태가 추가됨

				break;
			}
			else {
				it = q.erase(it); it--;				// 연도가 입력된 경우	
				it = q.erase(it); it--;
				it = q.erase(it);

				y=y*10000;
				m=m*100;

				int date = y+m+d;

				vector<string> v;
				v.push_back("n");
				v.push_back("Date");
				v.push_back("");
				
				stringstream ss;
				ss << date;
				
				q.insert(it, 1, pair<string, vector<string>>(ss.str(), v));

				break;
			}
		}
	}
}
void Normalization::test_word(vector<pair<string, vector<string>>> &q) {

	map<string, string> word;

	Util ut;
	ut.file_to_map("normalization\\Word.txt", word);

	vector<pair<string, vector<string>>>::iterator it=q.begin();
	map<string, string>::iterator itm;

	for(; it != q.end(); ++it) {

		if((itm = word.find(it->first)) != word.end()){

			string changed_word;//한 어절인 경우
			changed_word = itm->second;

			it = q.erase(it);

			map<string, vector<string>>::iterator it2;

			it2 = s_map.find(itm->first);
			
			vector<string> v;
			v.push_back(it2->second[0]);
			v.push_back(it2->second[1]);
			v.push_back("");


			q.insert(it, 1, pair<string, vector<string>>(itm->second, v));
			// 단어 변환

			it = q.begin();
		}
	}
}
void Normalization::test_rdate(vector<pair<string, vector<string>>> &q) {

	map<string, int> rdate;
	map<string, int> rdate2;
	map<string, int> rdate3;

	Util ut;
	ut.file_to_map("normalization\\Rdate.txt", rdate);
	ut.file_to_map("normalization\\Rdate2.txt", rdate2);
	ut.file_to_map("normalization\\Rdate3.txt", rdate3);

	time_t timer;
	struct tm today;

	timer = time(NULL);
	localtime_s(&today, &timer);

	int y=0, m=0, d=0;
	int rdate_num=0;
	int op_test=0;

	vector<pair<string, vector<string>>>::iterator it=q.begin();
	map<string, int>::iterator itm;

	for(; it != q.end(); ++it) {

		if((itm = rdate.find(it->first)) != rdate.end()){

			d = today.tm_mday;						//두 어절인 경우
			rdate_num = itm->second;

			it++;

			if(it->second[1] == "After"){
				d += rdate_num;						//'뒤, 후' 라는 단어를 계산해주는 장소 
			} else if(it->second[1] == "Before"){
				d -= rdate_num;						//'전, 앞' 라는 단어를 계산해주는 장소 
			}

			it = q.erase(it); it--;
			it = q.erase(it); 

			y=today.tm_year+1900;
			y=y*10000;
			m=today.tm_mon+1;
			m=m*100;

			int date = y+m+d;

			vector<string> v;
			v.push_back("n");
			v.push_back("Date");
			v.push_back("");

			stringstream ss;
			ss << date;

			q.insert(it, 1, pair<string, vector<string>>(ss.str(), v));
			it = q.begin();

		} 
		else if((itm = rdate2.find(it->first)) != rdate2.end()){
			
			d = today.tm_mday;					//어절이 한 개인 경우
			rdate_num = itm->second;
			d += rdate_num;

			it = q.erase(it);
			

			y=today.tm_year+1900;
			y=y*10000;
			m=today.tm_mon+1;
			m=m*100;

			int date = y+m+d;

			vector<string> v;
			v.push_back("n");
			v.push_back("Date");
			v.push_back("");

			stringstream ss;
			ss << date;

			q.insert(it, 1, pair<string, vector<string>>(ss.str(), v));
			// 날짜 변환

			it = q.begin();
		} 
		else if((itm = rdate3.find(it->first)) != rdate3.end()){
			
			d = today.tm_mday;							//~까지 와 같이 질문이 입력된 경우
			rdate_num = itm->second;
			d += rdate_num;

			it = q.erase(it);

			y=today.tm_year+1900;
			y=y*10000;
			m=today.tm_mon+1;
			m=m*100;

			int date = y+m+d;

			vector<string> v;
			v.push_back("n");
			v.push_back("Until");
			v.push_back("");

			stringstream ss;
			ss << date;

			q.insert(it, 1, pair<string, vector<string>>(ss.str(), v));
			it = q.begin()+1;
		} else {
			continue;
		}
	}
}