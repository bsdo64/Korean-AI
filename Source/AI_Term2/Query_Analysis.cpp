#include "Total.h"

using namespace std;

string Query_Analysis::analyze(map<string, vector<string>> &m, vector<pair<string, vector<string>>> &q, map<string, string> &pattern_map) {

	pattern.clear();
	is_qna = "";
	domain_str = "";


	string txt;

	set<string> compound_index_set;

	Util ut;
	ut.file_to_set("compound\\Compound_noun_index.txt", compound_index_set);	//���ո�� �ҷ�����
	string ck = ut.file_to_vector("query\\pos.txt", q, m, compound_index_set, domain_str, is_qna, pattern);	//�����м� �ϱ�
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
		cerr << "���� ���� ����" << endl;
		exit(1);
	}

	ofs << " - " << is_qna << " - " << domain_str << " - ";			//domain�� ����, domain�� �з�

	set<string>::iterator it_pattern;
	for(it_pattern = pattern.begin(); it_pattern!=pattern.end(); it_pattern++)
		ofs << *it_pattern << " ";									//pattern �м�

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

	//pattern.clear();	//������ clear �մϴ�.

}		// query ���� �ȿ� result.txt ��� file�� �����Ͽ� 3�� term���� ������ �ϴ� output�� ����մϴ�.

string Query_Analysis::get_domain(){	return domain_str;	};

string Query_Analysis::get_is_qna(){	return is_qna;	};

set<string> Query_Analysis::get_pattern(){	return pattern;	};
