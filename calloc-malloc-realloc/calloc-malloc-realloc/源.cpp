#define For(n) for(int index = 0;index < n;++index)
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<vector>
#include<stdlib.h>
using namespace std;

void test1()
{
    int* p = (int*)malloc(20 * sizeof(int));
    int* pp = (int*)calloc(20, sizeof(int));
    int i;

    printf("malloc����Ŀռ�ֵ:\n\n");
    for (i = 0; i < 20; i++)
    {
        printf("%d ", *p++);
    }
    printf("\n\n");
    printf("calloc����Ŀռ��ֵ:\n\n");
    for (i = 0; i < 20; i++)
    {
        printf("%d ", *pp++);
    }
    printf("\n");
}

void test2()
{
    char* str = NULL;

    // ����һ������Ϊ 10 ���ַ���
    str = (char*)malloc(10 * sizeof(char));
    if (str == NULL) {
        printf("Error: memory allocation failed.\n");
        exit(1);
    }

    // ���ַ�����ʼ��Ϊ "Hello"
    strcpy(str, "Hello");
    strcpy(str + 5, ", 123world!");
    // ��չ�ַ�������Ϊ 20
    str = (char*)realloc(str, 20 * sizeof(char));
    if (str == NULL) {
        printf("Error: memory allocation failed.\n");
        exit(1);
    }

    // ���µ� 10 ���ַ���ʼ��Ϊ ", world!"
    strcpy(str + 5, ", world!");

    // ������ַ���
    printf("New string: %s\n", str);

    // �ͷ��ڴ�
    free(str);
}

int main() {
    test1();
    test2();
	system("pause");
	return 0;
}