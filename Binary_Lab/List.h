#include <iostream>
#include "Node.h"
#ifndef ADD_LIST
#define ADD_LIST
using namespace std;

template<typename T> class List   //������� ��� ������ ������
{
public:
	Node<T> *Tail; //��������� �� ������ ������ ������ � ��� �����
	int count = 0;
	list() :Tail(NULL){}; //�������������� ������ ��� ������
	~list(); //����������
	void show(); //������� ����������� ������ �� ������
	void add(T x); //������� ���������� ��������� � ������
	T del();
};

#endif