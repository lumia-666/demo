#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

//��C++�У�ָ������鶼�������洢���ݵ��������ͣ�����������һЩ����
//
//�ڴ���䷽ʽ�������ڶ���ʱ����Ҫ�����ڴ�ռ䣬��ָ�����������Ҫʱ���ж�̬�ڴ���䡣
//
//�ڴ沼�֣��������ڴ�����һ���������ڴ�ռ䣬��ָ���ǵ���ָ�����������ָ������ݿ��Էֲ����ڴ������λ�á�
//
//������ʽ���������ֱ��ʹ���±�������Ԫ�أ���ָ����Ҫ�Ƚ������ٽ��з��ʡ����磬��������a��ָ��p��Ҫ����a�ĵ�i��Ԫ�أ�����ʹ��a[i]����Ҫ����p��ָ��ĵ�i��Ԫ�أ�����Ҫʹ��* (p + i)��
//
//���ͼ�飺�����ڶ���ʱ��Ҫָ��Ԫ�ص����ͺ���������������������ͼ���Ԫ��������顣��ָ��ֻ��Ҫ����ָ����������ͼ��ɣ��������������Ԫ�������ļ�飬���׷���Խ�����
//
//��С���ƣ�����Ĵ�С�ڶ���ʱ���Ѿ�ȷ�������ܸı䣻��ָ��û�д�С���ƣ�����ͨ��ָ�����������ʶ��Ԫ�ء�
//
//��Ҫע����ǣ�ָ�������֮�䲢������ȫ�����ģ�����֮�����һЩ��ϵ�����磬���������Կ�����һ��ָ��������Ԫ�ص�ָ�룬����ͨ������������������Ԫ�أ�ͬʱ��ָ��Ҳ���Ա���Ϊһ�����飬����ͨ��ָ�����������ʶ��Ԫ�ء����⣬ָ��Ҳ����������̬�ط�����ͷ������ڴ棬ʵ������Ķ�̬������������

#ifdef __cplusplus
extern "C" {
#endif
    void C_stack();
    void C_malloc();
    void CXX_stack();
    void CXX_new();
#ifdef __cplusplus
};
#endif

void test(char* buf)
{
    for (int i = 0; i < 2; ++i)
    {
        auto ptr = buf + 4 * i;
        auto tempValue = new char[4 + 1];
        memcpy(tempValue, ptr, 4);
        tempValue[4] = '\0';
        cout << tempValue << '\t';
    }
    cout << endl;
}

void C_stack() {
    printf("====== C stack ======\n");
    char str[2][4] = { {65,66,67,68}, {69,70,71,72} };
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 4; j++) {
            printf("[%c]%p\t", str[i][j], &str[i][j]);
        }
        printf("\n");
    }
    printf("=====================\n\n");
}
void C_malloc() {
    printf("====== C malloc ======\n");

    char** str = (char**)malloc(2 * sizeof(char*));

    for (int i = 0; i < 2; i++)
        str[i] = (char*)malloc(4 * sizeof(char));
    char s = 'A';
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 4; j++) {
            str[i][j] = s++;
            printf("[%c]%p\t", str[i][j], &str[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < 2; i++)
        free(str[i]);
    free(str);
    printf("====================\n\n");
}


void CXX_stack() {
    cout << "====== Cpp stack ======" << endl;
    char str[2][4] = { {65,66,67,68}, {69,70,71,72} };
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 4; j++) {
            cout << "[" << str[i][j] << "]" << (void*)&str[i][j] << "\t";
        }
        cout << endl;
    }
    //��ǡǡ˵���������ָ����������ȫ���������ݽṹ
    //char[][]��ʾһ����ά�ַ����飬�����ڴ�����һ���������ڴ�ռ䣬ÿ��Ԫ�ض���һ���ַ����飬��С���ǹ̶��ġ�
    //char**��ʾһ��ָ���ַ�ָ���ָ�룬�����ڴ�����һ��ָ�����飬ÿ��Ԫ�ض���һ��ָ���ַ������ָ��
    //�����ָ�뿴����λ�ţ�char**���Կ�����λ�ŵ����飬��ҿ�����������������1��3��5��8
    test((char*)str);//ջ�ϵĶ�ά���������������ڴ�����ʽ�洢�ģ�������������ڵ�һ�е�һ��Ԫ�صĵ�ַ��������Ϊ��������������������Ԫ�صĵ�ַ
    cout << "======================" << endl << endl;
}
void CXX_new() {
    cout << "====== Cpp new ======" << endl;

    char** str = new char* [2];
    for (int i = 0; i < 2; i++)
        str[i] = new char[4];
    char s = 'A';
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 4; j++) {
            str[i][j] = s++;
            cout << "[" << str[i][j] << "]" << (void*)&str[i][j] << "\t";
        }
        cout << endl;
    }
    cout << (void*)str << endl;//��C++�У����ϵĶ�ά��������ָ���������ʽ�洢�ģ�����������������ڵ�һ�е�һ��Ԫ�صĵ�ַ������ָ���һ��Ԫ�����ڵ�ָ���ָ��
    cout << (void*)*str << endl;//str��һ��ָ��char����ָ���ָ�룬���洢�˶�̬����Ķ�ά����ĵ�ַ�����ڸ���������ָ���������ʽ�洢�ģ����strָ����ǵ�һ�е�ָ�룬������������׵�ַ��
    test((char*)*str);
    for (int i = 0; i < 2; i++)
        delete[]str[i];
    delete str;
    cout << "====================" << endl;
}

void test2()
{
    auto arr = new int[3];
    for (int i = 0; i < 3; ++i)
    {
        arr[i] = i + 8;
    }
    int a = 0;
    memcpy(&a, (char*)arr + 8, 4);

}

int main() {
    test2();
    C_stack();
    C_malloc();
    CXX_stack();
    CXX_new();
    return 0;
}

