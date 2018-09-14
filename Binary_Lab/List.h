#include <iostream>
#include "Node.h"
#ifndef ADD_LIST
#define ADD_LIST
using namespace std;

template<typename T> class List   //Создаем тип данных Список
{
public:
	Node<T> *Tail; //Указатели на адреса начала списка и его конца
	int count = 0;
	list() :Tail(NULL){}; //Инициализируем адреса как пустые
	~list(); //Деструктор
	void show(); //Функция отображения списка на экране
	void add(T x); //Функция добавления элементов в список
	T del();
};

#endif