
//
// This is example code from Chapter 23.8.7 "Regular expression errors" of
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//

#include <boost/regex.hpp>
#include <iostream>
#include <string>
#include <fstream>
using namespace std;
using namespace boost;

//------------------------------------------------------------------------------

void wrong_patterns()
{
	regex pat1("(|ghi)");    // missing alternative
	regex pat2("[c-a]");     // not a range
}

//------------------------------------------------------------------------------

// Accept a pattern and a set of lines from input
// Check the pattern and search for lines with that pattern

int main()
{
	regex pattern;

	string pat;
	cout << "����һ��ģʽ: ";
	getline(cin, pat);        // read pattern
	try {
		pattern = pat;       // this checks pat
		cout << "pattern: " << pattern << '\n';
	}
	catch (regex_error) {
		cout << pat << " is not a valid regular expression\n";
		exit(1);
	}

	string file_name;
	cout << "����һ���ļ�����";
	getline(cin, file_name);
	ifstream ifs{ file_name };
	if (!ifs)
	{
		cerr << "�������ļ���" << file_name << endl;
		system("pause");
		exit(1);
	}
	string line;             // input buffer
	int lineno = 0;

	while (getline(ifs, line)) {
		++lineno;
		smatch matches;
		if (regex_search(line, matches, pattern)) {
			cout << "line " << lineno << ": " << line << '\n';
			for (int i = 0; i<matches.size(); ++i)
				cout << "\tmatches[" << i << "]: "
				<< matches[i] << '\n';
		}
		else
			cout << "û���ڸ����ҵ�ƥ����\n";
	}
	system("pause");
	return 0;
}

//------------------------------------------------------------------------------
