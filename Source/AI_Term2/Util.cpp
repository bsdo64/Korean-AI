#include "Total.h"

using namespace std;

void Util::file_to_map(string dest, map<string, int> &m) {
	ifstream inf;

	inf.open(dest);				
	if(inf.fail()){
		cout << "������ �������� �ʽ��ϴ�." << endl;
		return;
	}

	while(!inf.eof()){
		string cstr = "";	
		getline(inf, cstr);

		istringstream is(cstr);
		istream_iterator<string> begin(is);
		istream_iterator<string> end;

		string a = *begin; begin++;
		int b = stoi(*begin);
		m.insert(pair<string, int>(a, b));		
	}						
}
void Util::file_to_map(string dest, map<string, string> &m) {
	ifstream inf;

	inf.open(dest);
	if(inf.fail()){
		cout << "������ �������� �ʽ��ϴ�." << endl;
		return;
	}

	while(!inf.eof()){
		string cstr = "";	
		getline(inf, cstr);

		istringstream is(cstr);
		istream_iterator<string> begin(is);
		istream_iterator<string> end;

		string a = *begin; begin++;
		string b = *begin;
		m.insert(pair<string, string>(a, b));		
	}						
}
void Util::file_to_map(string dest, string domain, map<string, vector<string>> &m) {
	ifstream inf;

	inf.open(dest);
	if(inf.fail()){
		cout << "������ �������� �ʽ��ϴ�." << endl;
		return;
	}

	while(!inf.eof()){
		vector<string> pos_sementic;
		string line = "";
		getline(inf, line);

		istringstream is(line);
		istream_iterator<string> begin(is);
		istream_iterator<string> end;

		string word = *begin; begin++;

		pos_sementic.push_back(*begin);
		pos_sementic.push_back(domain);

		m.insert(pair<string, vector<string>>(word, pos_sementic));			//�������� ������ word�� pos_sementic���� pair�� �����մϴ�.
	}
}

void Util::file_to_map(string dest, map<set<string>, string> &m){
	ifstream inf;

	inf.open(dest);
	if(inf.fail()){
		cout << "������ �������� �ʽ��ϴ�. " << endl;
		return;
	}

	while(!inf.eof()){
		set<string> s1;
		string line = "";
		getline(inf, line);

		istringstream is(line);
		istream_iterator<string> begin(is);
		istream_iterator<string> end;

		while(*begin != "|"){
			s1.insert(*begin);
			begin++;
		}
		begin++;
		string file_name = *begin;
		m.insert(pair<set<string>, string>(s1, file_name));			//�������� ������ word�� pos_sementic���� pair�� �����մϴ�.
	}
}

int word_num(string line2, string tok){
	//���ڿ� \t���� ����
	char* context = NULL;
	char* token = strtok_s(&line2[0], &tok[0], &context);
	int tok_num = 0;

	while(token){
		tok_num++;
		token = strtok_s(NULL, &tok[0], &context);
	}
	return tok_num;
}
void Util::file_to_vector(string dest, vector<pair<int, map<string, string>>> &v){
	ifstream inf;

	inf.open(dest);
	if(inf.fail()){
		cout << "������ �������� �ʽ��ϴ�." << endl;
		return;
	}
	int i=0;

	while(!inf.eof()){

		map<string, string> m1;
		
		string line = "";
		getline(inf, line);
		string line2 = line;

		istringstream is(line);
		istream_iterator<string> begin(is);
		istream_iterator<string> end;

		int tok_num = 0;
		tok_num = word_num(line2, "\t");

		string word1 = *begin; begin++;
		string word2 = *begin; begin++;
		string word3 = *begin; begin++;
		string word4 = *begin; begin++;
		string word5 = *begin; begin++;
		string word6 = *begin; begin++;
		string word7 = *begin; begin++;
		string word8 = *begin;

		if(tok_num==6){
			m1.insert(pair<string, string>(word1, word2));
			m1.insert(pair<string, string>(word3, word4));
			m1.insert(pair<string, string>(word5, word6));
		} else if(tok_num==8){
			m1.insert(pair<string, string>(word1, word2));
			m1.insert(pair<string, string>(word3, word4));
			m1.insert(pair<string, string>(word5, word6));		
			m1.insert(pair<string, string>(word7, word8));
		}

		v.push_back(pair<int, map<string, string>>(i,m1));
		i++;
	}
}


