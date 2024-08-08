#ifndef LIRTDB_DEFINE_H
#define LIRTDB_DEFINE_H

// ����Ȩ����
#define  RTDB_SOFTLIMIT

// ���ð汾����
//#define LIRTDB_LIMIT
//#define LIRTDB_LIMIT_RUNTIME_CONTINUE

#include <Windows.h>
#include <cstdint>
#include <string>
#include <map>

const int RTDB_TAG_NUM(100000);
const int RTDB_GROUP_NUM(200);
const int RTDB_APPLOCK_NUM(2400);
//const INT LIRTDB_SYSTEMLOCK_NUM(LIRTDB_APPLOCK_NUM + LIRTDB_TAG_NUM);

const uint32_t RTDB_CACHE_FILE_MINLEN = 1;
const uint32_t RTDB_CACHE_FILE_MAXLEN = 100;
const uint32_t RTDB_CACHE_MEM_MINLEN = 1;
const uint32_t RTDB_CACHE_MEM_MAXLEN = 16;
const uint32_t RTDB_CACHE_DATA_MINLEN = 1;
const uint32_t RTDB_CACHE_DATA_MAXLEN = 128;
const uint32_t RTDB_CACHE_DATA_MINNUM = 10;

const uint32_t RTDB_CACHE_FILELEN_UNIT = 1024 * 1024;
const uint32_t RTDB_CACHE_MEMLEN_UNIT = 64 * 1024;
const uint32_t RTDB_CACHE_DATALEN_UNIT = 512;

const uint32_t RTDB_CACHE_SYNCFILE_MAXLEN = 64 * 1024;
const uint32_t RTDB_CACHE_SYNCTAG_MAXCNT = 10000;

const uint32_t MAXLEN_DBNAME = 32;
const uint32_t MAXLEN_GROUP = 60;
const uint32_t MAXLEN_TAGNAME = 120;
const uint32_t MAXLEN_TAGDESC = 200;
const uint32_t MAXLEN_TAGUNIT = 20;
const uint32_t MAXLEN_TAGTYPE = 1;
const uint32_t MAXLEN_TAGSOURCE = 20;
const uint32_t MAXLEN_TAGDESCEX = 99;
const uint32_t MAXLEN_TAGEXA = 49;
const uint32_t MAXLEN_TAGEXB = 49;
const uint32_t MAXLEN_TAGSCRIPT = 3072;

LPCWSTR const RTDB_SERVICE_MUTEX_NAME(L"Global\\LUCULENT_LIRTDB_SYSTEM_RUN_STATUS");
LPCWSTR const RTDB_VERSION_FILENAME(L"version.dat");
LPCWSTR const RTDB_HISTEXE_FILENAME(L"TrendDB_HIS.exe");
LPCWSTR const RTDB_DATAEXE_FILENAME(L"TrendDB_FUN.exe");
LPCWSTR const RTDB_MAINEXE_FILENAME(L"TrendDB_MAIN.exe");
LPCWSTR const RTDB_BACKUPEXE_FILENAME(L"TrendDB_Backup.exe");
LPCWSTR const RTDB_COMINTERFACE_FILENAME(L"TrendDBACCESS.dll");

const std::string RTDB_FILENAME_DBCFG = "TrendDB.ini";
const std::string RTDB_FILENAME_SYSCFG = "DBConfig.ini";

