#define For(n) for(int index = 0;index < n;++index)
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<vector>
#include"nocopyable.h"
using namespace std;

class A:public noncopyable {
public:
	A() { data_ = 0; }
	A(int a) {
		data_ = a;
	}
	A(A& a) {
		data_ = a.data_;
	}

private:
	int data_;
};


class Base:noncopyable {
public:
	Base() { cout << "Base Default Constructor" << endl; }
	Base(const Base&) { cout << "Base Copy Constructor" << endl; }
};
class Drived : public Base {
public:
	Drived() { cout << "Drived Default Constructor" << endl; }
	Drived(const Drived& d) {
		cout << "Drived Copy Constructor" << endl;
	}
};


int main() {
	A a(3);
	a.set(2);
	A b = a;//ִ��������Ŀ�������Ϳ�����ֵ֮ǰ��Ҫ���û���Ŀ�������Ϳ�����ֵ
	//�����ڻ���Ŀ�������Ϳ�����ֵ��delete���ˣ����Ա���ʧ��

	//����ʱ�����໹�����Զ��忽�����죬��Ϊ���������û���Զ��忽�����죬������ִ�п�������֮ǰ����ִ�л����Ĭ��
	//�������죻����������Զ��忽�����죬������ִ�п�������֮ǰ����ִ�л����Ĭ�Ϲ��죬���ǿ������졣
	Drived d1;
	Drived d2(d1);
	system("pause");
	return 0;
}