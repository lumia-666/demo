#include <windows.h>
#include <stdio.h>
typedef struct {		//��Ե�ַ	
	int m_1;			//0x0
	int m_2;			//0x4
	int m_3;			//0x8
}DATA, *PDATA;
// ���õ�ַ��ƫ�ƺͶ�0�ýṹ��ָ����ǿ������ת����ʵ�ֶԽṹ�����ַ��Ѱַ��
//��������ĳһ��Ա�������иó�Ա�ĵ�ַ�Լ���һ�ṹ����������
#define CONTAINING_RECORD(address,type,field) ((type*)((PCHAR)(address)-(ULONG_PTR)(&((type*)0)->field)))
int main()
{

	DATA Data = { 33,22,11 };
	//int* v3 = (int*)(&((PDATA)0)->m_1);
	int* v1 = &Data.m_2;
	PDATA v2 = CONTAINING_RECORD(v1, DATA, m_2);
	printf("%d %d %d\n", v2->m_1, v2->m_2, v2->m_3);
	//printf("%p\r\n", v3);
	return 0;
}
//����v2���Ƕ���Data�ĵ�ַ�����ǿ��Բ�ʹ��Data��ֱ�ӷ��ʸö���ĳ�Ա
