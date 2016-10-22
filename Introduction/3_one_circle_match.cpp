/*
 *存储结构:用一个以为数组储存n个元素代表n个选手（元素值依次初始化为0到n-1),一个二维数组储存选手之间的比赛结果;
 *解决方案:快速排序,根据快速排序的原理，将n个选手排成一个队列,则排序完成后任意一个非端点选手左侧1人一定胜于于他，右侧1人一定负于他;
 */

#include <iostream>
#include <vector>
using namespace std;

vector<vector<bool>> grade;//Save competition result between competitors;

//Swaping two elements;
void swap_person(int &lhs, int &rhs)
{
	int temp = lhs;
	lhs = rhs;
	rhs = temp;
}

//Insertion_sort solution;
void insertion_sort(vector<int> &a, int left, int right)
{
	int data_size = right - left + 1;   //To get the size of current sequence;
	for (int p = left + 1,j; p != left + data_size; ++p)
	{
		int temp = a[p];
		for (j = p; j > left && grade[temp][a[j - 1]]; --j)
			a[j] = a[j - 1];
		a[j] = temp;
	}
}

//Sorting the three elements in the left,mid and right position
//and then swap element in the middle with element in the second right position;
const int& median3(vector<int> &a, int left, int right)
{
	//Sorting the three elements;
	int mid = left + (right - left) / 2;
	if (grade[a[mid]][a[left]])
		swap_person(a[mid], a[left]);
	if (grade[a[right]][a[left]])
		swap(a[right], a[left]);
	if (grade[a[right]][a[mid]])
		swap(a[right], a[mid]);

	//Placing pivot at position right-1;
	swap_person(a[mid], a[right - 1]);

	return a[right - 1];
}

//Quick_sort solution with 3 as the cutoff number;
//If the size of the array is smaller than 3,carray out insertion_sort,or else carry out quick_sort;
//After carrying out the quick_sort,all the elements are divided into three parts:
//the pivot element,elements that are smaller than or equal to the pivot element,
//and elements that are greater than or equal to the pivot element,
//then carry out quick_sort for the later two parts recursively;
void quick_sort(vector<int> &a, int left, int right)
{
	if (left + 3 <= right)
	{
		//To get the number of pivot element and sort the three special elements;
		int pivot = median3(a, left, right);

		int i = left, j = right - 1;
		for (;;)
		{
			while (grade[a[++i]][pivot]) {}  //if the current element is greater than pivot element,continue;
			while (grade[pivot][a[--j]]) {}  //if the current element is smaller than pivot element,continue;
			if (i < j)
				swap_person(a[i], a[j]);
			else
				break;
		}
		swap_person(a[i], a[right - 1]);    //Putting the pivot element in the correct position;

		quick_sort(a, left, i - 1);
		quick_sort(a, i + 1, right);
	}
	else
		insertion_sort(a, left, right);
}

//The function for users to call;
void quick_sort(vector<int> &a)
{
	//Check whether if the array is empaty;
	if (a.empty())
		return;
	quick_sort(a, 0, a.size() - 1);
}

int main()
{
	//Enter number of competitors;
	int persons_num;
	cout << "Please enter number of all competitors:";
	cin >> persons_num;

	//Init arrays,1 stands for person 1;
	vector<int> persons(persons_num);
	for (int i = 0; i != persons_num; ++i)
		persons[i] = i;
	grade.resize(persons_num);
	for (auto &arr : grade)
		arr.resize(persons_num);

	//Input result of matches;
	//For example, i and j are two competitors, if i beats j, enter true;,or else enter false;
	bool result;
	for (int i = 0; i != persons_num - 1; ++i)
		for (int j = i + 1; j != persons_num; ++j)
		{
			cout << persons[i] << " & " << persons[j] << " :";
			cin >> result;
			grade[i][j] = result;
			grade[j][i] = !result;
		}

	//Sort competitors and output the result;
	quick_sort(persons);
	for (const auto &num : persons)
		cout << num << " ";
	cout << endl;

	return 0;
}