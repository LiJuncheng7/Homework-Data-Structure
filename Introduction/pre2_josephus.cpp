#include <iostream>
#include <vector>
#include <list>
using namespace std;

void josephus(vector<int> &out_queue, int total_num, int transmit_dist)
{
	//Init the array;
	list<int> arr(total_num);
	int i = 0;
	for (auto &n : arr)
		n = ++i;
	
	auto current = arr.begin();
	while (!arr.empty())
	{
		//After M times delivery£¬the person who owns the potato leaves the circle;
		int rest_dist = transmit_dist;
		while (rest_dist--)
		{
			if (current != --arr.end())
				++current;
			else
				current = arr.begin();
		}
		out_queue.push_back(*current);
		//The next adjacent person pick up the potato,and game continues;
		current = arr.erase(current);
		if (current == arr.end())
			current = arr.begin();
	}
}
int main()
{
	int people_num;
	int transmit_dist;
	cout << "Please input number of all people and the transmit distance:";
	cin >> people_num >> transmit_dist;

	list<int> arr(people_num);
	vector<int> out_queue;
	josephus(out_queue, people_num, transmit_dist);
	for (auto n : out_queue)
		cout << n << " ";
	cout << endl;

	return 0;
}