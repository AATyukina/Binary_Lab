#include <string>
#include <algorithm>
#include <cstdlib>
#include "Binary.h"
#include "Stack.h"


using namespace std;

Binary::Binary(int b)
{
	diap_max = diap_max_count();
	diap_min = diap_min_count();
	if ((b > diap_max) || (b < diap_min))
	{
		std::cout << "Incorrect value range" << endl;
		getchar();
		exit(1);
	}
	for (int i = N - 1, j = 0; i >= 0; i--, j++)
	{
		num[j] = (b >> i) & 0x01;
	}
}
Binary Binary::operator+ (Binary& right)		//Сложение двух двоичных чисел
{
	Binary Temp;
	int middle = 0;
	for (int i = N - 1; i >= 0; i--)
	{
		if ((num[i] == 1) && (right.num[i] == 1))
		{
			if (middle == 0)
				Temp.num[i] = 0;
			else
				Temp.num[i] = 1;
			middle = 1;
		}
		else if (((num[i] == 0) && (right.num[i] == 1)) ||
			((num[i] == 1) && (right.num[i] == 0)))
		{
			if (middle == 1){
				Temp.num[i] = 0;
			}
			else
				Temp.num[i] = 1;
		}
		else
		{
			Temp.num[i] += middle;
			middle = 0;
		}
		if (i == 1 && num[0] == 0 && right.num[0] == 0 && middle == 1)
			throw - 5;
	}
	return Temp;
}
Binary Binary::operator+ (int a)			//Сложение двоичного числа с десятичным 
{
	Binary Temp1, Temp2(a);
	Temp1 = *this + Temp2;
	return Temp1;
}
Binary Binary::operator* (int a){
	Binary Temp1, Temp2(a);
	Temp1 = *this * Temp2;
	return Temp1;
}
Binary Binary::operator- (Binary right)		// Вычитание двух двоичных чисел
{
	Binary Temp1 = *this;
	Binary Temp2 = right;
	if (right == Binary(0))
		return Temp1;
	if (Temp1 >= Temp2)
		return Temp1 + Temp2.addCode();
	else
	{
		Binary Temp_mid = Temp1.addCode() + Temp2;
		Temp_mid.num[0] = 1;
		return Temp_mid;
	}

}
Binary Binary::operator *(Binary right)
{
	if (right == Binary(0) || *this == Binary(0))
		return Binary(0);
	Binary Temp_sum, Temp;
	for (int i = N - 1; i >= 0; i--)
	{
		if (right.num[i] == 0)
		{
			for (int j = 0; j < N; j++)
			{
				Temp.num[j] = 0;
			}
		}
		else
		{
			for (int j = N - 1; j >= 0; j--)
			{
				if (j > i)
					Temp.num[j] = 0;
				else
					Temp.num[j] = num[N - 1 - (i - j)];
			}
		}
		Temp_sum = Temp_sum + Temp;
	}
	if ((right > Temp_sum) || (*this > Temp_sum))
		throw - 5;
	return Temp_sum;
}
bool Binary::operator>=(Binary right){
	Binary Temp = *this;
	if (Temp.dec() >= right.dec())
		return true;
	else
		return false;
}
bool Binary::operator>(Binary right)
{
	Binary Temp = *this;
	if (Temp.dec() > right.dec())
		return true;
	else
		return false;
}
Binary Binary::operator/(Binary right){
	Binary res, Temp(0), check = *this;
	if (right >= check)
	{
		for (int i = 0; i < N; i++)
			res.num[i] = 0;
	}
	if (right == Binary(0))
		throw - 3;
	int midnum[N];
	for (int i = 0; i < N; i++)
		midnum[i] = 0;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (j == N - 1)
				midnum[j] = num[i];
			else
				midnum[j] = Temp.num[j + 1];
		}
		for (int j = 0; j < N; j++)
		{
			Temp.num[j] = midnum[j];
		}
		if (Temp >= right)
		{
			res.num[i] = 1;
			Temp = Temp - right;
		}
		else
			res.num[i] = 0;
	}
	return res;
}
bool Binary::operator==(Binary right)
{
	int k = 0;
	for (int i = 0; i < N; i++)
	{
		if (num[i] != right.num[i])
			break;
		else
			k++;
	}
	if (k == N)
		return true;
	else
		return false;
}
Binary Binary::addCode()
{
	Binary one(1);
	Binary Temp = *this;
	for (int i = 0; i < N; i++)
	{
		if ((Temp.num[i] == 1))
		{
			Temp.num[i] = 0;
		}
		else
		{
			Temp.num[i] = 1;
		}
	}
	Temp = Temp + one;
	Temp.num[0] = 1;
	return Temp;
}
ostream& operator << (ostream &s, const Binary& a)		//Вывод на экран
{
	for (int i = 0; i < a.N; i++){
		s << a.num[i];
	}
	s << endl;
	return s;
}
int Binary::dec()
{
	int res = 0;
	for (int i = 0, j = N - 1; j >= 0; i++, j--)
	{
		if (i < N - 1)
			res += pow(2, i)*num[j];
		else
		{
			if (num[j] == 1)
				res *= (-1);
		}
	}
	return res;
}
int Binary::diap_min_count()
{
	for (int i = 0; i < N; i++)
		num[i] = 1;
	return dec() - 1;
}
int Binary::diap_max_count()
{
	for (int i = 0; i < N; i++)
	{
		if (i == 0)
			num[i] = 0;
		else
			num[i] = 1;
	}
	return dec();
}
#pragma region Lab2 // Методы связного списка
template<typename T>
List<T>::~list()
{
	while (Tail)
	{
		Node *temp = Tail->Prev;
		delete Tail;
		Tail = temp;
	}
	delete count;
}
template<typename T>
void List<T>::add(T x)
{
	Node<T> *temp = new Node<T>;
	temp->Next = NULL;
	temp->x = x;

	if (this->Tail != NULL)
	{
		temp->Prev = Tail;
		Tail->Next = temp;
		Tail = temp;
	}
	else
	{
		temp->Prev = NULL;
		Tail = temp;
	}
	count++;
}
template<typename T>
void List<T>::show()
{

	Node<T> *temp = Tail;
	while (temp != NULL)
	{
		cout << temp->x << " ";
		temp = temp->Prev;
	}
	cout << "\n";
}
template<typename T>
T List<T>::del()
{
	if (Tail != NULL)
	{
		Node<T> *temp = Tail;
		T ret = Tail->x;
		Tail = Tail->Prev;
		if (Tail != NULL)
		{
			Tail->Next = NULL;
		}
		count--;
		delete temp;
		return ret;
	}

	return NULL;
}

