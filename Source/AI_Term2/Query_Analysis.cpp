#include "Total.h"

using namespace std;

string Query_Analysis::analyze(map<string, vector<string>> &m, vector<pair<string, vector<string>>> &q, map<string, string> &pattern_map) {

	pattern.clear();
	is_qna = "";
	domain_str = "";


	string txt;

	set<string> compound_index_set;

	Util ut;
	ut.file_to_set("compound\\Compound_noun_index.txt", compound_index_set);	//복합명사 불러오기
	string ck = ut.file_to_vector("query\\pos.txt", q, m, compound_index_set, domain_str, is_qna, pattern);	//쿼리분석 하기
	compound_index_set.clear();

	if(ck=="err"){
		return "err";
	} else {
		Domain_Analysis DA;
		domain_str = DA.analyze_domain(q);

		Domain_Classification domain;
		domain.pattern_call(pattern_map, domain_str);
		domain.pattern_insert(q, pattern_map, pattern);


		Normalization norm(m);
		norm.test_date(q);
		norm.test_rdate(q);
		norm.test_word(q);

		return "";
	}
}

void Query_Analysis::print(vector<pair<string, vector<string>>> &q) {

	ofstream ofs;
	ofs.open("query\\result.txt");

	if(!ofs) {
		cerr << "파일 오픈 실패" << endl;
		exit(1);
	}

	ofs << " - " << is_qna << " - " << domain_str << " - ";			//domain의 종류, domain의 분류

	set<string>::iterator it_pattern;
	for(it_pattern = pattern.begin(); it_pattern!=pattern.end(); it_pattern++)
		ofs << *it_pattern << " ";									//pattern 분석

	ofs << " - " << endl;

	vector<pair<string, vector<string>>>::iterator it_map;
	vector<string>::iterator it_vec;

	for(it_map = q.begin(); it_map != q.end(); it_map++){

		ofs << (*it_map).first << "\t";

		for(it_vec = (*it_map).second.begin(); it_vec != (*it_map).second.end(); ++it_vec){
			ofs << *it_vec << "\t";
		}
		ofs << endl;
	}

	//pattern.clear();	//패턴을 clear 합니다.

}		// query 폴더 안에 result.txt 라는 file을 생성하여 3차 term에서 엊고자 하는 output을 출력합니다.

string Query_Analysis::get_domain(){	return domain_str;	};

string Query_Analysis::get_is_qna(){	return is_qna;	};

set<string> Query_Analysis::get_pattern(){	return pattern;	};
