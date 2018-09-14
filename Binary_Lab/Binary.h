#include <iostream>
#ifndef ADD_BINARY
#define ADD_BINARY
using namespace std;
class Binary
{
private:
	static const int N = 8;
	int num[N];
	int diap_min = 0, diap_max = 0;
public:
	Binary(int b = 0);
	Binary operator+ (Binary& right);		//�������� ���� �������� �����
	Binary operator+ (int a);			//�������� ��������� ����� � ���������� 
	Binary operator* (int a);
	Binary operator- (Binary right);	// ��������� ���� �������� �����
	Binary operator *(Binary right);
	bool operator>=(Binary right);
	bool operator>(Binary right);
	Binary operator/(Binary right);
	Binary addCode();
	bool operator==(Binary right);
	friend ostream& operator << (ostream &s, const Binary& a);		//����� �� �����
	int dec();
	int diap_min_count();
	int diap_max_count();
};
#endif