 /*
  *	存储方案:100个数储存在一个顺序数组中，另外一个数组存储最大值的下标，作为目的数组
  *	解决方案:假设数组首元素最大，用一个变量记录最大值，初始化为数组首元素，并将0 push_back 到目的数组中
  *			 遍历原数组，如果遇到更小的数则跳过，遇到相等的数，则push_back下标，如果遇到更大的数则更新最大值同时push_back下标
  *			 遍历结束后，从目的数组尾部开始，输出元素值，直到遇到一个元素对应的真值不等于最大值或者到达数组头部结束，这些元素即最大值的下标
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