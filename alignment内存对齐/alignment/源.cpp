#include <iostream>

struct Storage {
	char      a;
	int       b;
	double    c;
	long long d;
};
//���ø����͵Ķ��뷽ʽ�������ܱ�ԭ��Ĭ�ϵ�8С
//��alignasС����Ȼ�������С��λ���򱻺���
struct alignas(1) AlignasStorage {
	char      a;
	int       b;
	double    c;
	long long d;
};

int main() {
	//���ظ����͵��ֽڶ��뷽ʽ
	std::cout << alignof(Storage) << std::endl;//8
	std::cout << sizeof(Storage) << std::endl;
	std::cout << alignof(AlignasStorage) << std::endl;//16
	std::cout << sizeof(AlignasStorage) << std::endl;

	return 0;
}