#include<string>
#include<vector>
#include<fstream>
#include<iostream>
#include<regex>
using namespace std;

int main()
{
	string file_name = "my-mail-file.txt";
	ifstream in(file_name.c_str());    // 打开文件
	if (!in) {
		cerr << "no " << file_name << '\n';
		system("pause");
	}
	vector<string> senders;
	vector<string> subjects;
	regex sender;
	regex subject;
	string sub = R"(^Subject:([[:print:]]*)$)";
	string send = R"(^From:([[:print:]]*)$)";
	try
	{
		sender = send;
	}
	catch (std::regex_error)
	{
		cerr << send << "是一个错误格式的模式!!!\n";
		system("pause");
		exit(1);
	}
	try
	{
		subject = sub;
	}
	catch (std::regex_error)
	{
		cerr << sub << "是一个错误格式的模式!!!\n";
		system("pause");
		exit(1);
	}
	
	for (string s; getline(in, s);)
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
