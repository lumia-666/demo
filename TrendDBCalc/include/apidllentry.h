#ifndef LRAPI_DLLENTRY_H
#define LRAPI_DLLENTRY_H

////////////////////////////////////////////////////////////////////////////////
//
// �ļ����ƣ�dllentry.h
// �ļ���ʶ��
// ժҪ��LiRTDBApiģ�飭dll���뵼��
//
// �汾��1.0
// ���ߣ���εܿ
// ���ڣ�2011.3.11
//
////////////////////////////////////////////////////////////////////////////////

#ifndef RTDB_APICLR
#ifdef RTDBAPI_EXPORTS
#define DBAPI_DLLENTRY    __declspec(dllexport)
#else
#define DBAPI_DLLENTRY    __declspec(dllimport)
#endif // LIRTDBAPI_EXPORTS
#endif // LIRTDB_APICLR

#endif // LRAPI_DLLENTRY_H
