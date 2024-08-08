#include<iostream>
#include<vector>
using namespace std;
//�����޶��������ö���ͱ���ͨ����enum class�������ģ�������ʱ����Ҳ����Ϊö���ࡣ

//�޶��������ö���ͱ���������ֿռ���Ⱦ���ͣ��Ѿ��ǡ�Ӧ������ѡ�����������ǲ��޷�Χ��ö���ͱ𡱵��㹻���ɡ�
//�����޶��������ö���ͱ��еڶ������ƣ�����ö�����Ǹ�ǿ�ͱ��(strongly typed)��
//���޷�Χ��ö���ͱ��е�ö����������ʽת���������ͱ�(���ܹ��Ӵ˴���һ��ת���������ͱ�)��
//���޶��������ö���ͱ��κ������ͱ𶼲�������ʽת��·����
std::vector<std::size_t> primeFactors(std::size_t x) { return std::vector<std::size_t>(); }

enum class Status; // ǰ������, Ĭ�ϵײ��ͱ�(underlying type)��int
enum class Status2 : std::uint32_t; // Status2�ĵײ��ͱ���std::uint32_t
enum Color : std::uint8_t; // ���޷�Χ��ö���ͱ��ǰ���������ײ��ͱ���std::uint8_t

int test_item_10()
{
	enum Color1 { black, white, red }; // ���޷�Χ��(unscoped)ö���ͱ�black, white, red�����������Color1��ͬ
	//auto white = false; // error, white already declared in this scope
	Color1 c1 = black;

	enum class Color2 { black2, white2, red2 }; // C++11, �޶��������(scoped)ö���ͱ�:black2, white2, red2�����������޶���Color2��
	auto white2 = false; // û���⣬��Χ�ڲ�������"white2"
	//Color2 c1 = black2; // ���󣬷�Χ�ڲ�����Ϊ"black2"��ö����
	Color2 c2 = Color2::black2; // fine
	auto c3 = Color2::black2; // also fine

	if (c1 < 14.5) // ��Color1�ͱ��double�ͱ�ֵ���Ƚ�,��̥
		auto factors = primeFactors(c1);

	//if (c2 < 14.5) // ���󣬲��ܽ�Color�ͱ��double�ͱ�ֵ���Ƚ�
	//	auto facotrs = primeFactors(c2); // ���󣬲��ܽ�Color2�ͱ���Ҫ��std::size_t�ͱ��βεĺ���

	return 0;
}
int main() {
	test_item_10();
	return 0;
}