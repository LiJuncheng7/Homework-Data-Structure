 /*
  *	�洢����:100����������һ��˳�������У�����һ������洢���ֵ���±꣬��ΪĿ������
  *	�������:����������Ԫ�������һ��������¼���ֵ����ʼ��Ϊ������Ԫ�أ�����0 push_back ��Ŀ��������
  *			 ����ԭ���飬���������С������������������ȵ�������push_back�±꣬����������������������ֵͬʱpush_back�±�
  *			 ���������󣬴�Ŀ������β����ʼ�����Ԫ��ֵ��ֱ������һ��Ԫ�ض�Ӧ����ֵ���������ֵ���ߵ�������ͷ����������ЩԪ�ؼ����ֵ���±�
  */

#include <iostream>
#include <vector>
using namespace std;

int main()
{
	vector<int> position;
	vector<int> number;

	//Read data;
	int elem;
	while (number.size() != 100)
		if (cin >> elem)
			number.push_back(elem);

	//To find the maximum numbers and their positions;
	int maximum = number[0];
	for (int i = 0; i != 100; ++i)
	{
		if (number[i] >= maximum)
		{
			if (number[i] > maximum)
				maximum = number[i];
			position.push_back(i);
		}
	}

	//Output the result;
	cout << "maximum number is " << maximum << "\nPosition of them: ";
	for (auto iter = --position.cend(); number[*iter] == maximum; --iter)
	{
		cout << *iter << " ";
		if (iter == position.cbegin())break;
	}

	return 0;
}