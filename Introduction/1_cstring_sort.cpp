/*
 * �洢����:
 *		vector<string> ��ÿһ���ַ�������һ��string������,�����ַ������һ������;
 * �������:
 *		��һ:�����������ַ���֮��ıȽϣ����αȽ϶�Ӧλ�õ��ַ���������;
 *			 �������ַ���A��B��������һ�αȽ��У����A���ַ�С��B����AС��B����֮����,���������һλ;
 *			 ���ĳһ�ַ����ȵ��ַ���ĩβ�����ȵ���ΪС,���A��Bͬʱ�����ַ���ĩβ����A��B���;
 *		�ڶ�:���������Զ��嵥���ַ��ȽϺ������ַ����ȽϺ���;
 *		����:�ַ������򣬿�������ַ�����Ŀ�϶����ַ����ϴ�������������и�ֵ�������˷Ѻܶ�ʱ�䣬
 *			 ��˳�����ü����������������ָ����������һ�������ַ����±�����飬�����±�Ѱַ,���±�����
 *			 ��������(�˳�����õ��ǲ�������,����ַ����ܶ�ɲ���л��������߿�������)��Ȼ����������������ַ�����������ȷ��λ�ã�
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