LPCWSTR const RTDB_SHMEM_NAME_SYSCONFIG(L"Global\\LUCULENT_RTDB_SYSCONFIG");
LPCWSTR const RTDB_SHMEM_NAME_SYSSTATUS(L"Global\\LUCULENT_RTDB_SYSSTATUS");
LPCWSTR const RTDB_SHMEM_NAME_GRPCONFIG(L"Global\\LUCULENT_RTDB_GROUPCONFIG");
LPCWSTR const RTDB_SHMEM_NAME_TAGCONFIG(L"Global\\LUCULENT_RTDB_TAGCONFIG");
LPCWSTR const RTDB_SHMEM_NAME_TAGCONFIGEX(L"Global\\LUCULENT_RTDB_TAGCONFIGEX");
LPCWSTR const RTDB_SHMEM_NAME_TAGHASH(L"Global\\LUCULENT_RTDB_TAGHASH");
LPCWSTR const RTDB_SHMEM_NAME_CACHEINDEX(L"Global\\LUCULENT_RTDB_CACHEINDEX");
LPCWSTR const RTDB_SHMEM_NAME_CACHESYNC(L"Global\\LUCULENT_RTDB_CACHESYNC");
LPCWSTR const RTDB_SHMEM_NAME_ALARM(L"Global\\LUCULENT_RTDB_ALARM");
LPCWSTR const RTDB_SHMEM_NAME_FIXCACHE(L"Global\\LUCULENT_RTDB_FIXCACHE");
LPCWSTR const RTDB_SHMEM_NAME_MIGRATIONCONFIG(L"Global\\LUCULENT_RTDB_MIGRATIONCONFIG");
LPCWSTR const RTDB_SHMEM_NAME_MIGRATIONSTATUS(L"Global\\LUCULENT_RTDB_MIGRATIONSTATUS");

LPCWSTR const RTDB_FILE_NAME_SYSCONFIG(L"BaseInfo.dat");
LPCWSTR const RTDB_FILE_NAME_GRPCONFIG(L"GroupInfo.dat");
LPCWSTR const RTDB_FILE_NAME_TAGCONFIG(L"PointInfo.dat");
LPCWSTR const RTDB_FILE_NAME_TAGCONFIGEX(L"PointInfoEx.dat");
LPCWSTR const RTDB_FILE_NAME_TAGHASH(L"TagHash.dat");
LPCWSTR const RTDB_FILE_NAME_CACHEINDEX(L"CacheIndex.dat");
LPCWSTR const RTDB_FILE_NAME_CACHESYNC(L"CacheSync.dat");
LPCWSTR const RTDB_FILE_NAME_ALARM(L"alarm.dat");
LPCWSTR const RTDB_FILE_NAME_FIXCACHE(L"FixCache.dat");
LPCWSTR const RTDB_FILE_NAME_BACKUPSTATUS(L"MigrationStatus.dat");

LPCWSTR const RTDB_MUTEX_NAME_GRPCONFIG(L"Global\\LUCULENT_RTDB_GROUPCONFIG_MUTEX");
LPCWSTR const RTDB_MUTEX_NAME_TAGCONFIG(L"Global\\LUCULENT_RTDB_TAGCONFIG_MUTEX");
LPCWSTR const RTDB_MUTEX_NAME_BACKUPCONFIG(L"Global\\LUCULENT_RTDB_BACKUPCONFIG_MUTEX");
LPCWSTR const RTDB_MUTEX_NAME_CACHEOPEN(L"Global\\LUCULENT_RTDB_CACHEOPEN_MUTEX");
LPCWSTR const RTDB_MUTEX_NAME_COMOPEN(L"Global\\LUCULENT_RTDB_COMOPEN_MUTEX");

LPCWSTR const RTDB_OBJECT_NAME_SYSTEMLOCK(L"Global\\SystemLock");
LPCWSTR const RTDB_FILE_NAME_SYSTEMLOCK(L"SystemLock");

LPCWSTR const RTDB_SEM_HISTCONTROL(L"Global\\LUCULENT_RTDB_HISTCONTROL");
LPCWSTR const RTDB_SEM_DATACONTROL(L"Global\\LUCULENT_RTDB_DATACONTROL");
LPCWSTR const RTDB_SEM_BACKUPCONTROL(L"Global\\LUCULENT_RTDB_BACKUPCONTROL");
const static std::wstring RTDB_FUN_INIT_OVER_EVENT = L"Global\\Luculent.SIS.RTDB.Fun.Init.Over.Event.";
const static std::wstring DBSHAREDINFO = L"SharedInfo.dat";

