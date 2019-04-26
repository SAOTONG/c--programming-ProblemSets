
//
// ����һ��ʹ�ö��ֲ����㷨����Ԫ��Ϊint�͵�����vector�е�Ŀ��ֵ��ʵ�֡�
// �԰�����������������ļ���Ϊ���룬�����ж�β��ԡ�
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
//TODO(1053001374@qq.com)����д�����䡣
//TODO(����)����˼����д������������ߡ�
//TODO(�����ƵĶ��ֲ����㷨)����������Ƕ��ֲ����㷨��һ������ʵ�֣����������ơ�
bool my_binary(const vector<int> &vr, int x)
{
	//begin��endָ����Ԫ�����е��±����������ҿ����䣬
	//�������6��Ԫ�ص�vector�±�����Ϊ[0,6)��
	//��ôbeginΪ0,endΪ6��
	int end = vr.size();
	int begin = 0;
	//sizeΪ��ǰ���������Ԫ��������
	for (int size = end - begin; size > 0;size = end - begin)
	{
		//��ǰ����������м�Ԫ���±��ù�ʽ(end - begin - 1) / 2 + begin�����á�
		int middle = (end - begin - 1) / 2 + begin;
		if (x == vr[middle])
		{
			return true;
		}
		else if (x < vr[middle])
			//��Ŀ��ֵС�ڵ�ǰ����������м�ֵʱ��
			//�ı��ҿ����䣬������䲻�䡣
			end = middle;
		else {
			//��Ŀ��ֵ���ڵ�ǰ����������м�ֵʱ��
			//�ı�������䣬�ҿ����䲻�䡣
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
			error_m("�޷����ļ���", file_name);
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

