#include <iostream>
using namespace std;
#include <string>
class A
{
public:
	A(int a) :m_A(a) {}
	int m_A;
	static const int m_B = 1;
	static void show()
	{
		cout << "��̬��Ա����show�ĵ���m_B=" << m_B << endl;//��̬��Ա�������ʾ�̬��Ա����
	}
	static void fun()
	{
		cout << "��̬��Ա����fun�ĵ���" << endl;
		show();//��̬��Ա�������þ�̬��Ա����
	}
};

const int& f(const int& r)
{
	return r;
}

//int Person::m_B = 10;//�������ռ䣬��ȫ����
int main()
{
	int n = 1 ? (1, A::m_B) // S::x �ڴ˴�δ�� ODR ʹ��
		: 0;  // S::x �ڴ˴��� ODR ʹ�ã���Ҫһ������
	//��̬���������ڱ���׶ξͷ���ռ䣬����û�д���ʱ�����Ѿ�����ռ䡣
	//��̬��Ա�������������������������ⶨ�塣
	//��̬���ݳ�Ա������ĳ��������Ϊ�������ռ��в�������̬��Ա��ռ�ռ䡣
	return 0;
}