void Util::file_to_map(string dest, map<string, vector<string>> &m){
	ifstream inf;

	inf.open(dest);
	if(inf.fail()){
		cout << "������ �������� �ʽ��ϴ�." << endl;
		return;
	}

	while(!inf.eof()){
		vector<string> pos_sementic;
		string line = "";
		getline(inf, line);

		istringstream is(line);
		istream_iterator<string> begin(is);
		istream_iterator<string> end;

		string word = *begin; begin++;
		string star = *begin;

		if(*begin==word)
			star = "";

		pos_sementic.push_back(word);
		pos_sementic.push_back(star);

		m.insert(pair<string, vector<string>>(word, pos_sementic));			//�������� ������ word�� pos_sementic���� pair�� �����մϴ�.
	}
}
string Util::file_to_vector(string dest, vector<pair<string, vector<string>>> &q, map<string, vector<string>> &m, set<string> &s, string &domain_str, string &is_qna, set<string> &pattern) {
	
	map<string, vector<string>>::iterator find_sementic;
	map<string, vector<string>>::iterator find_pattern;

	string txt;

	ifstream inf;

	inf.open(dest);			//���¼� �м��� ��� txt file�� �о�´�.
	if(inf.fail()){
		cout << "������ �������� �ʽ��ϴ�." << endl;
		return "err";
	}

	while(!inf.eof()){

		getline(inf, txt);
		getline(inf, txt);

		istringstream is(txt);
		string token;		//token = ����
		string token2;		//token2 = word
		string token3 ="";		//token3 = domain

		string token4 = "";	//token4 = ���ո��
		int num =0;

		for(int i=0; i < txt.length(); i++){
			if(txt.at(i) == '('){
				for(int j = i; j <txt.length(); j++){
					if(txt.at(j) == ')') {
						token2 = txt.substr(i+4, j-i-5);		//()���� �ܾ �ڸ��� ���� ���

						if(s.find(token2) != s.end()){ //���ո�� �˻� if��
							num++;
						}
						if(num>0) {
							token4 += token2;		//���� ��縦 ������ֱ� ���� string concatenation
							if(m.find(token4) != m.end()){

								find_sementic = m.find(token4);
								if(find_sementic==m.end()){
									cout << "�����ͺ��̽��� ���� ���� �Դϴ�.(�ܾ� : " << token4 << ")" << endl;
									cout << "������ �ٽ� �Է����ּ���" << endl;
									return "err";
								}
								token = (*find_sementic).second[0];
								token3 = (*find_sementic).second[1];

								vector<string> v;
								v.push_back(token);
								v.push_back(token3);

								if((*find_sementic).first == "?"){
									is_qna = "Q\&A";
								} 
								else {
									is_qna = "Command";
								}

								q.push_back(pair<string, vector<string>>(token4, v));
								num = 0;
							}

						}
						else if (m.find(token2) != m.end()) {		//���ո�簡 �ƴҰ��
							find_sementic = m.find(token2);	
							
							token = (*find_sementic).second[0];
							token3 = (*find_sementic).second[1];

							vector<string> v;
							v.push_back(token);
							v.push_back(token3);

							if((*find_sementic).first == "?"){
								is_qna = "Q\&A";
							}
							else {
								is_qna = "Command";
							}

							q.push_back(pair<string, vector<string>>(token2, v));	//�� �������� ���� �Ǵ� ������ word, pos_tag, type �� �˴ϴ�
						} else if(m.find(token2) == m.end()) {
								cout << "�����ͺ��̽��� ���� ���� �Դϴ�.(�ܾ� : " << token2 << ")" << endl;
								cout << "������ �ٽ� �Է����ּ���" << endl<<endl;
								return "err";
						}
						break;
					}
				}
			}
		}

	}
	return "";
}
void Util::file_to_vector(string dest, vector<string> &v){
	ifstream ifs;

	ifs.open(dest);		//���ո�縦 �������ֱ� ���� ù�ܾ� index ����
	if(ifs.fail()){
		cout << "������ �������� �ʽ��ϴ�." << endl;
		return;
	}

	while(!ifs.eof()){
		string cstr = "";	//compound_index �˻�
		getline(ifs, cstr);
		string cstr2 = cstr;

		istringstream is(cstr);
		istream_iterator<string> begin(is);
		
		int tok_num = 0;
		tok_num = word_num(cstr2, " ");
		
		for(int i=0; i<tok_num; i++){
			v.push_back(*begin);
			begin++;
		}
	}
}
void Util::file_to_set(string dest, set<string> &s){
	ifstream ifs;

	ifs.open(dest);		//���ո�縦 �������ֱ� ���� ù�ܾ� index ����
	if(ifs.fail()){
		cout << "������ �������� �ʽ��ϴ�." << endl;
		return;
	}

	while(!ifs.eof()){
		string cstr = "";	//compound_index �˻�

		getline(ifs, cstr);

		istringstream is(cstr);
		istream_iterator<string> begin(is);
		istream_iterator<string> end;

		s.insert(*begin);
	}
}