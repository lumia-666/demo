#include <assert.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#ifdef _DEBUG
#define DEBUG_CLIENTBLOCK   new( _CLIENT_BLOCK, __FILE__, __LINE__)
#else
#define DEBUG_CLIENTBLOCK   new( _CLIENT_BLOCK, __FILE__, __LINE__)
#endif
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#ifdef _DEBUG
#define new DEBUG_CLIENTBLOCK
#endif
#define new DEBUG_CLIENTBLOCK
using namespace std;
void Exit()
{
	int i = _CrtDumpMemoryLeaks();
}
int main()
{
	//ifstream fin("input.txt"); // ���������ļ�
	//ofstream fout("output.txt"); //����ļ�
	//streambuf *cinbackup;
	//streambuf *coutbackup;
	//coutbackup = cout.rdbuf(fout.rdbuf()); //�� rdbuf() ���¶���
	//cinbackup = cin.rdbuf(fin.rdbuf()); //�� rdbuf() ���¶���
	atexit(Exit);
	int* p = new int();
	return 0;
}