enum RTDB_SYSTEMLOCK_ID
{
    RTDB_SYSTEMLOCK_TAGHASH = 0,
    RTDB_SYSTEMLOCK_TAGCACHE,
};

enum RTDB_SYS_RUN_STATUS
{
    RTDB_SYS_STOP = 0,
    RTDB_SYS_RUN = 1,
	RTDB_SYS_UNKNOWN
};

enum RTDB_TAG_TYPE
{
    RTDB_TAG_TYPE_BEGIN = '0',
    RTDB_TAG_SWITCH_CHAR = RTDB_TAG_TYPE_BEGIN,
    RTDB_TAG_SWITCH_SHORT,
    RTDB_TAG_SWITCH_INT,
    RTDB_TAG_SWITCH_LONG,
    RTDB_TAG_SWITCH_FLOAT,
    RTDB_TAG_SWITCH_DOUBLE,
    RTDB_TAG_SWITCH_VCHAR,
    RTDB_TAG_SWITCH = RTDB_TAG_SWITCH_VCHAR,
    RTDB_TAG_SIMULATE_FLOAT,
    RTDB_TAG_SIMULATE_DOUBLE,
    RTDB_TAG_SIMULATE = RTDB_TAG_SIMULATE_DOUBLE,
    RTDB_TAG_TYPE_CNT
};

enum RTDB_TAG_STATUS
{
	RTDB_TAG_STATUS_NULL = 0,
	RTDB_TAG_STATUS_NORMAL,
	RTDB_TAG_STATUS_DEL
};

const uint32_t RTDB_SYNCTAG_MAXNUM = 10000;

enum RTDB_HIST_STORE
{
    RTDB_HIST_NONE = 0,
    RTDB_HIST_LSC,
    RTDB_HIST_RESERVE,
    RTDB_HIST_ORG
};

enum RTDB_FIX_STATUS
{
    RTDB_FIX_INIT = 0,
    RTDB_FIX_OK,
    RTDB_FIX_NOT,
    RTDB_FIXING
};

enum RTDB_VALUETYPE    //ֵ����
{
	RTDB_TYPE_INT = 0,
	RTDB_TYPE_FLOAT,
	RTDB_TYPE_LONG,
	RTDB_TYPE_BOOL,
	RTDB_TYPE_STRING,
	RTDB_TYPE_UNDEFINE
};


struct CacheSyncFile
{
    uint32_t runStatus;
    int runTime;
    uint32_t syncCode;
    uint32_t syncTagCnt;
	uint32_t ctrlCode;
	int ctrlTime;

	int	licenseTagNum;		// ��Ȩ����
	int	tagDelCount;	    // ��ǰɾ�������
	int	tagCount;		    // ��ǰ��Ч�����

	int dbLinkNum;

	int hisProcessID;
	int mainProcessID;
	int funProcessID;
	int calcProcessID;

	int hisCPUUserate;
	int mainCPUUserate;
	int funCPUUserate;
	int calcCPUUserate;

	int hisDisIO;
	int mainDisIO;
	int funDisIO;
	int calcDisIO;

	int hisNetIO;
	int mainNetIO;
	int funNetIO;
	int calcNetIO;

	int hisPrivateMem;
	int mainPrivateMem;
	int funPrivateMem;
	int calcPrivateMem;

	int hisVirtualMem;
	int mainVirtualMem;
	int funVirtualMem;
	int calcVirtualMem;
};

struct CacheSync
{
    CacheSyncFile *syncInfo;
    int *tagId;

    CacheSync():syncInfo(NULL),tagId(NULL) {}
    CacheSync(CacheSyncFile *sync, int *tag):syncInfo(sync),tagId(tag) {}
};

