#pragma once
#include <random>
#include <time.h>

void swap(int &a, int &b)
{
	//��Ȼ��ͬ���������ᶼ���0
	if (a == b) return;
	a = a ^ b;
	b = a ^ b;
	a = a ^ b;
}

int * CreateRandomArray(int num)
{
	auto arr = new int[num];
	for (size_t i = 0; i < num; ++i)
	{
		arr[i] = rand() % 10000;
	}
	return arr;
}