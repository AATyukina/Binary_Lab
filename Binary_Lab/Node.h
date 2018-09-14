#include <iostream>
#ifndef ADD_NODE
#define ADD_NODE
using namespace std;
template <typename T>
struct Node       //Структура являющаяся звеном списка
{
	T x;     //Значение x будет передаваться в список
	Node *Next, *Prev;
};

#endif