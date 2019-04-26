#include <iostream>
#include <vector>
using namespace std;
//number_of_times������¼���ֲ����㷨��ɲ������õĴ�����
int number_of_times = 0;

template <typename ForwardIterator,typename T>
bool my_binary(ForwardIterator first, ForwardIterator last, const T& value)
{
	for (int size = last - first; size > 0; size = last - first)
	{
		auto middle = (last - first - 1) / 2 + first;
		if (value == *middle)
		{
			number_of_times++;
			return true;
		}
		else if (value < *middle)
			last = middle;
		else {
			first = middle + 1;
		}
		number_of_times++;
	}
	return false;
}

int main()
{
	vector<double> v{ 1.1,2.2,3.0,4.0,5.0,6.1 };
	if (my_binary(v.begin(),v.end(), 6.1))
	{
		cout << "���ι�������" << number_of_times << "��\n";
		cout << "��ϲ���ҵ���Ŀ��ֵ����\n";
	}
	else
	{
		cout << "���ι�������" << number_of_times << "��\n";
		cout << "��⣡��û���ҵ�Ŀ��ֵ\n";
	}
	system("pause");
	return 0;
}