//���������ڴ��
struct PromConfig
{
	int				licenseTagNum;		// ��Ȩ����
	int				licenseDate;		// ��Ȩ����
	BOOL			validLicense;		// ��Ȩ��Ч
	int				tagDelCount;	    // ��ǰɾ�������
    int				tagCount;		    // ��ǰ��Ч�����
    int				minUnusedID;		// ��ǰ��С����ID��
    int             calcChanged;        // ������޸ı�־
    int             histNotify;         // ��ʷ����֪ͨ
    int             minDeleteID;
    int             reserve0;           // ���ݷ���֪ͨ
    int             reserve1;           // ���ݷ���֪ͨ
    char            version[64];        // �汾��Ϣ
};

enum RTDB_MODULE
{
    RTDB_MAINSERVER = 0,
    RTDB_HISTORYSERVER,
    RTDB_BACKUPSERVER,
    RTDB_DATAENGINE,
    RTDB_COMINTERFACE,
	RTDB_CALCSERVER,
    RTDB_MODULE_COUNT,
};

LPCSTR const RTDB_MODULE_NAME[] =
{
    "������",
    "��ʷ����",
    "���ݷ���",
    "��������",
    "����ӿ�",
	"��������"
};

//ģ��汾��Ϣ
struct ModuleInfo
{
    char            version[16];        // �汾��Ϣ
    char            createTime[16];     // ����ʱ��
};

//����״̬�ڴ��
struct ServerStatus
{
    int             serverRunTime;      // ��������ʱ��
    int             historyServerStatus;// ��ʷ����״̬
    int             historyServerTime;  // ��ʷ��������ʱ��
	int				hisProcessID;		// ��ʷ�������ID
    int             backupServerStatus; // ���ݷ���״̬
    int             backupServerTime;   // ���ݷ�������ʱ��
	int				backupProcessID;	// ��ʷ�������ID
	int             dataServerStatus;	// ���ݷ���״̬
	int             dataServerTime;		// ���ݷ�������ʱ��
	int				dataProcessID;		// ��ʷ�������ID
	int             calcServerStatus;	// �������״̬
	int             calcServerTime;		// ���㷨��������ʱ��
	int				calcProcessID;		// ��ʷ�������ID
    ModuleInfo      moduleInfo[RTDB_MODULE_COUNT];  // ģ����Ϣ
    int             linkCount;          // ������
    
};

//����
struct TagGroup
{  
    int            gID;                 // ��ID
    char           groupname[MAXLEN_GROUP+1];       // ����
    unsigned char  availability;        // ����Ч
    char           groupdesc[63];       // ������
};

//������
union AlarmFlag
{
    struct 
    {
        short           sAlarmH:1;
        short           sAlarmSH:1;
        short           sAlarmSSH:1;
        short           sAlarmL:1;
        short           sAlarmSL:1;
        short           sAlarmSSL:1;
        short           sAlarmReserve:9;
        short           sAlarm:1;
    };
    short sflag;
};

enum class AlarmLevel
{
	HIGHT_ALARMLEVEL,
	SHIGHT_ALARMLEVEL,
	SSHIGHT_ALARMLEVEL,
	LOW_ALARMLEVEL,
	SLOW_ALARMLEVEL,
	SSLOW_ALARMLEVEL,
	NUM_ALARMLEVEL
};

struct AlarmAttr
{
    char            cType[3];
    union
    {
        float       fAlarm[3];          // 0-���� 1-������ 2-��������
        int         iAlarm[3];
    };
};

struct TagAttr
{
	int				iID;			    // ��ID
	char			cName[MAXLEN_TAGNAME+1];		    // ����
	char			cDesc[MAXLEN_TAGDESC+1];		    // ����
	char			cUints[MAXLEN_TAGUNIT+1];         // ���̵�λ
	char			cSource[MAXLEN_TAGSOURCE+1];		    // ��Դ
	char			cExDesc[MAXLEN_TAGDESCEX+1];		// �������
	char			cType[MAXLEN_TAGTYPE+1];			// ����
	float           fCompdev;		    // ѹ������
	

