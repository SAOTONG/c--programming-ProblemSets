
//
// 这是一个使用二分查找算法查找元素为int型的升序vector中的目标值的实现。
// 以包含多个测试用例的文件作为输入，来进行多次测试。
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
void error_m(string s)
{
	throw runtime_error(s);
}
void error_m(string s1, string s2)
{
	error_m(s1 + s2);
}
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//TODO(1053001374@qq.com)：编写人邮箱。
//TODO(侯金成)：构思并编写这个函数的作者。
//TODO(不完善的二分查找算法)：这个函数是二分查找算法的一个基础实现，待后续完善。
bool my_binary(const vector<int> &vr, int x)
{
	//begin和end指的是元素序列的下标左闭区间和右开区间，
	//例如包含6个元素的vector下标区间为[0,6)，
	//那么begin为0,end为6。
	int end = vr.size();
	int begin = 0;
	//size为当前查找区间的元素数量。
	for (int size = end - begin; size > 0;size = end - begin)
	{
		//当前查找区间的中间元素下标用公式(end - begin - 1) / 2 + begin计算获得。
		int middle = (end - begin - 1) / 2 + begin;
		if (x == vr[middle])
		{
			return true;
		}
		else if (x < vr[middle])
			//当目标值小于当前查找区间的中间值时，
			//改变右开区间，左闭区间不变。
			end = middle;
		else {
			//当目标值大于当前查找区间的中间值时，
			//改变左闭区间，右开区间不变。
			begin = middle + 1;
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
		bool r = my_binary(t.seq, t.val);
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
			error_m("无法打开文件：", file_name);
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

