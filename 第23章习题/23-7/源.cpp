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
		cerr << "不存在文件：" << file_name << endl;
		system("pause");
		exit(1);
	}
	string pat_str = R"([645]\d{15})";
	regex pat;
	try
	{
		pat = pat_str;
	}
	catch (regex_error)
	{
		cerr << pat_str << "是一个错误的模式!!!\n";
		system("pause");
		return 0;
	}
	int line_num = 0;
	smatch matches;
	for (string line; getline(ifs, line);)
	{
		line_num++;
		if (regex_search(line, matches, pat))
		{
			cout << "匹配的内容为：" << matches[0] << endl;
			cout << line_num << ":" << line << endl;
			cout << "-------------------------------\n";
		}
	}
	system("pause");
	return 0;
}