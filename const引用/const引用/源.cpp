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
int main() {
	//1��const���ÿɶ����ɸģ���󶨶����Ƿ�Ϊconst�޹أ���const���ÿɶ��ɸģ�ֻ�����const�����
	int val = 1024;
	const int& ir = val;
	val++;//������Ȼ����ͨ��valֱ�Ӹı���ֵ
	ir++;//ͨ��ir���ı�val��ֵ������ʱ�����

	const int ival = 1024;
	const int& refVal = ival; // ok: both reference and object are const
	int& ref2 = ival;            // ��const����ֻ�����const�����

	//2����const����ֻ�ܰ󶨵��������ͬ���͵Ķ���const��������԰󶨵���ͬ����ص����͵Ķ����󶨵���ֵ��
	//ͬʱconst���ÿ��Գ�ʼ��Ϊ��ͬ���͵Ķ�����߳�ʼ��Ϊ��ֵ��������ֵ����
	//����ԭ���Ǳ�����Ϊ��ʵ�����ã���������һ����ʱ���󣬽��ö����ֵ������ʱ�����У�
	//����ʵ����ָ��ö��󣨶Ը����õĲ������ǶԸ���ʱ����Ĳ����������û����ܷ�������
	int i = 42;
	// legal for const references only
	const int& r = 42;//��ʼ��Ϊ��ֵ
	const int& r2 = r + i;//ͬ���ĳ�ʼ�����ڷ�const����ȴ�ǲ��Ϸ��ģ����һᵼ�±���ʱ����
	double dval = 3.14;
	const int& ri = dval;//��ͬ���Ͷ���

	//3.const���úͷ�const�������ڴ��еĶԱ�
	//����const���ã�

	const int t = 9;
	const int& k = t;
	cout << &k << endl;//0012FF6C
	cout << &t << endl;//0012FF74

	//�����const���ã�
	int t1 = 9;
	int& k1 = t1;
	cout << &k1 << endl;//0012FF74
	cout << &t1 << endl;//0012FF74
	//ԭ����const����������һ���û�����������ʱ����
	system("pause");
	return 0;
}