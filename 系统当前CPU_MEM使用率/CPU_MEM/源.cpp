#define _CRT_SECURE_NO_WARNINGS
#define For(n) for(int index = 0;index < n;++index)
//#include "vld.h"
#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
using namespace std;

//windows �ڴ� ʹ����  
DWORD getWin_MemUsage() {
	MEMORYSTATUS ms;
	::GlobalMemoryStatus(&ms);
	return ms.dwMemoryLoad;
}

__int64 CompareFileTime(FILETIME time1, FILETIME time2)
{
	__int64 a = time1.dwHighDateTime << 32 | time1.dwLowDateTime;
	__int64 b = time2.dwHighDateTime << 32 | time2.dwLowDateTime;

	return (b - a);
}
//WIN CPUʹ�����  
void getWin_CpuUsage() {
	HANDLE hEvent;
	BOOL res;
	FILETIME preidleTime;
	FILETIME prekernelTime;
	FILETIME preuserTime;
	FILETIME idleTime;
	FILETIME kernelTime;
	FILETIME userTime;

	res = GetSystemTimes(&idleTime, &kernelTime, &userTime);
	preidleTime = idleTime;
	prekernelTime = kernelTime;
	preuserTime = userTime;

	hEvent = CreateEventA(NULL, FALSE, FALSE, NULL); // ��ʼֵΪ nonsignaled ������ÿ�δ������Զ�����Ϊnonsignaled  

	while (true) {
		WaitForSingleObject(hEvent, 1000);
		res = GetSystemTimes(&idleTime, &kernelTime, &userTime);

		__int64 idle = CompareFileTime(preidleTime, idleTime);
		__int64 kernel = CompareFileTime(prekernelTime, kernelTime);
		__int64 user = CompareFileTime(preuserTime, userTime);

		__int64 cpu = (kernel + user - idle) * 100 / (kernel + user);
		__int64 cpuidle = (idle) * 100 / (kernel + user);
		cout << "CPU������:" << cpu << "%" << " CPU������:" << cpuidle << "%" << endl;

		preidleTime = idleTime;
		prekernelTime = kernelTime;
		preuserTime = userTime;
	}
}

//��ȡ WIN Ӳ��ʹ�����  
int getWin_DiskUsage() {
	int DiskCount = 0;
	DWORD DiskInfo = GetLogicalDrives();
	//����GetLogicalDrives()�������Ի�ȡϵͳ���߼����������������������ص���һ��32λ�޷����������ݡ�    
	while (DiskInfo)//ͨ��ѭ�������鿴ÿһλ�����Ƿ�Ϊ1�����Ϊ1�����Ϊ��,���Ϊ0����̲����ڡ�    
	{
		if (DiskInfo & 1)//ͨ��λ������߼���������ж��Ƿ�Ϊ1    
		{
			++DiskCount;
		}
		DiskInfo = DiskInfo >> 1;//ͨ��λ��������Ʋ�����֤ÿѭ��һ��������λ�������ƶ�һλ��    
		//DiskInfo = DiskInfo/2;    
	}
	cout << "Logical Disk Number:" << DiskCount << endl;
	//-----------------------------------------------------------------------------------------  
	int DSLength = GetLogicalDriveStrings(0, NULL);
	//ͨ��GetLogicalDriveStrings()������ȡ�����������ַ�����Ϣ���ȡ�    
	char* DStr = new char[DSLength];//�û�ȡ�ĳ����ڶ�������һ��c�����ַ�������    
	GetLogicalDriveStrings(DSLength, (LPTSTR)DStr);
	//ͨ��GetLogicalDriveStrings���ַ�����Ϣ���Ƶ�����������,���б�������������������Ϣ��    

	int DType;
	int si = 0;
	BOOL fResult;
	unsigned _int64 i64FreeBytesToCaller;
	unsigned _int64 i64TotalBytes;
	unsigned _int64 i64FreeBytes;

	for (int i = 0; i < DSLength / 4; ++i)//Ϊ����ʾÿ����������״̬����ͨ��ѭ�����ʵ�֣�����DStr�ڲ������������A:\NULLB:\NULLC:\NULL����������Ϣ������DSLength/4���Ի�þ����ѭ����Χ    
	{
		char dir[3] = { DStr[si], '��', '\\' };
		cout << dir;
		DType = GetDriveType(DStr + i * 4);
		//GetDriveType���������Ի�ȡ���������ͣ�����Ϊ�������ĸ�Ŀ¼    
		if (DType == DRIVE_FIXED)
		{
			cout << "Hard Disk";
		}
		else if (DType == DRIVE_CDROM)
		{
			cout << "CD-ROM";
		}
		else if (DType == DRIVE_REMOVABLE)
		{
			cout << "Removable Disk";
		}
		else if (DType == DRIVE_REMOTE)
		{
			cout << "Network Disk";
		}
		else if (DType == DRIVE_RAMDISK)
		{
			cout << "Virtual RAM Disk";
		}
		else if (DType == DRIVE_UNKNOWN)
		{
			cout << "Unknown Device";
		}

		fResult = GetDiskFreeSpaceEx(
			dir,
			(PULARGE_INTEGER)&i64FreeBytesToCaller,
			(PULARGE_INTEGER)&i64TotalBytes,
			(PULARGE_INTEGER)&i64FreeBytes);
		//GetDiskFreeSpaceEx���������Ի�ȡ���������̵Ŀռ�״̬,�������ص��Ǹ�BOOL��������    
		if (fResult)//ͨ�����ص�BOOL�����ж��������Ƿ��ڹ���״̬    
		{
			cout << " totalspace:" << (float)i64TotalBytes / 1024 / 1024 << " MB";//����������    
			cout << " freespace:" << (float)i64FreeBytesToCaller / 1024 / 1024 << " MB";//����ʣ��ռ�    
		}
		else
		{
			cout << " �豸δ׼����";
		}
		cout << endl;
		si += 4;
	}
	return 0;
}

int main(int argc, char **argv)
{
	//+++======================��ȡwindows �ڴ�ʹ����==================+++//  
	DWORD dwValue = getWin_MemUsage();
	printf("�ڴ�ʹ����Ϊ %d %% \n", dwValue);
	//+++======================��ȡWindows CPUʹ����====================+++//  
	getWin_CpuUsage();  
	//+++======================��ȡWindows Ӳ��ʹ��====================+++//  
	getWin_DiskUsage();
	return 0;
}