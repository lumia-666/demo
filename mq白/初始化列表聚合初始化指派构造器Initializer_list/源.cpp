#include<iostream>
#include<vector>
using namespace std;
template <class T>
//c++�кܶ��ʼ����ʽ��Ĭ�ϳ�ʼ����ֵ��ʼ�������Ƴ�ʼ�����б��ʼ�����ۺϳ�ʼ����ָ���飬�ṹ��ȳ�ʼ����
struct MyStruct
{
	//MyStruct(){}//�û�����Զ����˹��캯������಻����ۺ��࣬�޷�ʹ�þۺϳ�ʼ��
	//��ʱ�����û����ų�ʼ�����б��б��ʼ��һ������
	// ���ж�Ӧ���캯������һ�� std::initializer_list ����
	//MyStruct() = default;
	MyStruct(std::initializer_list<T> l) {
		std::cout << "constructed with a " << l.size() << "-element list\n";
	}
	int a;
	double b;
	char* c;
};

class M
{
	void test(){}
};

int main() {
	MyStruct m = { 1,2 };
	//������ָ�ɳ�ʼ������c++20�����밴�ճ�Ա����˳��,������Ϊinitializer_list����
	//MyStruct m2 = { .a = 1 ,.c = (char*)"haha"};
	auto a = { 1,2,3 };
	M m3 = {};
	system("pause");
}