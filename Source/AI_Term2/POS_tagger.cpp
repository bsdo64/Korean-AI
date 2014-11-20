#include "Total.h"

using namespace std;

void POS_tagger::run() {
	ofstream os;
	os.open("query\\question.txt");		//질문을 저장하는 question.txt를 만듦

	string question = "";
	cin.get();

	cout << "질문을 입력하세요 : ";
	getline(cin, question);

	os << question << endl; 

	if(!os) {
		cerr << "파일 오픈 실패" << endl;
		exit(1);
	}

	system("kma.exe -1sl query\\question.txt > query\\pos.txt");		//형태소 분석을 마친 pos.txt가 query folder 안에 생깁니다.
}