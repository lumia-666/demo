#include<iostream>
#include<string>
using namespace std;

template<typename T>
struct Test
{
	Test(T) {}
	T s;
};
//�Ƶ�ָ��,�������������Լ����Ƶ�ָ��
Test(const char*)->Test<string>;

template<typename T, size_t size>
struct arr {
	T array[size];
};

struct test
{
	int arr[1];
};
//�Ƶ�ָ�������þ��ǲ���Ҫ�ڳ�ʼ��ʱָ�����������ͺ͸�����ȴ��������array(int,3)������Ч��
template<typename _Ty,typename ..._Tp>
arr(_Ty,_Tp...)->arr<std::enable_if_t<(std::is_same_v<_Ty,_Tp>&&...),_Ty>,sizeof...(_Tp)+ 1>;

template<typename T>
typename std::enable_if<true>::type fun(T) {

}

int main() {
	Test t1("123");
	std::enable_if_t<true,int> a = 1;
	fun(1);
	arr b{ 1,2,3 };
	test t{1};
	system("pause");
}