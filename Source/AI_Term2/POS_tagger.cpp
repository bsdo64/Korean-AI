#include "Total.h"

using namespace std;

void POS_tagger::run() {
	ofstream os;
	os.open("query\\question.txt");		//������ �����ϴ� question.txt�� ����

	string question = "";
	cin.get();

	cout << "������ �Է��ϼ��� : ";
	getline(cin, question);

	os << question << endl; 

	if(!os) {
		cerr << "���� ���� ����" << endl;
		exit(1);
	}

	system("kma.exe -1sl query\\question.txt > query\\pos.txt");		//���¼� �м��� ��ģ pos.txt�� query folder �ȿ� ����ϴ�.
}