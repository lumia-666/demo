#include <iostream>

using namespace std;
//��������ǰ++ �ͺ�++������
//����ʹ���෽������
struct T
{
	int a;
	T & operator ++()
	{
		(this->a)++;
		return *this;
	}
	const T operator ++(int)
	{
		const T temp = *this;
		this->a++;
		return temp;
	}
};


ostream& operator <<(ostream &os, const T &t)
{
	os << "a is " << t.a;
	return os;
}
int main()
{
	T t = { 1 };
	//t++���ص���t�仯֮ǰ�ĸ�����������t��ʱ�Ѿ��ı�
	cout << t++ << endl;
	cout << t << endl;
	return 0;
}