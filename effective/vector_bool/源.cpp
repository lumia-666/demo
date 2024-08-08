#include<iostream>
#include<vector>
using namespace std;
class Widget6 {};
std::vector<bool> features(const Widget6& w)
{
	return std::vector<bool>{true, true, false, false, true, false};
}


class Widget7 {
public:
	Widget7(int i, bool b) {} // constructor not declaring std::initializer_list params
	Widget7(int i, double d) {}
	//Widget7(std::initializer_list<long double> il) { fprintf(stdout, "std::initializer_list params\n"); }
	Widget7() = default;
	Widget7(int) {}

	operator float() const { return 1.0f; } // ǿ��ת����float�ͱ�, ע�⣺�˺���������,�����w13��w15

private:
	int x{ 0 }; // fine, x's default value is 0
	int y = 0; // also fine
	//int z(0); // error
};

void processWidget6(const Widget6& w, bool highPriority) {}

double calcEpsilon() { return 1.0; }
//vector<bool>��һ��α��������������������bool�����Ǵ��bool�Խ�ʡ�ռ䡣��һ�����͵�ʵ���У�
//ÿ�������ڡ�vector���еġ�bool��ռ��һ�������ı��أ���һ��8���ص��ֽڽ�����8����bool�������ڲ���
//vector<bool>ʹ������λ��bitfield���ȼ۵�˼������ʾ����װ���ɵ�bool��
//���õ�������Ҳ�ǽ�ֹ�ģ���Ϊvector<bool>�ӿڵ���ưڳ������⡣��Ϊvector<T>::operator[]�ķ���ֵӦ����T& ��
//���vector<bool>��������bool���ⲻ�����⣬����Ϊ��û�У�vector<bool>::operator[]��Ҫ����ָ��һ�����ص����ã�
//���������������Ķ�����Ϊ�˽��������⣬vector<boo>::operator[]����һ����������Ϊ�����ڱ��ص����ã�Ҳ��Ϊ�������
int test_item_6()
{
	Widget6 w;
	bool highPriority = features(w)[5]; // ��ȷ,��ʽ����highPriority���ͱ�
	processWidget6(w, highPriority);

	// ��highPriority����ʾ�ͱ�ĳ�auto
	auto highPriority2 = features(w)[5]; // highPriority2���ͱ����Ƶ�����,std::vector<bool>��operator[]�ķ���ֵ��
										//����������һ��Ԫ�ص�����(����bool�Ǹ�����),���ص��Ǹ�
										//std::vector<bool>::reference�ͱ�Ķ���,����һ��std::vector<bool>�ͱ����ʱ����
	processWidget6(w, highPriority2); // undefined behavior, highPriority2 contains dangling pointer(����ָ��)

	auto highPriority3 = static_cast<bool>(features(w)[5]); // ��ȷ
	processWidget6(w, highPriority3);

	float ep = calcEpsilon(); // ��ʽת�� double-->float,����д�����Ա���"�ҹ��⽵���˺����ķ���ֵ����"
	auto ep2 = static_cast<float>(calcEpsilon()); // �Ƽ�

	return 0;
}

int main() {
	Widget7 w10{ 10, true };
	int a = 1;
	const int& b = a;
	test_item_6();
	return 0;
}