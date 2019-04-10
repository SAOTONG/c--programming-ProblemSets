#include<string>
#include<vector>
#include<fstream>
#include<iostream>
#include<regex>
using namespace std;
//------------------------------------------------------------------------------
int main()
{
	string file_name = "my-mail-file.txt";
	ifstream in(file_name.c_str());    // 打开文件
	if (!in) {
		cerr << "no " << file_name << '\n';
		system("pause");
	}
	string s;
	vector<string> senders;
	vector<string> subjects;
	regex sender{ R"(^Subject:([[:print:]]*)$)" };
	regex subject{ R"(^From:([[:print:]]*)$)" };
	while (getline(in, s))
	{
		smatch matches;
		if (regex_match(s, matches, sender))
			senders.push_back(matches[0]);
		else if (regex_match(s, matches, subject))
			subjects.push_back(matches[0]);
	}
	for (string s : senders)
		cout << s << endl;
	cout << "-----------------------------\n";
	for (string s : subjects)
		cout << s << endl;
	system("pause");
	return 0;
}

//------------------------------------------------------------------------------
