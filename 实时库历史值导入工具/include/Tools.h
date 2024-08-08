#ifndef _TOOLS_H_
#define _TOOLS_H_
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif 

//#ifdef TOOLS_EXPORTS
//#define TOOLS_EXPORTS __declspec(dllexport)
//#else 
//#define  TOOLS_EXPORTS __declspec(dllimport)
//#endif // LED_EXPORTS

#include <fstream>
#include <vector>
#include <string>
#include <time.h>
#include <windows.h>
namespace Tools
{
	inline time_t StrToTime(const std::string& str)
	{
		char* ptr = (char*)str.c_str();
		tm tmTemp;
		int year, month, day, hour, minute, second = 0;
		auto ret = sscanf_s(ptr, "%d/%d/%d %d:%d:%d", &month, &day, &year, &hour, &minute, &second);
		tmTemp.tm_year = year - 1900;
		tmTemp.tm_mon = month - 1;
		tmTemp.tm_mday = day;
		tmTemp.tm_hour = hour;
		tmTemp.tm_min = minute;
		tmTemp.tm_sec = second;
		tmTemp.tm_isdst = 0;
		time_t tTemp = mktime(&tmTemp);
		return tTemp;
	}

	inline void Time_tToFileTime(time_t t, FILETIME *ft)
	{
		LONGLONG ll = Int32x32To64(t, 10000000) + 116444736000000000;
		ft->dwLowDateTime = (DWORD)ll;
		ft->dwHighDateTime = (DWORD)(ll >> 32);
	}

	inline void  FileTimeToTime_t(FILETIME  ft, time_t* t)
	{
		LONGLONG  ll;
		ULARGE_INTEGER ui;
		ui.LowPart = ft.dwLowDateTime;
		ui.HighPart = ft.dwHighDateTime;
		//ll = ft.dwHighDateTime << 32 + ft.dwLowDateTime;  //��һ���ǲ��Ƕ����
		*t = ((LONGLONG)(ui.QuadPart - 116444736000000000) / 10000000);
		//��ui.QuadPart����������ULONGLONGǿ��ת��Ϊtime_t��LONGLONG��������
	}

	inline std::string Time_tToString(time_t time)
	{
		tm *tm_ = localtime(&time);                // ��time_t��ʽת��Ϊtm�ṹ��
		if (tm_ == nullptr)
		{
			return "0";
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
		sprintf(s, "%s/%s/%s %s:%s:%s", dayStr, monthStr, yearStr, hourStr, minuteStr, secondStr);// ��������ʱ����ϲ���
		std::string str(s);                             // ����string����������������ʱ��char*������Ϊ���캯���Ĳ������롣
		return str;                                // ����ת������ʱ����string������
	}

	inline void SplitString(const std::string& s, std::vector<std::string> &v, const std::string& c)
	{
		std::string::size_type pos1, pos2;
		pos2 = s.find(c);
		pos1 = 0;

		while (std::string::npos != pos2)
		{
			auto it = v.end();
			v.push_back(s.substr(pos1, pos2 - pos1));

			pos1 = pos2 + c.size();
			pos2 = s.find(c, pos1);
		}
		if (pos1 != s.length())
			v.push_back(s.substr(pos1));
	}
	template<typename T>
	inline void GetFiles(const std::string&filePath, T &fileNames)
	{

		std::string pointstr = "dir " + filePath + " /B > ./fname.txt";
		//const char *a =("dir %s /B > D:\\fname.txt", pointstr.c_str());
		system(pointstr.c_str());
		std::ifstream fReadFName("./fname.txt");
		std::string tName;
		while (getline(fReadFName, tName))
		{
			auto it = fileNames.end();
			fileNames.insert(it, tName);
		}
	}
	//LOADOMETER_API double GetWeight(int &id, int &orgNo);
};
#endif