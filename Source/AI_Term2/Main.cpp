#include "Total.h"

using namespace std;

int main() {
	map<string, vector<string>> sementic_map;
	vector<pair<string, vector<string>>> query_map;	//2�� result
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
		cout << "��ȣ�� �����ϼ���" << endl;
		cout << "-----------------------------------------" << endl;
		cout << "1. ���� �Է�" << endl;
		cout << "2. ���α׷� ����" << endl;
		cout << "-----------------------------------------" << endl << endl;

		cout << "��ȣ�� �Է��ϼ��� : " ;
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

			// �ǹ� ǥ�� ������ �����
			Find_Frame frame;
			frame.finding_Frame(slot_data, query.domain_str, query.is_qna, query.pattern);
			
			// ����ȭ�� �ǹ� ǥ�� ����
			frame.slot_insert(query_map,slot_data, slot_map);
			frame.print_Frame(slot_map);

			// �ڿ��� �����

			Answer_Function af(frame, slot_map,db_map, query_map);

			af.finding_Function();

			pattern_map.clear();
			sementic_map.clear();
			query_map.clear();
			slot_data.clear();
			slot_map.clear();

		} else if(num == 2) {
			cout << "���α׷��� ����Ǿ����ϴ�.\n" << endl;
			return 0;
		} else
			cout << "1���� 2���� �ϳ��� ������" << endl;

	}
}