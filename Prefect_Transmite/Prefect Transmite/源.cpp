#pragma message( "Compiling " __FILE__ )         //��ʾ��������ļ�
#pragma message( "Last modified on " __TIMESTAMP__ )     //�ļ����һ���޸ĵ����ں�ʱ�� 
#pragma warning( push, 4 )
#define For(n) for(int index=0;index<n;++index)
//#include "vld.h"
#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <set>
#include <array>
using namespace std;
// �ȽϽӽ�C++11��std::move��ʾ��ʵ��,������ȫ���ϱ�׼������ϸ��
template<typename T> // in namespace std
typename std::remove_reference<T>::type&& move(T&& param)
{
	using ReturnType = typename std::remove_reference<T>::type&&; // ��������
	return static_cast<ReturnType>(param);
}

// C++14�бȽϽӽ���std::moveʾ��ʵ��
template<typename T> // C++14, still in namespace std
decltype(auto) move(T&& param)
{
	using ReturnType = std::remove_reference_t<T>&&;
	return static_cast<ReturnType>(param);
}

class Widget23 {};

void process(const Widget23& lvalArg) { fprintf(stderr, "process lvalues\n"); } // process lvalues
void process(Widget23&& rvalArg) { fprintf(stderr, "process rvalues\n"); } // process rvalues

template<typename T>
void logAndProcess(T&& param) // template that passes param to process
{
	process(std::forward<T>(param));
}

int test_item_23()
{
	Widget23 w;
	logAndProcess(w); // call with lvalue
	logAndProcess(std::move(w)); // call with rvalue

	return 0;
}
std::multiset<std::string> names; // global data structure

//void logAndAdd(const std::string& name) // ��һ��ʵ�ַ���
template<typename T>
void logAndAdd(T&& name) // universal reference���ڶ���ʵ�ַ���
{
	auto now = std::chrono::system_clock::now();
	fprintf(stdout, "time point\n");
	names.emplace(name);
	//names.emplace(std::forward<T>(name));
}

std::string nameFromIdx(int idx) // ����������Ӧ������
{
	return std::string("xxx");
}

void logAndAdd(int idx) // �µ����غ���
{
	auto now = std::chrono::system_clock::now();
	fprintf(stdout, "time point2\n");
	names.emplace(nameFromIdx(idx));
}

int test_item_26()
{
	std::string petName("Darla");

	logAndAdd(petName); // as before, copy lvalue into multiset
	logAndAdd(std::string("Persephone")); // move rvalue instead of copying it
	logAndAdd("Patty Dog"); // create std::string in multiset instead of copying a temporary std::string

	logAndAdd(22); // �����β��ͱ�Ϊint�����ذ汾

	short nameIdx = 100;
	//logAndAdd(nameIdx); // error c2664, �β��ͱ�ΪT&&�İ汾���Խ�T�Ƶ�Ϊshort, ����short�ͱ��ʵ����˵���������ò����˱�int���õ�ƥ��

	return 0;
}
std::multiset<std::string> names27; // global data structure
std::string nameFromIdx27(int idx) { return std::string("xxx"); }

template<typename T>
void logAndAddImpl(T&& name, std::false_type) // ������ʵ��
{
	auto now = std::chrono::system_clock::now();
	fprintf(stdout, "time point: no int\n");
	names27.emplace(std::forward<T>(name));
}

void logAndAddImpl(int idx, std::true_type) // ����ʵ��
{
	auto now = std::chrono::system_clock::now();
	fprintf(stdout, "time point: int\n");
	names.emplace(nameFromIdx(idx));
}

template<typename T>
void logAndAdd27(T&& name) // name to data structure
{
	logAndAddImpl(std::forward<T>(name), std::is_integral<typename std::remove_reference<T>::type>());
}

class Person {
public:
	//template<typename T, typename = typename std::enable_if<!std::is_same<Person, typename std::decay<T>::type>::value>::type>
	//template<typename T, typename = typename std::enable_if<!std::is_base_of<Person, typename std::decay<T>::type>::value>::type> // ��ʹ�̳���Person���࣬�����û���Ĺ��캯��ʱ�ߵ��ǻ���Ŀ������ƶ����캯��
	//template<typename T, typename = std::enable_if_t<!std::is_base_of<Person, std::decay_t<T>>::value>> // C++14
	template<typename T, typename = std::enable_if_t<!std::is_base_of<Person, std::decay_t<T>>::value &&
		!std::is_integral<std::remove_reference_t<T>>::value>> // C++14
		explicit Person(T&& n) // ֻ��ָ�������������˲Ż����ô�ģ��, constructor for string and args convertible to string
		: name(std::forward<T>(n))
	{
		// assert that a std::string can be created from a T object
		static_assert(std::is_constructible<std::string, T>::value, "Parameter n can't be used to construct a std::string");
	}

	explicit Person(int idx) // constructor for integral args
		: name(nameFromIdx27(idx)) {}

private:
	std::string name;
};
class MyClass
{
public:
	MyClass(string &str);
private:
	string m_str;

};

int test_item_27()
{
	// ע�⣺test_item_26()��test_item_27()ʵ�ֵĲ���
	std::string petName("Darla");
	Person p2(petName);
	logAndAdd27(petName);
	logAndAdd27(std::string("Persephone"));
	logAndAdd27("Patty Dog");

	logAndAdd27(22);

	short nameIdx = 100;
	logAndAdd27(nameIdx);

	return 0;
}
int main()
{
	//test_item_23();
	/*test_item_27();*/
	std::vector<int> aw1(10000,1);
	// ... // put data into aw1
	// move aw1 into aw2. runs in linear time. all elements in aw1 are moved into aw2
	auto aw2 =(aw1);

	system("pause");
	return 0;
}

MyClass::MyClass(string & str)
{
	m_str = str;
}
