#include<iostream>
#include<string>
#include<format>
using namespace std;

struct A
{
	auto operator ()() { cout << 2 << endl; }
};
struct B
{
	auto operator ()() const { ++data_; }
private:
	int& data_;
};

template <typename T, typename ...Ts>
auto concat(T t, Ts ...ts)
{
	if constexpr (sizeof...(ts) > 0)
	{
		return [&](auto ...para) {
			return t(concat(ts...)(para...));
		};
	}
	else
	{
		return t;
	}
}
int main() {
	auto one = [] {return "one"; };//�˴���С���ſ���ʡ��
	auto two = []() -> std::string {return "one"; };//�˴���С���Ų�����ʡ��
	auto a1 = one();
	auto a2 = two();
	auto p2 = [] <typename T> (T && f) { f(); };//c++20
	p2(one);
	p2(std::move(one));
	[] <typename T> (T && f) { f(); }(two);
	A()();
	int num{};
	//auto p3 = [num]() {++num};//�������mutable��Ĭ�ϵ�����()��Ա������const��
	auto p3 = [num]() mutable {++num; cout << num << endl; };//�������mutable��Ĭ�ϵ�����()��Ա������const��
	auto pp = [&num]() {++num; cout << num << endl; };//���������ǿ����޸ĵģ����õĳ����������ð󶨵Ķ���ĳ�������������������ð󶨵�һ���� const �����ϣ���ô�������� const ��Ա������ͨ�������޸ĸö�����Ϊ���ý��ṩ�˶Զ���ķ��ʣ�������Ӱ�������ĳ����ԡ�
	p3();
	cout << num << endl;
	auto p4 = [=] {};//�õ��˾Ͳ��񣬱����ں������õ���num�Ͳ���num
	cout << sizeof(p4) << endl;//1,��Ϊɶ��û�õ�
	cout << sizeof(p3) << endl;//4
	constexpr int c = [] {return 3; }();//��ʽconstexpr
	constexpr int cc = []() constexpr {return 3; }();//��ʽconstexpr
	auto three = [](int i) {return i * 3; };
	auto four = [](int i) {return i * 4; };
	auto f = concat(three, four, std::plus<int>{});
	auto rs = f(1, 2);
}