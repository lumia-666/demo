#include<iostream>

template<class T>
struct X {
	void f(){}
};

template<class T>
struct Y :X<T>
{
	void t() {
		//�������this�������ǷǴ�����
		//���İ������ģ�嶨�������ȷ��
		//�����������ֲ�������ʵ����֮��ʼ��
		this->f();
;	}
};

template<class T>
struct U {
	//using type = const T::value;//����typename��ʾ����һ�����ͣ�����ĳ���������������typename���������
	using type = typename const T::value;//����typename��ʾ����һ�����ͣ�����ĳ���������������typename���������
};

struct O {
	using value = int;
};

int main() {
	Y<int> y;
	y.t();
	U<O>::type a = 0;
}