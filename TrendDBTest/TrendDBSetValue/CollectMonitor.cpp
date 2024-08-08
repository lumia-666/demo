
#include "CollectMonitor.h"
#include <fstream>
#include "minidump.h"

CollectMonitor::~CollectMonitor()
{
}

void SplitStr(const std::string& str, std::vector<std::string>& tokens, const std::string delim = "_")
{
	tokens.clear();

	auto start = str.find_first_not_of(delim, 0);       // �ָ���ַ����ĵ�һ���ַ�
	auto position = str.find_first_of(delim, start);    // �ָ�����λ��
	while (position != std::string::npos || start != std::string::npos) {
		// [start, position) Ϊ�ָ��������ַ���
		tokens.emplace_back(std::move(str.substr(start, position - start)));
		start = str.find_first_not_of(delim, position);
		position = str.find_first_of(delim, start);
	}
}

void  FileTimeToTime_t(FILETIME  ft, time_t* t)
{
	LONGLONG  ll;
	ULARGE_INTEGER ui;
	ui.LowPart = ft.dwLowDateTime;
	ui.HighPart = ft.dwHighDateTime;
	//ll = ft.dwHighDateTime << 32 + ft.dwLowDateTime;  //��һ���ǲ��Ƕ����
	*t = ((LONGLONG)(ui.QuadPart - 116444736000000000) / 10000000);
	//��ui.QuadPart����������ULONGLONGǿ��ת��Ϊtime_t��LONGLONG��������
}

std::string DatetimeToString(time_t time)
{
	tm *tm_ = localtime(&time);                // ��time_t��ʽת��Ϊtm�ṹ��
	if (tm_ == nullptr)
	{
		return "0/0/0 0:0:0";
	}
	int year, month, day, hour, minute, second;// ����ʱ��ĸ���int��ʱ������
	year = tm_->tm_year + 1900;                // ��ʱ�������꣬����tm�ṹ��洢���Ǵ�1900�꿪ʼ��ʱ�䣬������ʱ����intΪtm_year����1900��
	month = tm_->tm_mon + 1;                   // ��ʱ�������£�����tm�ṹ����·ݴ洢��ΧΪ0-11��������ʱ����intΪtm_mon����1��
	day = tm_->tm_mday;                        // ��ʱ�������ա�
	hour = tm_->tm_hour;                       // ��ʱ������ʱ��
	minute = tm_->tm_min;                      // ��ʱ�������֡�
	second = tm_->tm_sec;                      // ��ʱ�������롣
	char yearStr[5], monthStr[3], dayStr[3], hourStr[3], minuteStr[3], secondStr[3];// ����ʱ��ĸ���char*������
	sprintf(yearStr, "%d", year);              // �ꡣ
	sprintf(monthStr, "%d", month);            // �¡�
	sprintf(dayStr, "%d", day);                // �ա�
	sprintf(hourStr, "%d", hour);              // ʱ��
	sprintf(minuteStr, "%d", minute);          // �֡�
	if (minuteStr[1] == '\0')                  // �����Ϊһλ����5������Ҫת���ַ���Ϊ��λ����05��
	{
		minuteStr[2] = '\0';
		minuteStr[1] = minuteStr[0];
		minuteStr[0] = '0';
	}
	sprintf(secondStr, "%d", second);          // �롣
	if (secondStr[1] == '\0')                  // �����Ϊһλ����5������Ҫת���ַ���Ϊ��λ����05��
	{
		secondStr[2] = '\0';
		secondStr[1] = secondStr[0];
		secondStr[0] = '0';
	}
	if (monthStr[1] == '\0')                  // �����Ϊһλ����5������Ҫת���ַ���Ϊ��λ����05��
	{
		monthStr[2] = '\0';
		monthStr[1] = monthStr[0];
		monthStr[0] = '0';
	}
	if (dayStr[1] == '\0')                  // �����Ϊһλ����5������Ҫת���ַ���Ϊ��λ����05��
	{
		dayStr[2] = '\0';
		dayStr[1] = dayStr[0];
		dayStr[0] = '0';
	}
	if (hourStr[1] == '\0')                  // �����Ϊһλ����5������Ҫת���ַ���Ϊ��λ����05��
	{
		hourStr[2] = '\0';
		hourStr[1] = hourStr[0];
		hourStr[0] = '0';
	}
	char s[20];                                // ����������ʱ��char*������
	sprintf(s, "%s-%s-%s %s:%s:%s", yearStr, monthStr, dayStr, hourStr, minuteStr, secondStr);// ��������ʱ����ϲ���
	std::string str(s);                             // ����string����������������ʱ��char*������Ϊ���캯���Ĳ������롣
	return str + ".000";                                // ����ת������ʱ����string������
}

