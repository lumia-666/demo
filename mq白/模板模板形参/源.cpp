#include<iostream>
using namespace std;

template<class T>
struct X{};

template<class T,template<class T> typename C>
struct Y {
	C<T>c;
};

template<class T>
struct X2
{
	T t;
};
// ���͵�ģ����
template <typename T>
class MyClass {
public:
    MyClass(T data) {
        // ʵ�ִ���
    }
};

// ����ָ�����͵��ػ�ʵ��
template <typename T>
class MyClass<T*> {
public:
    MyClass(T* data) {
        // �ػ���ʵ�ִ���
    }
};

int f() {
    return 3;
}


int main() {
    int &&a = f();
    int b = 4;
    a = b;
    b = 5;
}