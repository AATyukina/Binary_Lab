#include <iostream>
#ifndef ADD_NODE
#define ADD_NODE
using namespace std;
template <typename T>
struct Node       //��������� ���������� ������ ������
{
	T x;     //�������� x ����� ������������ � ������
	Node *Next, *Prev;
};

#endif