	//��������
    AlarmFlag       tAlarmFlag;         // ������ʶ
    AlarmAttr       tAlarmHigh;         // ���ޱ���
    AlarmAttr       tAlarmLow;          // ���ޱ���

	char			cExa[MAXLEN_TAGEXA+1];
	char			cExb[MAXLEN_TAGEXB+1];
	char			cGroupID[MAXLEN_GROUP+1];		// ��ID
	short		    iStatus;			// ��״̬
    short           iTimeDes;           // ʱ�侫��
	int				iIsHis;				// �Ƿ���Ҫ��ʷ�洢
    char            cQuote;             // �Ƿ����� 0-δ���� 1-��������
	RTDB_VALUETYPE	tagValueType;			//��ֵ����
	char			reserve[196];		// ����200���ֽ�
};

struct TagAttrEx
{
    int            createTime;           // �㴴��ʱ��
    int             preIndex;
    int             nextIndex;
    int             reserve;
};

//����

struct AlarmBuffer
{
    float mmValue;
    int timestamp;
    short timemsec;
    char alarmStatus;
};


#pragma pack(1)
struct AlarmIO
{
    short length;
	int alarmTime;
    short alarmTimemsec;
    char alarmStatus;
	int timestamp;
    short timemsec;
    float mmValue;
    char preAlarmStatus;
    char tagName[50];
};
#pragma pack()

// fix
struct TagFixDeter 
{
    int status;
	int cycle;
	int allCnt;
	int storeCnt;
	int startTime;
};


// backup
enum RTDB_MIGRATE_MODE
{
    RTDB_MIGRATE_RECOVER = 0,
    RTDBA_MIGRATE_MANUALBACKUP,
    RTDB_MIGRATE_AUTOBACKUP,
    RTDB_MIGRATE_MODE_COUNT,
};

enum RTDB_MIGRATE_SYNC
{
    RTDB_MIGRATE_SYNC_OK = 0,
    RTDB_MIGRATE_SYNC_SET
};

enum RTDB_MIGRATE_PLAN
{
    RTDB_MIGRATE_DAY = 0,
    RTDBA_MIGRATE_WEEK,
    RTDB_MIGRATE_MONTH,
};

enum RTDB_MIGRATE_STATUS
{
    RTDB_MIGRATE_IDLE = 0,
    RTDB_MIGRATE_REQUEST,
    RTDB_MIGRATE_BUSY,
};

#pragma pack(4)
struct MigrationConfig
{
    int         syncFlag;
    char        dataDir[MAX_PATH];
    char        backupDir[MAX_PATH];
    int         autoBackup;             // �Ƿ��Զ�����
    int         autoBackupTime;         // ����ʱ��
    int         autoBackupPlan;         // ���ݼƻ���0������ 1�������� 2������
    int         autoBackupPlanData;     // ���ݼƻ�ֵ
    int         autoBackupDeleteFile;   // �Զ������Ƿ�ɾ��ԭ�ļ�
};

struct MigrationStatus
{
    int         status;                 // ״̬��0-���� 1-���� 2-������
	int			autoBackupEndTime;		// �������ݽ�ֹʱ��
    int         migrationCheckTime;     // ���ݼ��ʱ��
    int         migrationStartTime;     // ���ݿ�ʼʱ��
    int         migrationEndTime;       // ���ݽ���ʱ��
    int         dataStartTime;          // �������ݿ�ʼʱ��
    int         dataEndTime;            // �������ݽ���ʱ��
    int         dataSize;               // ���ݴ�С����λ��M��
    int         currDataSize;           // �ѱ������ݴ�С����λ��M��
    int         progress;               // ���ȣ��ٷֱȣ�
    int         code;                   // ���ݽ��
};
#pragma pack()

// �ļ���Ϣ�ṹ
struct PathNameInfo
{
    std::string path;       // �ļ�·��
    std::string namePre;    // �ļ���ǰ׺
    std::string nameSuf;    // �ļ�����׺
};

#endif // LIRTDB_DEFINE_H
