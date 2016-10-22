/*
 * 存储方案:
 *		vector<string> 将每一个字符集存入一个string对象中,所有字符集组成一个数组;
 * 解决方案:
 *		第一:对任意两个字符集之间的比较，依次比较对应位置的字符或者数字;
 *			 例如有字符集A和B，在任意一次比较中，如果A的字符小于B，则A小于B，反之类似,否则继续下一位;
 *			 如果某一字符集先到字符串末尾，则先到者为小,如果A、B同时到达字符串末尾，则A、B相等;
 *		第二:根据题意自定义单个字符比较函数和字符集比较函数;
 *		第三:字符集排序，考虑如果字符集数目较多且字符集较大，则在排序过程中赋值操作会浪费很多时间，
 *			 因此程序采用间接排序，类似于利用指针排序，设置一个保存字符集下标的数组，利用下标寻址,对下标数组
 *			 进行排序(此程序采用的是插入排序,如果字符集很多可采用谢尔排序或者快速排序)，然后根据排序结果，将字符集拷贝到正确的位置；
 */


#include <iostream>
#include <vector>
#include <string>
using namespace std;

//Function:Compare two characters -- a < b,return -1; a==b,return 0;a>b,return 1;
//If a is an alphabet and b is a digit,b is greater than a;
int character_comparison(char a,char b)
{
	if (a >= 'A' && b >= 'A' || a <= '9' && b <= '9')
	{
		if (a < b)return -1;
		if (a > b)return 1;
		return 0;
	}
	if (a >= 'A' && b <= '9')
		return -1;
	return 1;
}

//Function:Compare two words A and B by comparing their characters one by one;
//A and B are the two words,if A is smaller than B,return true,or else return false;
//If length of A is shorter than B,A is smaller than B;
bool word_comparison(string &a,string &b)
{
	size_t i = 0;
	while (i < a.length() && i < b.length())
	{
		int ret = character_comparison(a[i], b[i]);
		if (ret == -1)
			return true;
		if (ret == 1)
			return false;
		++i;
	}
	if (i == a.length() && i != b.length())
		return true;
	return false;
}

//Indirect sort in order to decrease times for copying words;
//Resemble sorting a sequence by sorting addresses of elements,sort words by sorting their subscripts here;
void indirect_sort(vector<string> &words)
{
	vector<int> sequence;
	//Init the array which save subscripts of elements;
	size_t data_size = words.size();
	for (int i = 0; i != data_size; ++i)
		sequence.push_back(i);

	//Insertion sort;
	for (int p = 1, j; p != data_size; ++p)
	{
		int temp = sequence[p];
		for (j = p; j > 0 && word_comparison(words[temp], words[sequence[j-1]]); --j)
			sequence[j] = sequence[j - 1];
		sequence[j] = temp;
	}

	//Copy words to their correct position,there might be one or more circles;
	for (int i = 0; i != data_size; ++i)
	{
		if (sequence[i] != i)
		{
			string temp = words[i];
			int j = i, next_j;
			for (; sequence[j] != i; j = next_j)
			{
				next_j = sequence[j];
				words[j] = words[sequence[j]];
				sequence[j] = j;
			}
			words[j] = temp;
			sequence[j] = j;
		}
	}
}

int main()
{
	vector<string> words{"PAB", "5C", "PABC", "CXY", "CRSI", "7", "B899", "B9"};
	indirect_sort(words);
	for (const auto &elem : words)
		cout << elem << " ";
	return 0;
}