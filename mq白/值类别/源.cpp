
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

int f() {
	return 6;
}

void f2(int&&) {

}

void f3(const int&) {

}

int main() {
	//��ֵ���õ������ǽ�һ����ֵ������ֱֵ��ת��Ϊ��ֵ����C++�ͨ����������ֵ�Ժ󣬱��뽫��ֵ������һ����ֵ���ܱ���
	//������������������Դ���������ο������������������Դ��ģ���ֱ�ӽ���ֵת��Ϊ��ֵ�����ʡ��Щ��ģ�
	//��ʱ������ֵת��Ϊ��ֵ�Ĳ�����Ϊ�ƶ�����
	int&& p = f();//ֵ����Ǳ��ʽ�ķ��࣬f()������ʽֵ�������ֵ���������ǿ��Դ���һ����ֵ���ð󶨵�����ֵ��
	int p = f();
	//int& p = f();//error���ǳ�������ֵ�����õĳ�ʼֵ����Ϊ��ֵ��������һ����ֵ���ð�һ����ֵ
	const int& p2 = f();//������ֵ���ÿ��Խ�����ֵ������ֵ����ֵ��

	//decltype����ݱ��ʽ��ֵ����Ƶ���ͬ������
	//a) ��� ���ʽ ��ֵ�������ֵ������ decltype ���� T&&��
	//b) ��� ���ʽ ��ֵ�������ֵ������ decltype ���� T& ��
	//c) ��� ���ʽ ��ֵ����Ǵ���ֵ������ decltype ���� T��
	using T = decltype((42));//�˴��Ƶ�42Ϊint��T��,������ֵ
	using T2 = decltype((f())); //�˴��Ƶ�42Ϊint��T��������ֵ
	int a = 0;
	using T3 = decltype((a));//�˴��Ƶ�aΪint&��T&������ֵ
	using T4 = decltype((int&&)(a));//�˴��Ƶ�aΪint&&��T&&������ֵ
	using T5 = decltype(std::move(a));//�˴��Ƶ�aΪint&&��T&&������ֵ
	//f2(a);//�޷�����ֵ���ð󶨵���ֵ
	//f2(p);//�޷�����ֵ���ð󶨵���ֵ

	f3(a);
	f3(p);
	f3(6);
	f3(std::move(a));

	system("pause");
	return 0;
}