int CollectMonitor::Init()
{
	Minidump::startMonitering("");
	auto path = "./log.txt";
	spdlog::set_pattern("[%H:%M:%S %z] [source %s] [line %#] [thread %t] %v");
	m_logger = spdlog::daily_logger_mt(" ", path, 0, 0);
	m_logger->set_level(static_cast<spdlog::level::level_enum>(1));
	spdlog::flush_every(std::chrono::seconds(1));
	ReadTag();
	tagID_.dbID = 103;
	tagID_.tagID = 8;
	startTime_ = time(NULL) - 3600*29;
	endTime_ = time(NULL) + 3600*15;
	m_dbInfoGt.addr = L"192.168.1.227";
	if (m_dbApiGt.Connect(m_dbInfoGt) < 0)
	{
		LOGINFO("connect gt rtdb error");
		std::cout << "connect rtdb error" << std::endl;
		return -1;
	}
	return 0;
}

int CollectMonitor::Run()
{
	FILETIME fStart;
	FILETIME fEnd;
	Time_tToFileTime(startTime_, &fStart);
	Time_tToFileTime(endTime_, &fEnd);
	std::ofstream ofs("./data.txt", std::ios::trunc);
	while (true)
	{
		if (!m_dbApiGt.Connected())
		{
			LOGINFO("gt Rtdb Disconnect!");
			std::cout << "Rtdb Disconnect!" << std::endl;
			if (m_dbApiGt.Connect(m_dbInfoGt) < 0)
			{
				LOGINFO("gt Rtdb reconnect fail!");
				std::cout << "Rtdb reconnect fail!" << std::endl;
				continue;
			}
		}
		std::vector<TagData> tagDataList;
		int ret = m_dbApiGt.GetValueByPeriod(tagID_, fStart, fEnd, 3600*1000,tagDataList);
		for (auto data : tagDataList)
		{
			time_t tTemp;
			FileTimeToTime_t(data.timestamp, &tTemp);
			ofs << DatetimeToString(tTemp) << "\t" << data.value << std::endl;
		}
		Sleep(1000);
	}

	return 0;
}

int CollectMonitor::ReadCfg()
{
	std::ifstream file("./config.ini");
	if (!file)
	{
		WritePrivateProfileString("Config", "RtdbAddrGt", "127.0.0.1", "./config.ini");
	}
	char* lpPath = new char[MAX_PATH];
	char* RtdbAddr = new char[100];
	strcpy_s(lpPath, MAX_PATH, "./config.ini");
	GetPrivateProfileString("Config", "RtdbAddr", "", RtdbAddr, 100, lpPath);
	delete[] lpPath;
	m_dbInfoGt.addr = StringToWstring(RtdbAddr);
	m_dbInfoGt.port = 7000;
	delete[] RtdbAddr;
	return 0;
}

int CollectMonitor::ReadTag()
{
	std::ifstream ifs("./tag.txt");
	if (!ifs)
	{
		LOGINFO("can not find tag.txt");
		return -1;
	}
	std::string lineStr;
	TAGID tag;
	tag.dbID = 101;
	while (std::getline(ifs, lineStr))
	{
		//tagID_ = 
	}
	return 0;
}

std::wstring inline CollectMonitor::StringToWstring(const std::string str)
{
	unsigned len = str.size() * 2;// Ԥ���ֽ���
	setlocale(LC_CTYPE, "");     //������ô˺���
	wchar_t *p = new wchar_t[len];// ����һ���ڴ���ת������ַ���
	mbstowcs(p, str.c_str(), len);// ת��
	std::wstring str1(p);
	delete[] p;// �ͷ�������ڴ�
	return str1;
}

inline void CollectMonitor::Time_tToFileTime(time_t t, FILETIME *ft)
{
	LONGLONG ll = Int32x32To64(t, 10000000) + 116444736000000000;
	ft->dwLowDateTime = (DWORD)ll;
	ft->dwHighDateTime = (DWORD)(ll >> 32);
}
