#include <iostream>
#include <string>
#include <fstream>
using namespace std;

/*
�쳣����㴫��:�����catch���ڲ�׽��һ���쳣, ���Ǹÿ��ڴ����޷����߲��봦����,
���Լ����׳����ϲ�����ߴ���, ֱ���������ķ��try��
*/

void funcOfNo70() throw (string);

void test1OfMEH();

ofstream log_no70("log_no70.txt", ios::app);

int main() {
    try
    {
        funcOfNo70();
    }
    catch (exception e)
    {
        cout << e.what() << endl;
    }
    log_no70.close();
    return 0;
}

void funcOfNo70() throw(string)
{
    throw exception("123");
}

void test1OfMEH()
{
    log_no70 << "throw a string type exception!" << endl;
    throw "error";
}