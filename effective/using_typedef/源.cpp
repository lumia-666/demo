#include<iostream>
#include<unordered_map>
#include<vector>
using namespace std;
class Widget9 {};

typedef void (*FP1)(int, const std::string&);
using FP2 = void (*)(int, const std::string&);

//����ģ��
template<typename T>
using MyAllocList1 = std::list<T/*, MyAlloc<T>*/>; // C++11,  MyAllocList1<T>��std::list<T, MyAlloc<T>>��ͬ���

template<typename T>
struct MyAllocList2 { // MyAllocList<T>::type ��std::list<T, MyAlloc<T>>��ͬ���
	typedef std::list<T/*, MyAlloc<T>*/> type;
};

template<typename T>
class Widget9_2 { // Widget9_2<T>��һ��MyAllocList2<T>�ͱ�����ݳ�Ա
private:
	typename MyAllocList2<T>::type list; // MyAllocList2<T>::type����һ��������ģ���ͱ��β�(T)���ͱ�����MyAllocList2<T>::type��Ϊ�������ͱ�C++�й���֮һ���Ǵ������ͱ����ǰ��Ӹ�typename
};

template<typename T>
class Widget9_1 {
private:
	//������������ģ�廯(������������Ǳ���Ϊ����ģ�壬alias template)��typedef�Ͳ��С�
	MyAllocList1<T> list; // ������"typename"��"::type"
};

int test_item_9()
{
	typedef std::unique_ptr<std::unordered_map<std::string, std::string>> UPtrMapSS1;
	using UPtrMapSS2 = std::unique_ptr<std::unordered_map<std::string, std::string>>; // C++11, alias declaration

	MyAllocList1<Widget9> lw1;
	MyAllocList2<Widget9>::type lw2;
	typedef const char cc;
	std::remove_const<cc>::type a; // char a
	std::remove_const<const char*>::type b; // const char* b

	typedef int&& rval_int;
	typedef std::remove_reference<int>::type A;

	//std::remove_const<T>::type // C++11: const T --> T
	//std::remove_const_t<T>     // C++14�еĵȼ���
	//template<class T>
	//using remove_const_t = typename remove_const<T>::type;

	//std::remove_reference<T>::type // C++11: T&/T&& --> T
	//std::remove_reference_t<T>     // C++14�еĵȼ���
	//template<class T>
	//using remove_reference_t = typename remove_reference<T>::type;

	return 0;
}
int main() {
	return 0;
}