
//#define LOGDEBUG(...) SPDLOG_LOGGER_CALL(m_logger,spdlog::level::level_enum::debug,__VA_ARGS__);
//#define LOGERR(...) SPDLOG_LOGGER_CALL(m_logger,spdlog::level::level_enum::err,__VA_ARGS__);
#define For(n) for(int index = 0;index < n;++index)
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<vector>
//#include<output_Container.h>
//#include<spdlog/spdlog.h>
//#include<spdlog/logger.h>
//#include<spdlog/sinks/daily_file_sink.h>
using namespace std;
//std::shared_ptr<spdlog::logger> m_logger;


class MyString
{
public:
	MyString(const char* str = NULL); // ��ͨ���캯��
	MyString(const MyString& other); // �������캯��
	~MyString(void); // ��������
	MyString& operator = (const MyString& other); // ��ֵ����
private:
	char* m_data; // ���ڱ����ַ���
};

int main() {

	system("pause");
	return 0;
}

MyString::MyString(const char* str)
{
	if (str != nullptr) {
		m_data = new char[strlen(str) + 1];
		strcpy(m_data, str);
	}
	//else
	//{
	//	m_data = new char[1];
	//	*m_data = '\0';
	//}
}

MyString& MyString::operator = (const MyString& other) {
	//�������Ҹ�ֵ
	if (this != &other) {
		delete[] m_data;
		m_data = new char[strlen(other.m_data) + 1];
		strcpy(m_data, other.m_data);
	}
	return *this;
}


MyString::MyString(const MyString& other)
{
	m_data = new char[strlen(other.m_data) + 1];
	strcpy(m_data, other.m_data);
}


MyString::~MyString(void)
{
	if (m_data != nullptr) {
		delete[] m_data;
		m_data = nullptr;
	}
}


class String
{
public:
	String(const char* str = NULL); // ��ͨ���캯��
	String(const String& other); // �������캯��
	~String(void); // ��������
	String& operator = (const String & other); // ��ֵ����
private:
	char* m_data; // ���ڱ����ַ���
};

#include <stdio.h>
#include <stdlib.h>

class SimpleObject
{
public:
	int n;
	SimpleObject(int n)
	{
		this->n = n;
		buffer = new char[n];
		printf("SimpleObject Created\n");
	}
	virtual ~SimpleObject()
	{
		if (buffer != NULL)
		{
			delete buffer;
			printf("SimpleObject Destroyed\n");
		}
	}
private:
	char* buffer;
};

int main()
{
	SimpleObject a(10);
	SimpleObject b = a;
	return 0;
}
class B;
class A {
private:shared_ptr<B>data;
};
class B {
private:shared_ptr<A>data;
};
