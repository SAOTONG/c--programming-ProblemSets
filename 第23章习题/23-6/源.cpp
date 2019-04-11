#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<regex>
using namespace std;
int main()
{
	string file_name = "file.txt";
	ifstream ifs{ file_name };
	if (!ifs)
	{
		cerr << "�������ļ���" << file_name << endl;
		system("pause");
		exit(1);
	}
	string data_pat = R"([1-9][1-2]?/[1-9]\d?/[1-9]\d{3})";
	regex data;
	try
	{
		data = data_pat;
	}
	catch (regex_error)
	{
		cerr << data_pat << "��һ�������ģʽ!!!\n";
		system("pause");
		return 0;
	}
	int line_num = 0;
	smatch matches;
	for (string line; getline(ifs, line);)
	{
		line_num++;
		if (regex_search(line, matches, data))
		{
			cout << "ƥ�������Ϊ��" << matches[0] << endl;
			cout << line_num << ":" << line << endl;
			cout << "-------------------------------\n";
		}
	}
	system("pause");
	return 0;
}