#pragma endregion Lab2	






int main()
{
	std::cout << "Enter an arithmetic expression" << endl;
	string str;
	getline(cin, str);

#pragma region Lab1
	/*str.erase(remove(str.begin(), str.end(), ' '), str.end());
	const int massArr = 10;
	Binary sign[massArr];
	int midBase[massArr];
	int oper[massArr][2];
	int usedNumberSign[massArr];
	int numberSign = 0, numberOper = 0;

	for (int i = 0; i < massArr; i++)
	{
	oper[i][0] = 5;
	usedNumberSign[i] = -1;
	midBase[i] = 0;
	}
	int k = 0;
	for (int i = 0; i < (int)str.length(); i++)
	{
	if (isdigit(str[i]))
	{
	k = 0;
	midBase[numberSign] = midBase[numberSign] * 10 + (str[i] - '0');
	}
	else
	{
	k++;
	if (k > 1 || i == 0)
	{
	cout << "Incorrect input" << endl;
	getchar();
	exit(1);
	}

	if (str[i] == '*'){
	oper[numberOper][0] = 0;

	}
	else if (str[i] == '/'){
	oper[numberOper][0] = 1;

	}
	else if (str[i] == '+'){
	oper[numberOper][0] = 2;

	}
	else if (str[i] == '-'){
	oper[numberOper][0] = 3;

	}
	else
	{
	cout << "Incorrect input" << endl;
	getchar();
	exit(1);
	}
	oper[numberOper][1] = numberSign;
	numberSign++;
	numberOper++;
	}
	}
	for (int i = 0; i < massArr; i++)
	sign[i] = Binary(midBase[i]);

	cout << "First param:       " << sign[0] << endl;
	cout << "Second param:       " << sign[1] << endl;
	for (int i = 0; i < massArr - 1; i++)
	{
	for (int j = 0; j < 10 - i - 1; j++) {
	if (oper[j][0] > oper[j + 1][0]) {
	int temp = oper[j][0];
	oper[j][0] = oper[j + 1][0];
	oper[j + 1][0] = temp;

	temp = oper[j][1];
	oper[j][1] = oper[j + 1][1];
	oper[j + 1][1] = temp;
	}
	}
	}
	for (int i = 0; i < massArr; i++)
	{
	if (oper[i][0] == 5)
	break;
	else
	{
	int currenRightNum = oper[i][1] + 1;
	int currenLeftNum = oper[i][1];
	bool flag = true;
	while (flag)
	{
	flag = false;
	for (int j = 0; j < 10; j++)
	{
	if (usedNumberSign[j] == currenRightNum)
	{
	flag = true;
	currenRightNum--;
	break;
	}
	}
	}
	flag = true;
	while (flag)
	{
	flag = false;
	for (int j = 0; j < massArr; j++)
	{
	if (usedNumberSign[j] == currenLeftNum)
	{
	flag = true;
	currenLeftNum--;
	break;
	}
	}
	}
	try
	{
	if (oper[i][0] == 0)
	sign[currenLeftNum] = sign[currenLeftNum] * sign[currenRightNum];
	else if (oper[i][0] == 1)
	sign[currenLeftNum] = sign[currenLeftNum] / sign[currenRightNum];
	else if (oper[i][0] == 2)
	sign[currenLeftNum] = sign[currenLeftNum] + sign[currenRightNum];
	else if (oper[i][0] == 3)
	sign[currenLeftNum] = sign[currenLeftNum] - sign[currenRightNum];
	usedNumberSign[i] = currenRightNum;
	}
	catch (int a)
	{
	if (a == -5)
	cout << "Stack overflow\n";
	else if (a == -4)
	cout << "Divisor exceeds the dividend\n";
	else if (a == -3)
	cout << "Divisor is equal to zero\n";
	getchar();
	return 0;
	}
	}

	}
	cout << "The result in a binary code:       " << sign[0] << endl;
	cout << "The result to decimal code:       " << sign[0].dec() << endl;
	getchar();
	return 0;*/
#pragma endregion Lab1

#pragma region Lab2_cont

	bool trigger = true, zero_trigger = false;
	int temp_num = 0;
	Binary num1, num2, res;
	char sign1;
	StackLinkedList<Binary> *num = new StackLinkedList<Binary>();
	StackLinkedList<char> *sign = new StackLinkedList<char>();

	try
	{
		for (int i = 0; i < (int)str.length(); i++)
		{
			if ((isdigit(str[i + 1])) && (str[i] == '-'))
			{
				sign->push('-');
				num->push(0);
			}

			else if (isdigit(str[i]))
			{
				temp_num = temp_num * 10 + (str[i] - '0');
				zero_trigger = true;
			}
			else if (str[i] != ' ')
			{
				if (!(str[i] == '+' || str[i] == '-' || str[i] == '/' || str[i] == '*'))
					throw - 2;
				sign->push(str[i]);
			}

			if (zero_trigger && (str[i] == ' '))
			{
				num->push(Binary(temp_num));
				temp_num = 0;
				zero_trigger = false;
			}

			if (zero_trigger && (str[i + 1] == '\0'))
			{
				num->push(Binary(temp_num));
			}
		}

		num->reverse();
		sign->reverse();

		if (sign->isEmpty() && (num->length() == 1))
			trigger = false;
		else if (!(num->length() - sign->length() == 1))
			throw - 2;

		while (trigger)
		{
			num1 = num->pop();
			num2 = num->pop();
			sign1 = sign->pop();

			switch (sign1)
			{
			case'+':
				res = num1 + num2;
				break;
			case'-':
				res = num1 - num2;
				break;
			case'*':
				res = num1 * num2;
				break;
			case'/':
				res = num1 / num2;
				break;
			default:
				break;
			}

			num->push(res);
			if (num->length() == 1)
				trigger = false;
		}

		Binary fin_res = num->pop();
		std::cout << "Result: " << fin_res << endl;
		std::cout << "Result2: " << fin_res.dec() << endl;
	}

	catch (int er)
	{
		if (er == -5)
			std::cout << "Stack overflow\n";
		else if (er == -3)
			std::cout << "Divisor is equal to zero\n";
		else if (er == -2)
			std::cout << "Incorrect input of arithmetic expression";
	}

	getchar();
	return 0;
#pragma endregion Lab2_cont
}
