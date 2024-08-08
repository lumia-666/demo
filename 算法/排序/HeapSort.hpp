#pragma once
#include "common.hpp"
#include <vector>
using namespace std;

void Heapify(vector<int> &arr, int arrLen)
{
	for (int i = arrLen / 2 - 1; i >= 0; --i)
	{
		if (arr[i] < arr[i * 2 + 1])
		{
			swap(arr[i], arr[i * 2 + 1]);
		}
		if (i * 2 + 2 < arrLen)
		{
			if (arr[i] < arr[i * 2 + 2])
			{
				swap(arr[i], arr[i * 2 + 2]);
			}
		}
	}
}

//�ѽṹ:���ӵ��±���2*i+1���Һ����±�2*i+2)
//������������ڵ��±���Զ�һ���Ǹ��ڵ�
void HeapSort(vector<int> &arr, int arrLen)
{
	for (int i = 0; i < arrLen - 1; ++i)
	{
		Heapify(arr, arrLen - i);
		swap(arr[0], arr[arrLen - i - 1]);
		For(10)
		{
			cout << arr[index] << "\t";
		}
		cout << endl;
	}
}
