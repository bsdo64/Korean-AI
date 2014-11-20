#include "Total.h"

using namespace std;

void Normalization::test_date(vector<pair<string, vector<string>>> &q) {
	
	string year[3] = {"2012��", "2013��", "2014��"};
	string month[12] = {"1��", "2��", "3��", "4��", "5��", "6��", "7��", "8��", "9��", "10��", "11��", "12��"};
	string day[31] = {"1��", "2��", "3��", "4��", "5��", "6��", "7��", "8��", "9��", "10��",
						"11��", "12��", "13��", "14��", "15��", "16��", "17��", "18��", "19��", "20��",
						"21��", "22��", "23��", "24��", "25��", "26��", "27��", "28��", "29��", "30��", "31��"};

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
			if(y == 0) {						//������ ������ �Էµ��� ���� ���
				it = q.erase(it); it--;
				it = q.erase(it);				//ex)10�� 17�� �̶�� �Էµ� ��� 10��, 17�� �� ���� iterator�� ����

				y=today.tm_year+1900;
				y=y*10000;
				m=m*100;

				int date = y+m+d;				//20131017 �� ���� ���·� ��Ÿ���� ����

				vector<string> v;
				v.push_back("n");
				v.push_back("Date");
				v.push_back("");

				stringstream ss;
				ss << date;
				
				q.insert(it, 1, pair<string, vector<string>>(ss.str(), v));		//iterator�� �߰������μ� 20131017�� ���� ���°� �߰���

				break;
			}
			else {
				it = q.erase(it); it--;				// ������ �Էµ� ���	
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

			string changed_word;//�� ������ ���
			changed_word = itm->second;

			it = q.erase(it);

			map<string, vector<string>>::iterator it2;

			it2 = s_map.find(itm->first);
			
			vector<string> v;
			v.push_back(it2->second[0]);
			v.push_back(it2->second[1]);
			v.push_back("");


			q.insert(it, 1, pair<string, vector<string>>(itm->second, v));
			// �ܾ� ��ȯ

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

			d = today.tm_mday;						//�� ������ ���
			rdate_num = itm->second;

			it++;

			if(it->second[1] == "After"){
				d += rdate_num;						//'��, ��' ��� �ܾ ������ִ� ��� 
			} else if(it->second[1] == "Before"){
				d -= rdate_num;						//'��, ��' ��� �ܾ ������ִ� ��� 
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
			
			d = today.tm_mday;					//������ �� ���� ���
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
			// ��¥ ��ȯ

			it = q.begin();
		} 
		else if((itm = rdate3.find(it->first)) != rdate3.end()){
			
			d = today.tm_mday;							//~���� �� ���� ������ �Էµ� ���
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