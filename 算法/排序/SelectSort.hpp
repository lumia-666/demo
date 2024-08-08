#pragma once
#include <iostream>
//#include "common.hpp"

void SelectSort(int *nums, int n) {
	if (n <= 1) return;
	int min;
	//���һ��û��Ҫ����
	for (int i = 0; i < n - 1; ++i) 
	{
		min = i;
		//i+1û��Ҫ���Լ��Ƚ�
		for (int j = i + 1; j < n; ++j)
		{
			if (nums[j] < nums[min])
			{
				min = j;
			}
		}
		if(min != i) swap(nums[min], nums[i]);
	}
}
