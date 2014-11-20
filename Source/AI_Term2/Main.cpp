#include "Total.h"

using namespace std;

int main() {
	map<string, vector<string>> sementic_map;
	vector<pair<string, vector<string>>> query_map;	//2차 result
	map<string, string> pattern_map;
	map<string, vector<string>> slot_data;
	map<string, string> slot_map;
	map<string, string> answer_map;

	map<string, vector<pair<int, map<string, string>>>> db_map;
	Database db;
	db.call_DB(db_map);

	int num = 0;

	while(num != 2) {
		cout << "-----------------------------------------" << endl;
		cout << "번호를 선택하세요" << endl;
		cout << "-----------------------------------------" << endl;
		cout << "1. 문장 입력" << endl;
		cout << "2. 프로그램 종료" << endl;
		cout << "-----------------------------------------" << endl << endl;

		cout << "번호를 입력하세요 : " ;
		cin >> num;

		if(num == 1) {

			POS_tagger pos;
			pos.run();

			Sementic_Database DB;
			DB.run(sementic_map);

			Query_Analysis query;
			string ck = query.analyze(sementic_map, query_map, pattern_map);

			if(ck == "err")
				continue;

			query.print(query_map);

			// 의미 표현 프레임 만들기
			Find_Frame frame;
			frame.finding_Frame(slot_data, query.domain_str, query.is_qna, query.pattern);
			
			// 정규화된 의미 표현 형식
			frame.slot_insert(query_map,slot_data, slot_map);
			frame.print_Frame(slot_map);

			// 자연어 응답기

			Answer_Function af(frame, slot_map,db_map, query_map);

			af.finding_Function();

			pattern_map.clear();
			sementic_map.clear();
			query_map.clear();
			slot_data.clear();
			slot_map.clear();

		} else if(num == 2) {
			cout << "프로그램이 종료되었습니다.\n" << endl;
			return 0;
		} else
			cout << "1번과 2번중 하나를 고르세요" << endl;

	}
}