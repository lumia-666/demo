#define _CRT_SECURE_NO_WARNINGS
#define For(n) for(int index = 0;index < n;++index)
#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include <windows.h>
using namespace std;
int main()
{
	//��bInitialOwner ����ΪTRUE���ó�������ӵ����������壬lpName ���ƿ�����ȡ
	//HANDLE hMutex = ::CreateMutex(NULL, TRUE, (LPCTSTR)L"name");
	//if (hMutex != NULL)
	//{
	//	if (GetLastError() == ERROR_ALREADY_EXISTS)
	//	{
	//		//ʵ���Ѵ��ڣ��˳�����
	//		CloseHandle(hMutex);
	//		hMutex = NULL;
	//		return 0;
	//	}
	//}
	while (true)
	{

		const char *str1 = "hello";
		char str2[] = "hello";
		printf("%d\n", str1 == "hello");//1
		printf("%d\n", str2 == "hello");//0
		printf("%d\n", strcmp(str1, "hello"));//0
		printf("%d\n", strcmp(str2, "hello"));//0
		//char str[50];
		//time_t now = time(NULL);
		//strftime(str, 50, "%b", localtime(&now));
		//cout << str << endl;
		break;
	}
	system("pause");
	return 0;
}