//#define LOGDEBUG(...) SPDLOG_LOGGER_CALL(m_logger,spdlog::level::level_enum::debug,__VA_ARGS__);
//#define LOGERR(...) SPDLOG_LOGGER_CALL(m_logger,spdlog::level::level_enum::err,__VA_ARGS__);
#define For(n) for(int index = 0;index < n;++index)
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<vector>
#include<thread>
//#include<output_Container.h>
//#include<spdlog/spdlog.h>
//#include<spdlog/logger.h>
//#include<spdlog/sinks/daily_file_sink.h>
using namespace std;
//std::shared_ptr<spdlog::logger> m_logger;

void f(int, int, int = 10);//Ĭ�ϲ���˳�����Ҳ�ᱨ��
void f(int, int = 8, int);
void f(int a = 6, int b, int c){
	cout << a << '\t' << b << '\t' << c << '\n';
}

void f2(int a, ...);//�䳤ʵ��
void f2(int, int, int = 10);
void f2(int, int = 8, int);
void f2(int a = 6, int b, int c) {
	cout << a << '\t' << b << '\t' << c << '\n';
}

//����ֵΪint�ĺ���ָ��
void f3(int(void));
void f3(int()) {

}

void f4(int(*)/*�����������βη������д��д*Ҳ�ã�дABCDҲ�ö���ʾͬһ������*/(int, int));
void f4(int(lumia)(int, int)) {
	cout << lumia(1, 2) << endl;
}

//���������޶��������Ǳ�ʾͬһ������
//��������ײ��޶���������
//void f5(const int*);//�����ж������
void f5(int* const);
void f5(int* volatile);
void f5(int* n) {
	cout << n << endl;
}

//��������ǡ�T �����顱��T ��δ֪�߽����顱����ô���ᱻ�滻�����͡�ָ�� T ��ָ�롱
//��������ָ���Ķ���ͬһ������
void f6(int[]);
void f6(int*);
void f6(int* const);
void f6(int[10]);
void f6(int* p) {
	cout << p << endl;
}

struct F
{
	auto operator()(){

	}
};

int main() {
	f();
	f2();
	f3([] {return 6; });
	f4([](int a, int b) {return a + b; });
	f5(nullptr);
	f6(nullptr);
	cout << boolalpha << is_same_v<void(int* const), void(int[10])> << endl;
	//thread t(F());//��ʱ�����е�F()�ᱻ���ɷ���ֵΪF�ĺ���ָ��
	thread t{ F() };//��{}��������
	system("pause");
	return 0;
}