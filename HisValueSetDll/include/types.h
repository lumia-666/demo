#pragma once
#include <stdint.h>
#include <string>


#ifdef _WIN32
#include <WinSock2.h>
#endif // _WIN32


// SystemTime��ӦWindows�е�SystemTime�ṹ
struct SystemTime
{
	uint16_t year;					// �� ��1970~30827
	uint16_t month;					// �� 1~12
	uint16_t day;					// �� 1~31
	uint16_t hour;					// ʱ 0~23
	uint16_t minute;				// �� 0~59
	uint16_t second;				// �� 0~59
	uint16_t milliseconds;			// ���� 0~999
};

// FileTime��ӦWindows�е�FileTime�ṹ
// ��ʱ��Ϊ��԰1601��1��1��0ʱ������ĿǰΪֹ��ȥ��ʱ�䳤�ȣ�
// �䵥λΪ100���룬��1��=10^7������
struct FileTime
{
	uint32_t lowTime;				// ��32λʱ��
	uint32_t highTime;				// ��32Ϊʱ��
};

typedef uint8_t			byte_t;

typedef uint32_t           TAGID_T;
typedef TAGID_T *       LP_TAGID_T;

typedef uint32_t            TAGTYPE_T;
typedef TAGTYPE_T *      LP_TAGTYPE_T;

typedef uint64_t          RTDBTIME_T;
typedef RTDBTIME_T *     LP_RTDBTIME_T;
typedef const RTDBTIME_T * LPCRTDBTIME_T;
//using LPCRTDBTIME_T = const RTDBTIME_T *;

typedef int32_t           STATUS_T;
typedef STATUS_T *   LP_STATUS_T;
typedef const STATUS_T * LPCSTATUS_T;
//using LPCSTATUS_T = const STATUS_T *;

typedef int8_t            VALUE_INT8;
typedef VALUE_INT8 *    LP_VALUE_INT8;

typedef int16_t           VALUE_INT16;
typedef VALUE_INT16 *   LP_VALUE_INT16;

typedef int32_t           VALUE_INT32;
typedef VALUE_INT32 *   LP_VALUE_INT32;

typedef int64_t           VALUE_INT64;
typedef VALUE_INT64 *   LP_VALUE_INT64;

typedef float         VALUE_FLT32;
typedef VALUE_FLT32 *   LP_VALUE_FLT32;

typedef double         VALUE_FLT64;
typedef VALUE_FLT64 *   LP_VALUE_FLT64;

namespace port
{
#ifdef  _WIN32 // _WIN32
	typedef wchar_t			char16;
	typedef int32_t			char32;
	typedef std::basic_string<char32> u32string;
	typedef std::wstring	u16string;

	struct Socket
	{
		SOCKET sock;
		Socket()
			: sock(-1)
		{}
	};
#else // linux
	typedef int16_t			char16;
	typedef wchar_t			char32;
	typedef std::wstring u32string;
	typedef std::basic_string<char16> u16string;
	struct Socket
	{
		int sock;
		Socket()
			: sock(-1)
		{}
	};
#endif // _WIN32
} // port
