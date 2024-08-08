#include<iostream>
using namespace std;
class A {
public:
    A() {
        cout << "constructor" << endl;
    }

    A(const A& rhs) {
        cout << "copy constructor" << endl;
    }

    A(A&& rhs) {
        cout << "move constructor" << endl;
    }

    A& operator=(const A& rhs) {
        cout << "copy assignment operator" << endl;
        return *this;
    }

    A& operator=(A&& rhs) {
        cout << "move assignment operator" << endl;
        return *this;
    }

    ~A() {
        cout << "destructor" << endl;
    }
};

A f1() {
	return A();
}

A f2() {
    A a;
    return a;
}
//���� cppreference ��֪��C++ �д��� �������� �����ԣ�
//������������һ����ʱ����������ʡ�������ĸ��ƺ��ƶ����죬�����㸴�Ƶİ�ֵ�������壺
//�� return ����У�����������һ���뺯������������ͬ�������͵Ĵ���ֵʱ
//�ڶ���ĳ�ʼ���У�����ʼ�������ʽ��һ�������������ͬ�������͵Ĵ���ֵʱ
int main() {
	std::cout << "Hello World!\n";
	//A obj = f1();����������ֻ����һ��Ĭ�Ϲ��죬һ������
	A obj = f2();//Ĭ�Ϲ��졢�ƶ����졢��������
    //A a = A(A()); //����������ֻ����һ��Ĭ�Ϲ��죬һ������
}