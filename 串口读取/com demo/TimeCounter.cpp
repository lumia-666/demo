#include "TimeCounter.h"

#include <cstdint>
#include <ctime>
#include <Windows.h>


TimeCounter::TimeCounter()
	: frequency_(1)
	, start_(0)
	, end_(0)
{
	LARGE_INTEGER frequency;    // ÿ���ӵ�Ƶ�� 
	if (QueryPerformanceFrequency(&frequency))
	{
		frequency_ = frequency.QuadPart;
	}
	Start();
}


TimeCounter::~TimeCounter()
{

}

void TimeCounter::Start()
{
	LARGE_INTEGER timeStart;    //��ʼʱ��  
	if (QueryPerformanceCounter(&timeStart))
	{
		start_ = timeStart.QuadPart;
	}
	else
	{
		start_ = time(nullptr);
	}
}

uint64_t TimeCounter::End()
{
	LARGE_INTEGER timeEnd;      //����ʱ��  
	if (QueryPerformanceCounter(&timeEnd))
	{
		end_ = timeEnd.QuadPart;
	}
	else
	{
		end_ = time(nullptr);
	}

	// frequency_��ÿ���ӵĴ�����end_ - start_�õ��ܴ��� ����frequency_ �õ�����������1000������
	auto elapsed = uint64_t(((end_ - start_) * 1.0 / frequency_) * 1000);
	return elapsed;
}
