#include <iostream>
#include <string>

void g(double) { std::cout << "g(double)\n"; }

template<class T>
struct S
{
    void f() const
    {
        g(1); // "g" �ǷǴ����������ڰ�
    }
};

void g(int) { std::cout << "g(int)\n"; }

int main()
{
    g(1);  // ���� g(int)

    S<int> s;
    s.f(); // ���� g(double)
}