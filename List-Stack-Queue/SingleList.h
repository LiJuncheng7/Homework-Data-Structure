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
	public:
		const_iterator() :current(nullptr), theList(nullptr) {}   //Users are allowed to build an empty const_iterator;
		const_iterator(const const_iterator &rhs) :current(rhs.current), theList(rhs.theList) {}  //Copy constructor;

		//Overloaded operators;
		const Object& operator*()const { return current->data; }
		const_iterator& operator++()//prefix version;
		{ 
			current = current->next; 
			return *this;
		}
		const_iterator operator++(int)//suffix version;
		{
			const_iterator previous = *this;
			++(*this);
			return previous;
		}
		const_iterator operator+(int n)
		{
			const_iterator temp = *this;
			while (n--)
				temp.current = temp.current->next;
			return temp;
		}
		bool operator==(const const_iterator &rhs)const { return theList == rhs.theList && current == rhs.current; }  //Check whether if they point to the same node from one list;
		bool operator!=(const const_iterator &rhs)const { return !(*this == rhs); }

	protected:
		Node *current;    //Pointer of current node;
		const SingleList<Object> *theList;    //Pointer of the list current node belongs to;
		const_iterator(Node *p, const SingleList<Object> &lst) :current(p), theList(lst) {}   //This constructor is only used by designer of this class;
	
		void assertIsValid()const   //Check whether if current iterator point to a valid node;
		{
			if(theList == nullptr || current ==nullptr)
			{
				cerr << "Iterator out of bounds exception!" << endl;
				exit(1);
			}
		}
		friend class SingleList<Object>;
	};

	class iterator:public const_iterator{};

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