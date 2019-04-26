
//
// 这个程序是在测试二分查找1.1基础上做了修改，
// 把其中的二分查找1.1算法修改成了二分查找1.2算法。
// 测试方法：以包含多个测试用例的文件作为输入，来进行多次测试。
//

#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>
#include <fstream>
using namespace std;
//------------------------------------------------------------------------------

struct Test {
	string label;
	int val;
	vector<int> seq;
	bool res;
};

//------------------------------------------------------------------------------

istream& operator>>(istream& is, Test& t) // use the described format
{
	// Example input: { 27 7 { 1 2 3 5 8 13 21} 0 }
	string a, b;

	if (is >> a >> t.label >> t.val >> b && (a != "{" || b != "{"))
	{
		std::cerr << "ERROR: Invalid test file format" << std::endl;
		return is;
	}

	t.seq.clear();
	std::copy(
		std::istream_iterator<int>(is),
		std::istream_iterator<int>(),
		std::back_inserter(t.seq)
	);

	is.clear();

	string c, d;
	int res = 0;

	if (is >> c >> res >> d && (c != "}" || d != "}"))
	{
		std::cerr << "ERROR: Invalid test file format" << std::endl;
		return is;
	}

	t.res = res;
	return is;
}

//------------------------------------------------------------------------------

ostream& operator<<(ostream& os, const Test& t)
{
	os << "{ " << t.label << ' ' << t.val << " { ";
	std::copy(t.seq.begin(), t.seq.end(), std::ostream_iterator<int>(os, " "));
	return os << "} " << t.res << " }";
}

//------------------------------------------------------------------------------

void error(string s)
{
	throw runtime_error(s);
}
void error(string s1, string s2)
{
	error(s1 + s2);
}

//------------------------------------------------------------------------------

template <typename ForwardIterator, typename T>
bool my_binary(ForwardIterator first, ForwardIterator last, const T& value)
{
	for (int size = last - first; size > 0; size = last - first)
	{
		auto middle = (last - first - 1) / 2 + first;
		if (value == *middle)
		{
			return true;
		}
		else if (value < *middle)
			last = middle;
		else {
			first = middle + 1;
		}
	}
	return false;
}
//------------------------------------------------------------------------------

int test_all(istream& is)
{
	int error_count = 0;
	Test t;

	while (is >> t) {
		cout << t << endl;
		bool r = my_binary(t.seq.begin(),t.seq.end(), t.val);
		if (r != t.res) {
			cout << "failure: test " << t.label
				<< " my_binary: "
				<< t.seq.size() << " elements, v==" << t.val
				<< " -> " << t.res << '\n';
			++error_count;
		}
	}
	return error_count;
}

//------------------------------------------------------------------------------


int main()
{
	try
	{
		string file_name = "my_test.txt";
		ifstream ifs{ file_name };
		if (!ifs)
		{
			error("无法打开文件：", file_name);
		}
		int errors = test_all(ifs);
		cout << "number of errors: " << errors << "\n";
		system("pause");
		return 0;
	}
	catch (const std::exception&e)
	{
		cerr << e.what() << endl;
		system("pause");
		return 1;
	}

}

//------------------------------------------------------------------------------

