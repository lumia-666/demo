#define For(n) for(int index = 0;index < n;++index)
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<vector>
#include"PObject.h"
using namespace std;

class testClass
{
public:
    testClass(int data) :data(data) {}
    int getData() { return this->data; }
    void setData(int data) { this->data = data; }
    void* operator new(size_t size)
    {
        return malloc(size);
    }
    void* operator new(size_t size,void *ptr)
    {
        printf("global new/n");
        return malloc(size);
    }
private:
    int data;
};


int main()
{
    testClass* t = new testClass(1);
    //����һ��testClass���С�Ķ�̬�ڴ�
    char* buff = new char[sizeof(testClass)];
    memset(buff, 0, sizeof(buff));

    //placement newһ������
    testClass* myClass = new (buff)testClass(10);
    std::cout << myClass->getData() << std::endl;

    //ʹ����֮����������������ٶ����ÿգ�����buff��̬�ڴ��Դ��ڣ�
    myClass->~testClass();
    myClass = nullptr;

    //������ڴ����ٴη���һ������
    testClass* myClass2 = new (buff)testClass(12);
    std::cout << myClass2->getData() << std::endl;

    //�ͷŶ���
    myClass2->~testClass();
    myClass2 = nullptr;

    //�ͷŶ�̬�ڴ�
    delete[]buff;

    return 0;
}

