#include <iostream>
#include <vector>
using namespace std;

void swap_flowers(int &lhs,int &rhs)
{
	int temp = lhs;
	lhs = rhs;
	rhs = temp;
}

//Flowers:red--1,white--2,blue--3;
void flowers_sort(vector<int> &flowers)
{
	size_t total_num = flowers.size();
	int i = 0, j = total_num - 1, k = j;
	while (i != k)
	{
		if (flowers[k] == 1)
			swap_flowers(flowers[i++], flowers[k]);
		else if (flowers[k] == 3)
		{
			if (k != j)
				swap_flowers(flowers[k], flowers[j]);
			k--; j--;
		}
		else
			k--;
	}
}

int main()
{
	vector<int> flowers;

	//Input color of flowers;
	int n;
	while (cin >> n)
		flowers.push_back(n);

	//Sort flower by color and output the result;
	flowers_sort(flowers);
	for (auto elem : flowers)
		cout << elem << " ";
	cout << endl;

	return 0;
}