#include<iostream>
using namespace std;
//һ��Ҫ��һ����f��Ϊ�ݹ���õĳ��ڣ��ϸ��������ⲻ�����ݹ�
//��Ϊ�ݹ����Լ������Լ���ģ��ݹ�ÿ�εĲ�������һ������������ͬһ������
//ģ��һ��Ҫʵ�����ɾ���ĺ���������
void f()
{
}


template<typename T, typename ... Args>
void f(T t, Args... args)
{
	cout << t << endl;
	//������if���Ա����f
	//if constexpr (sizeof...(args)) 
	f(args...);
}


/* First instantiated from: insights.cpp:16 */
//�����������ʵ�������ɲ�ͬ�İ汾
#ifdef INSIGHTS_USE_TEMPLATE
template<>
void f<int, const char*, int>(int t, const char* __args1, int __args2)
{
	std::cout.operator<<(t).operator<<(std::endl);
	f(__args1, __args2);
}
#endif


/* First instantiated from: insights.cpp:11 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
void f<const char*, int>(const char* t, int __args1)
{
	std::operator<<(std::cout, t).operator<<(std::endl);
	f(__args1);
}
#endif


/* First instantiated from: insights.cpp:11 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
void f<int>(int t)
{
	std::cout.operator<<(t).operator<<(std::endl);
	f();
}
#endif
;


int main()
{
	f(1, "2", 3);
	int a = 0;
	int&& a1 = a++;
	system("pause");
	return 0;
}
