#include <iostream>
#include <vector>
using namespace std;
//����һ��Ԫ��Ϊint�͵�vector�������к�һ��int�Ͳ���Ŀ��ֵ��
//����һ��bool���͵�ֵ���ҵ�Ŀ��ֵ����true��
bool my_binary(const vector<int> &vr, int x);

//number_of_times������¼���ֲ����㷨��ɲ������õĴ�����
int number_of_times = 0;

int main()
{
	vector<int> v{ 1,2,3,4,5,6 };
	if (my_binary(v, 1))
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
			number_of_times++;
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
		number_of_times++;
	}
	return false;
}