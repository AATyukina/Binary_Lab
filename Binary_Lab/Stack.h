#include <iostream>
#include "List.h"
#ifndef ADD_STACK
#define ADD_STACK
using namespace std;

template<class T> class StackLinkedList
{
public:
	StackLinkedList()
	{
		ls = new List<T>();
	}

	void push(T item)
	{
		ls->Add(item);
	}

	T pop()
	{
		return ls->del();
	}

	void reverse()
	{
		StackLinkedList<T> *temp_arr = new StackLinkedList<T>();
		if (this->length() != 0)
		{
			while (true)
			{
				temp_arr->push(this->pop());
				if (this->isEmpty())
					break;
			}

			*this = *temp_arr;
			delete temp_arr;
		}
	}

	bool isEmpty()
	{
		if (this->ls->count == 0)
			return true;
		return false;
	}

	void printSLL()
	{
		this->ls->Show();
	}

	int length()
	{
		//	int counter = 0;
		//	Node<T> *temp = ls->Tail;

		//	while (true)
		//	{
		//		counter++;
		//		if (temp->Prev == NULL)
		//			break;
		//		temp = temp->Prev;
		//	}
		//	return counter;
		//}
		return this->ls->count;
	}

private:
	List<T> *ls;
};

#endif