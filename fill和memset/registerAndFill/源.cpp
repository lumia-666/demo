//#pragma GCC optimize(2)
#include <iostream>
#include <time.h>
using namespace std;

//memset��Ҫ��������и�ֵ���Ҷ�int�����飬ֻ�ܸ�ֵΪ0�� - 1
//fill�������Զ�������������������и�ֵ��ֵ��������
//fill��memset��������int��������ʱ��fill�����ٶȽ���
#define max 100000000+5
int a[max];
int main()
{
	time_t beg, end;

	cout << "---------------------------for\n";
	beg = clock();
	for (int i = 0; i < max; ++i) a[i] = 0;
	end = clock();
	cout << "test 1 cost: " << end - beg << "MS" << endl;
	beg = clock();
	for (int i = 0; i < max; ++i) a[i] = 0;
	end = clock();
	cout << "test 2 cost: " << end - beg << "MS" << endl;
	beg = clock();
	for (int i = 0; i < max; ++i) a[i] = 0;
	end = clock();
	cout << "test 3 cost: " << end - beg << "MS" << endl;
	beg = clock();
	for (int i = 0; i < max; ++i) a[i] = 0;
	end = clock();
	cout << "test 4 cost: " << end - beg << "MS" << endl;
	beg = clock();
	for (int i = 0; i < max; ++i) a[i] = 0;
	end = clock();
	cout << "test 5 cost: " << end - beg << "MS" << endl;
	beg = clock();
	for (int i = 0; i < max; ++i) a[i] = 0;
	end = clock();
	cout << "test 6 cost: " << end - beg << "MS" << endl;

	cout << "----------------register---for\n";
	beg = clock();
	for (register int i = 0; i < max; ++i) a[i] = 0;
	end = clock();
	cout << "test 1 cost: " << end - beg << "MS" << endl;
	beg = clock();
	for (register int i = 0; i < max; ++i) a[i] = 0;
	end = clock();
	cout << "test 2 cost: " << end - beg << "MS" << endl;
	beg = clock();
	for (register int i = 0; i < max; ++i) a[i] = 0;
	end = clock();
	cout << "test 3 cost: " << end - beg << "MS" << endl;
	beg = clock();
	for (register int i = 0; i < max; ++i) a[i] = 0;
	end = clock();
	cout << "test 4 cost: " << end - beg << "MS" << endl;
	beg = clock();
	for (register int i = 0; i < max; ++i) a[i] = 0;
	end = clock();
	cout << "test 5 cost: " << end - beg << "MS" << endl;
	beg = clock();
	for (register int i = 0; i < max; ++i) a[i] = 0;
	end = clock();
	cout << "test 6 cost: " << end - beg << "MS" << endl;

	cout << "---------------------------fill\n";
	beg = clock();
	fill(a, a + max, 0);
	end = clock();
	cout << "test 1 cost: " << end - beg << "MS" << endl;
	beg = clock();
	fill(a, a + max, 0);
	end = clock();
	cout << "test 2 cost: " << end - beg << "MS" << endl;
	beg = clock();
	fill(a, a + max, 0);
	end = clock();
	cout << "test 3 cost: " << end - beg << "MS" << endl;
	beg = clock();
	fill(a, a + max, 0);
	end = clock();
	cout << "test 4 cost: " << end - beg << "MS" << endl;
	beg = clock();
	fill(a, a + max, 0);
	end = clock();
	cout << "test 5 cost: " << end - beg << "MS" << endl;
	beg = clock();
	fill(a, a + max, 0);
	end = clock();
	cout << "test 6 cost: " << end - beg << "MS" << endl;

	cout << "---------------------------memset\n";
	beg = clock();
	memset(a, 0, sizeof(a));
	end = clock();
	cout << "test 1 cost: " << end - beg << "MS" << endl;
	beg = clock();
	memset(a, 0, sizeof(a));
	end = clock();
	cout << "test 2 cost: " << end - beg << "MS" << endl;
	beg = clock();
	memset(a, 0, sizeof(a));
	end = clock();
	cout << "test 3 cost: " << end - beg << "MS" << endl;
	beg = clock();
	memset(a, 0, sizeof(a));
	end = clock();
	cout << "test 4 cost: " << end - beg << "MS" << endl;
	beg = clock();
	memset(a, 0, sizeof(a));
	end = clock();
	cout << "test 5 cost: " << end - beg << "MS" << endl;
	beg = clock();
	memset(a, 0, sizeof(a));
	end = clock();
	cout << "test 6 cost: " << end - beg << "MS" << endl;
	return 0;
}