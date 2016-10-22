#ifndef SINGLELIST
#define SINGLELIST

#include <iostream>
using namespace std;

template <typename Object> class SingleList
{
	struct Node
	{
		Object data;
		Node *next;
		Node(const Object &obj = Object(), Node *rhs_next = nullptr):data(obj),next(rhs_next){}
	};
public:
	class const_iterator
	{

	};
	class iterator:public const_iterator{};
	void makeEmpty();
	void insert_after(const_iterator &);

private:
	int theSize = 0;
	Node *head;
	Node *tail;
	void init()
	{
		theSize = 0;
		head = new Node;
		tail = new Node;
		head->next = tail;
	}
};
#endif //SINGLELIST