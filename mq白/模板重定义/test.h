//test.h
#ifndef TEST_TEMPLATE_TEST_H
#define TEST_TEMPLATE_TEST_H
#include<iostream>

//���print����һ��ģ�庯������ô���벻ͨ���������ظ�����
//�����print��һ������ģ�壬
template<typename T = void>
void print() {
	std::cout << 6 << std::endl;
}

#endif //TEST_TEMPLATE_TEST_H