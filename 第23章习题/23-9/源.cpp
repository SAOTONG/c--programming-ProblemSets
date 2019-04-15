
//
// This is example code from Chapter 23.9 "Matching with regular expression" of
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//

#include "std_lib_facilities.h"
//------------------------------------------------------------------------------

struct bad_from_string : std::bad_cast
	// class for reporting string cast errors
{
	const char* what() const throw() // override bad_cast's what()
	{
		return "bad cast from string";
	}
};

//------------------------------------------------------------------------------

template<class T> T from_string(const string& s)
{
	istringstream is(s);
	T t;
	if (!(is >> t)) throw bad_from_string();
	return t;
}

//------------------------------------------------------------------------------

int main()
try
{
	ifstream in("table.txt");    // input file
	if (!in) error("no input file");

	string line;            // input buffer
	int lineno = 0;
	regex row;

	string pat;
	cout << "输入一个模式: ";
    getline(cin, pat);        // read pattern
	try {
		row = pat;       // this checks pat
		cout << "pattern: " << row << '\n';
	}
	catch (regex_error) {
		cout << pat << " is not a valid regular expression\n";
		exit(1);
	}
	
	regex header(R"(^[\w ]+(	[\w ]+)*$)");
	/*regex row;
	string row_str = "^[\w ]+(	\d+)(	\d+)(	\d+)$";
	row = row_str;
	^[\w] + (\d + )(\d + )(\d + )$*/
	if (getline(in, line)) {        // check header line
		boost::smatch matches;
		if (!boost::regex_search(line, matches, header)) {
			error("no header");
		}
	}

	// column totals:
	int boys = 0;
	int girls = 0;

	// current line values:
	int curr_boy = 0;
	int curr_girl = 0;

	while (getline(in, line)) {    // extract and check data
		++lineno;
		smatch matches;
		if (!regex_search(line, matches, row))
			error("bad line", lineno);

		// check row:
		curr_boy = from_string<int>(matches[1]);
		curr_girl = from_string<int>(matches[2]);
		int curr_total = from_string<int>(matches[3]);
		if (curr_boy + curr_girl != curr_total) error("bad row sum");

		boys += curr_boy;
		girls += curr_girl;
	}

	// check columns:
	if (2 * curr_boy != boys)  error("boys don't add up");
	if (2 * curr_girl != girls) error("girls don't add up");
	system("pause");
	return 0;
}
catch (std::exception& e) {
	cerr << "error: " << e.what() << '\n';
	system("pause");
	return 1;
}
catch (...) {
	cerr << "Oops: unknown exception!\n";
	system("pause");
	return 2;
}

//------------------------------------------------------------------------------
