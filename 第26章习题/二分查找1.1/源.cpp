#include <iostream>
#include <vector>
using namespace std;
//接收一个元素为int型的vector升序序列和一个int型查找目标值。
//返回一个bool类型的值，找到目标值返回true。
bool my_binary(const vector<int> &vr, int x);

//number_of_times用来记录二分查找算法完成查找所用的次数。
int number_of_times = 0;

int main()
{
	vector<int> v{ 1,2,3,4,5,6 };
	if (my_binary(v, 1))
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
			number_of_times++;
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
		number_of_times++;
	}
	return false;
}