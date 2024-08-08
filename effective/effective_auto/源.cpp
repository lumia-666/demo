#include<iostream>
#include<array>
using namespace std;
//template<typename T>
//void f(ParamType param);

template<typename T>
void f(T& param) {} // param�Ǹ�����

template<typename T>
void f2(T* param) {} // param�����Ǹ�ָ��

template<typename T>
void f3(T&& param) {} // param�����Ǹ���������

template<typename T>
void f4(T param) {} // param�����ǰ�ֵ����

void test(int a) {
	cout << a << endl;
}

// �Ա����ڳ�����ʽ��������ߴ�(�������β�δ�����֣���Ϊ����ֻ��ϵ�京�е�Ԫ�ظ���)
template<typename T, std::size_t N>
constexpr std::size_t arraySize(T(&)[N]) noexcept // ���ú�������Ϊconstexpr���ܹ�ʹ���䷵��ֵ�ڱ����ھͿ��á��Ӷ��Ϳ�����
{						   // ����һ������ʱ��ָ����ߴ����һ������ͬ�������ߵĳߴ���ӻ����ų�ʼ��ʽ(braced initializer)����ó�
	return N;
}

void someFunc(int, double) {} // someFunc�Ǹ����������ͱ�Ϊvoid(int, double)

int test_item_1()
{
	//f(expr); // ��ĳ���ʽ����f
	//������ͨ��ʵ���Ƶ�ģ��������ͺͺ�����������
	// �ڱ����ڣ���������ͨ��expr�Ƶ������ͱ�һ����T���ͱ���һ����ParamType���ͱ��������ͱ�������һ��

	int x = 27; // x���ͱ���int
	const int cx = x; // cx���ͱ���const int
	const int& rx = x; // rx��x���ͱ�Ϊconst int������

	f(x); // T���ͱ���int, param���ͱ���int&
	f(cx); // T���ͱ���const int, param���ͱ���const int&
	f(rx); // T���ͱ���const int, param���ͱ���const int&, 
	//ע�⣺��ʹrx���������ͱ�TҲ��δ���Ƶ���һ�����ã�ԭ�����ڣ�rx��������(reference-ness)�����ͱ��Ƶ������б�����

	const int* px = &x; // px is ptr to x as a const int
	f2(&x); // T is int, param's type is int*
	f2(px); // T is const int, param's type is const int*

	f3(x); // x is lvalue, so T is int&, param's type is also int&
	f3(cx); // cx is lvalue, so T is const int&, param's type is also const int&
	f3(rx); // rx is lvalue, so T is const int&, param's type is also const int&
	f3(27); // 27 is rvalue, so T is int, param's type is therefore int&&

	// param�Ǹ���ȫ������cx��rx���ڵĶ���----��cx��rx��һ������
	f4(x); // T's and param's types are both int
	f4(cx); // T's and param's types are again both int
	f4(rx); // T's and param's types are still both int

	const char* const ptr = "Fun with pointers"; // ptr is const pointer to const object
	f4(ptr); // pass arg of type const char* const

	const char name[] = "J. P. Briggs"; // name's type is const char[13]
	const char* ptrToName = name; // array decays to pointer

	f4(name); // name is array, but T deduced as const char*
	f(name); // pass array to f, T���ͱ��Ƶ������const char[13], ��f���β�(�������һ������)�ͱ����Ƶ�Ϊconst char (&)[13]

	int keyVals[] = { 1, 3, 7, 9, 11, 22, 35 };
	fprintf(stdout, "array length: %d\n", arraySize(keyVals)); // 7
	int mappedVals[arraySize(keyVals)]; // mappedVals��ָ����֮��ͬ
	std::array<int, arraySize(keyVals)> mappedVals2; // mappedVals2Ҳָ��Ϊ7��Ԫ��

	f4(someFunc); // param���Ƶ�Ϊ����ָ��(ptr-to-func)�������ͱ���void (*)(int, double)
	f(someFunc); // param���Ƶ�Ϊ��������(ref-to-func), �����ͱ���void (&)(int, double)

	return 0;
}

int main() {
	int a = 1;
	const int& b = a;
	test(b);//�˴�������(reference-ness)������
	test_item_1();
	return 0;
}