#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <iostream>
using namespace std;
class String1
{
public:
	String1(const char*str = "")//Ĭ�Ϲ������//���Բ��ò���
	{
		m_str = new char[strlen(str) + 1];
		strcpy(m_str, str);          
		cout << "create String" << endl;
	}
	// ���磺String1 str3(str1); ���Ǽ��翽�����캯�����������������͵Ļ�,��ʱ�����ݹ�������캯��
	String1(const String1 &s) {
		m_str = new char[strlen(s.m_str) + 1];         
		strcpy(m_str, s.m_str);        
		cout << "copy String" << endl;
	}
	String1& operator=(const String1& s) {
		delete[] m_str;
		m_str = new char[strlen(s.m_str) + 1];
		strcpy(m_str, s.m_str);        
		cout << "=====" << endl;             
		return *this;
	}
	~String1()
	{
		delete[]m_str;       
		m_str = nullptr;
	}   

	char* m_str;

};
void main()
{
	String1 str1("a");
	String1 str2("b");
	String1 str3(str1);
	String1 str4 = str2;//ִ�п�������

	//����ʱ������ֵ������ֵ���ݻ���Ϊ������ʱ�������һ�ο������죬ͬ��������ֵ����Ϊ����Ҳ�ᴥ����������
	str4 = str1;
}