#pragma once
#include <unordered_map>

namespace RTDB
{
    namespace ApiCpp
    {
        class History;
    }
}

class DBAPI_DLLENTRY RTDB::ApiCpp::History
{
public:
    History(void);
    ~History(void);
	static int32_t GetDoubleValueByTagID(
		int32_t connecter,
		int32_t tagID,
		FILETIME startTime,
		FILETIME endTime,
		std::vector <TagDoubleData> &tagDataList);
    static int32_t GetValueByTagID(
        int32_t connecter, 
        int32_t tagID, 
        FILETIME startTime, 
        FILETIME endTime, 
		std::vector <TagData> &tagDataList);

	/**
	 *	��ȡÿ��ʱ���Ƭ�Ŀ�ʼʱ����ֵ
	 *	connecter ���ݿ����Ӿ��
	 *	tagID ��ǩ��ID
	 *	startTime ��ʼʱ�䣨UTC��
	 *	endTime ����ʱ�䣨UTC��
	 *	period ʱ���Ƭ�����룩
	 *	tagDatas ���
	 */
	static int32_t GetValueByPeriod(
		int32_t connecter,
		int32_t tagID,
		FILETIME startTime,
		FILETIME endTime,
		int64_t period, 
		std::vector<TagData> &tagDatas);


	/**
	*	��ȡÿ��ʱ���Ƭ�Ŀ�ʼʱ����ֵ
	*	connecter ���ݿ����Ӿ��
	*	tagID ��ǩ��ID
	*	startTime ��ʼʱ�䣨UTC��
	*	endTime ����ʱ�䣨UTC��
	*	period ʱ���Ƭ�����룩
	*	tagDatas ���
	*/
	static int32_t GetValueByPeriod(
		int32_t connecter,
		int32_t tagID,
		FILETIME startTime,
		FILETIME endTime,
		int64_t period,
		std::vector<TagDoubleData> &tagDatas);
	/**
	*	��ȡÿ��ʱ���Ƭ�Ŀ�ʼʱ����ֵ
	*	connecter ���ݿ����Ӿ��
	*	tagName ��ǩ������
	*	startTime ��ʼʱ�䣨UTC��
	*	endTime ����ʱ�䣨UTC��
	*	period ʱ���Ƭ�����룩
	*	tagDatas ���
	*/
	static int32_t GetValueByPeriod(
		int32_t connecter,
		const std::wstring& tagName,
		FILETIME startTime,
		FILETIME endTime,
		int64_t period,
		std::vector<TagData> &tagDatas);

    static int32_t GetValueByTagIDEx(
        int32_t connecter, 
        int32_t tagID, 
        FILETIME startTime, 
        FILETIME endTime, 
        std::vector <TagDataEx> &tagDataList);

    static int32_t GetValueByTagIDAtTime(
        int32_t connecter, 
        int32_t tagID, 
        FILETIME timestamp,
        int32_t mode,
        TagData &tagData);

	static int32_t GetValueByTagIDAtTime(
		int32_t connecter,
		int32_t tagID,
		FILETIME timestamp,
		int32_t mode,
		TagDoubleData &tagData);

	static int32_t EnableSpeedUp(int32_t connecter, bool enable);

	static int GetNValues(
		int32_t connecter, 
		int tagID, 
		FILETIME startTime, 
		FILETIME endTime, 
		uint32_t valueNum, 
		std::vector<TagData> &values);

	static int GetNValues(
		int32_t connecter,
		int tagID,
		FILETIME startTime,
		FILETIME endTime,
		uint32_t valueNum,
		std::vector<TagDoubleData> &values);

	/**
	 *	period�Ǻ���Ϊ��λ
	 */
    static int32_t GetValueByTagIDByStatistics(
        int32_t connecter, 
        int32_t tagID, 
        FILETIME startTime,
        FILETIME endTime,
        int64_t period,
        int32_t mode,
        std::vector <TagData> &tagDataList);

	static int32_t GetStatistics(
		int32_t connecter,
		int32_t tagID,
		FILETIME startTime,
		FILETIME endTime,
		uint64_t period,
		uint32_t mode,
		std::unordered_map<uint32_t, std::vector<TagData>> &tagDataList);

    static int32_t UpdateValueByTagID(
		int32_t connecter,
		int32_t tagID,
		TagData &tagData);

	static int32_t UpdateHistoryValues(
		int32_t connecter,
		const std::vector<int32_t> &tagIDs,
		const std::vector<TagData> &tagDatas,
		std::vector<int32_t> &resutlts);

    static int32_t DeleteValueByTagID(
		int32_t connecter,
		int32_t tagID,
		FILETIME startTime,
		FILETIME endTime);

	static int32_t DeleteHistoryValues(
		int32_t connecter,
		const std::vector<int32_t> &tagIDs,
		const std::vector<FILETIME> &tagTimes,
		std::vector<int32_t> &resutlts);

	static int32_t GetCurveByZone(
		int32_t connecter, 
		int32_t tagID, 
		FILETIME startTime, 
		FILETIME endTime, 
		int32_t zone, 
		std::vector <TagData> &tagDataList );

	static int32_t SetHistoryValues(
		int32_t connecter,
		int32_t tagID,
		const std::vector<TagData> &tagDatas);

	static int32_t SetHistoryValues(
		int32_t connecter,
		int32_t tagID,
		const std::vector<TagDoubleData> &tagDatas);
};
