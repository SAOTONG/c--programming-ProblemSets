#include <iostream>
#include <vector>
using namespace std;
//number_of_times用来记录二分查找算法完成查找所用的次数。
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
		cout << "本次共查找了" << number_of_times << "次\n";
		cout << "恭喜你找到了目标值！！\n";
	}
	else
	{
		cout << "本次共查找了" << number_of_times << "次\n";
		cout << "糟糕！！没有找到目标值\n";
	}
	system("pause");
	return 0;
}