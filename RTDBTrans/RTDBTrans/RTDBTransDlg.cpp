
// RTDBTransDlg.cpp: ʵ���ļ�
//

#include "pch.h"
#include "framework.h"
#include "RTDBTrans.h"
#include "RTDBTransDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CRTDBTransDlg �Ի���



CRTDBTransDlg::CRTDBTransDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_RTDBTRANS_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
	ReadCfg();
	m_pointPath = "";
	spdlog::set_pattern("%Y-%m-%d %H:%M:%S - [thread %t][%^%l%$][%s][%#]|,%v");
	spdlog::set_level(static_cast<spdlog::level::level_enum>(m_logLevel));
	//������־Ϊ�첽��־��������������־�ļ���һֱд��
	//my_logger_ = spdlog::basic_logger_mt(logger_name, file_name);
	m_logger = spdlog::basic_logger_mt<spdlog::async_factory>("trans", "./log.txt");
	//���������󼶱����ϵ�����ˢ�µ���־
	m_logger->flush_on(spdlog::level::err);
	//ÿ����ˢ��һ��
	spdlog::flush_every(std::chrono::seconds(3));
}

void CRTDBTransDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_IPADDRESS_RTDB, m_rtdbAddr);
	DDX_Text(pDX, IDC_EDIT_UAPORT, m_uaPort);
	DDX_Text(pDX, IDC_EDIT_INTERVAL, m_interval);
	DDX_Text(pDX, IDC_IPADDRESS_TSDB, m_tsdbAddr);
	DDX_Text(pDX, IDC_IPADDRESS_MQTT, m_mqttAddr);
	DDX_Text(pDX, IDC_IPADDRESS_KAFKA, m_kafkaAddr);
	DDX_Text(pDX, IDC_EDIT_RTDBPORT, m_rtdbPort);
	DDX_Text(pDX, IDC_EDIT_TSDBPORT, m_tsdbPort);
	DDX_Text(pDX, IDC_EDIT_MQTTPORT, m_mqttPort);
	DDX_Text(pDX, IDC_EDIT_MQTTTOPIC, m_mqttTopic);
	DDX_Text(pDX, IDC_EDIT_KAFKATOPIC, m_kafkaTopic);
	DDX_Text(pDX, IDC_MFCEDITBROWSE1, m_pointPath);
	DDX_Check(pDX, IDC_CHECK_UA, m_uaCheck);
	DDX_Check(pDX, IDC_CHECK_OPENTSDB, m_tsdbCheck);
	DDX_Check(pDX, IDC_CHECK_MQTT, m_mqttCheck);
	DDX_Check(pDX, IDC_CHECK_KAFKA, m_kafkaCheck);
}

BEGIN_MESSAGE_MAP(CRTDBTransDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CHECK_UA, &CRTDBTransDlg::OnBnClickedCheckUa)
	ON_BN_CLICKED(IDC_CHECK_OPENTSDB, &CRTDBTransDlg::OnBnClickedCheckOpentsdb)
	ON_BN_CLICKED(IDC_CHECK_MQTT, &CRTDBTransDlg::OnBnClickedCheckMqtt)
	ON_BN_CLICKED(IDC_CHECK_KAFKA, &CRTDBTransDlg::OnBnClickedCheckKafka)
	ON_BN_CLICKED(IDC_START, &CRTDBTransDlg::OnBnClickedStart)
	ON_BN_CLICKED(IDC_CANCEL, &CRTDBTransDlg::OnBnClickedCancel)
	//ON_WM_TIMER()
END_MESSAGE_MAP()


// CRTDBTransDlg ��Ϣ�������

BOOL CRTDBTransDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CRTDBTransDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CRTDBTransDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CRTDBTransDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CRTDBTransDlg::ReadCfg()
{
	std::ifstream file("./config.ini");
	if (!file)
	{
		WritePrivateProfileString("Config", "RtdbAddr", "127.0.0.1", "./config.ini");
		WritePrivateProfileString("Config", "RtdbPort", "20010", "./config.ini");
		WritePrivateProfileString("Config", "Interval", "1000", "./config.ini");
		WritePrivateProfileString("Config", "LogLevel", "1", "./config.ini");;
	}
	char* lpPath = new char[MAX_PATH];
	char* addr = new char[20];
	char* path = new char[100];
	strcpy_s(lpPath, MAX_PATH, "./config.ini");

	GetPrivateProfileString("Config", "RtdbAddr", "", addr, 20, lpPath);
	m_rtdbPort = GetPrivateProfileInt("Config", "RtdbPort", 0, lpPath);
	m_interval = GetPrivateProfileInt("Config", "Interval", 0, lpPath);
	m_logLevel = GetPrivateProfileInt("Config", "LogLevel", 0, lpPath);
	delete[] lpPath;
	m_rtdbAddr = (CString)addr;
	m_pointPath = (CString)path;
	delete[]addr;
	delete[] path;
}

void CRTDBTransDlg::WriteCfg()
{
	WritePrivateProfileString("Config", "RtdbAddr", m_rtdbAddr, "./config.ini");
	WritePrivateProfileString("Config", "RtdbPort", std::to_string(m_rtdbPort).c_str(), "./config.ini");
	WritePrivateProfileString("Config", "Interval", std::to_string(m_interval).c_str(), "./config.ini");
}

void CRTDBTransDlg::OnBnClickedCheckUa()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	CButton* pBtn = (CButton*)GetDlgItem(IDC_CHECK_UA);
	int state = pBtn->GetCheck();
	if (state == 1)
	{
		GetDlgItem(IDC_IPADDRESS_UA)->EnableWindow(true);
	}
	else
	{
		GetDlgItem(IDC_IPADDRESS_UA)->EnableWindow(false);
	}
}


void CRTDBTransDlg::OnBnClickedCheckOpentsdb()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CButton* pBtn = (CButton*)GetDlgItem(IDC_CHECK_OPENTSDB);
	int state = pBtn->GetCheck();
	if (state == 1)
	{
		GetDlgItem(IDC_IPADDRESS_TSDB)->EnableWindow(true);
		GetDlgItem(IDC_EDIT_TSDBPORT)->EnableWindow(true);
	}
	else
	{
		GetDlgItem(IDC_IPADDRESS_TSDB)->EnableWindow(false);
		GetDlgItem(IDC_EDIT_TSDBPORT)->EnableWindow(false);
	}
}


void CRTDBTransDlg::OnBnClickedCheckMqtt()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CButton* pBtn = (CButton*)GetDlgItem(IDC_CHECK_MQTT);
	int state = pBtn->GetCheck();
	if (state == 1)
	{
		GetDlgItem(IDC_IPADDRESS_MQTT)->EnableWindow(true);
		GetDlgItem(IDC_EDIT_MQTTPORT)->EnableWindow(true);
		GetDlgItem(IDC_EDIT_MQTTTOPIC)->EnableWindow(true);
	}
	else
	{
		GetDlgItem(IDC_IPADDRESS_MQTT)->EnableWindow(false);
		GetDlgItem(IDC_EDIT_MQTTPORT)->EnableWindow(false);
		GetDlgItem(IDC_EDIT_MQTTTOPIC)->EnableWindow(false);
	}
}


void CRTDBTransDlg::OnBnClickedCheckKafka()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CButton* pBtn = (CButton*)GetDlgItem(IDC_CHECK_KAFKA);
	int state = pBtn->GetCheck();
	if (state == 1)
	{
		GetDlgItem(IDC_IPADDRESS_KAFKA)->EnableWindow(true);
		GetDlgItem(IDC_EDIT_KAFKAPORT)->EnableWindow(true);
		GetDlgItem(IDC_EDIT_KAFKATOPIC)->EnableWindow(true);
	}
	else
	{
		GetDlgItem(IDC_IPADDRESS_KAFKA)->EnableWindow(false);
		GetDlgItem(IDC_EDIT_KAFKAPORT)->EnableWindow(false);
		GetDlgItem(IDC_EDIT_KAFKATOPIC)->EnableWindow(false);
	}
}




void CRTDBTransDlg::OnBnClickedStart()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	UpdateData(true);
	CString kafkaPort;
	GetDlgItemText(IDC_EDIT_KAFKAPORT, kafkaPort);
	if(((std::string)kafkaPort).size()>0)
	m_kafkaPort = std::stoi(((std::string)kafkaPort).c_str());
	trans::TransInfo info;
	info.rtdbAddr = m_rtdbAddr;
	info.uaPort = m_uaPort;
	info.tsdbAddr = m_tsdbAddr;
	info.mqttAddr = m_mqttAddr;
	info.kafkaAddr = m_kafkaAddr;
	info.rtdbPort = m_rtdbPort;
	info.tsdbPort = m_tsdbPort;
	info.mqttPort = m_mqttPort;
	info.kafkaPort = m_kafkaPort;
	info.mqttTopic = m_mqttTopic;
	info.kafkaTopic = m_kafkaTopic;
	info.pointPath = m_pointPath;
	info.logger = m_logger;
	info.interval = m_interval;
	info.sdkEnable["ua"] = m_uaCheck;
	info.sdkEnable["tsdb"] = m_tsdbCheck;
	info.sdkEnable["mqtt"] = m_mqttCheck;
	info.sdkEnable["kafka"] = m_kafkaCheck;
	
	m_trans = std::make_shared<trans::TransTask>(info);

	std::ifstream istrm(m_pointPath);
	if (!istrm)
	{
		MessageBox("�ļ�·������!");
		return;
	}

	//const auto interval = 1000;

	//if (m_interval < interval);
	//{
	//	MessageBox("ת������������1000����!");
	//	return;
	//}
	int ret = m_trans->Init();

	if (ret == trans::POINTEMPTY)
	{
		MessageBox("��ȡ���Ĳ��Ϊ��!");
		return;
	}

	if (ret == trans::INTERVALERROR)
	{
		MessageBox("ת������������1000����!");
		return;
	}

	if (ret == trans::RTDBCONNECTERROR)
	{
		MessageBox("ʵʱ������ʧ��!");
		return;
	}

	if (ret == trans::GETINFOERROR)
	{
		MessageBox("��ȡ�����Ϣʧ��!");
		return;
	}

	if (ret == trans::TRANSEMPTY)
	{
		MessageBox("��ѡ��һ��ת������!");
		return;
	}

	m_trans->Run();


	GetDlgItem(IDC_START)->EnableWindow(false);
	GetDlgItem(IDC_CANCEL)->EnableWindow(true);
	WriteCfg();
}


void CRTDBTransDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_trans->cancelFlg = true;
	GetDlgItem(IDC_START)->EnableWindow(true);
	GetDlgItem(IDC_CANCEL)->EnableWindow(false);
}



//void CRTDBTransDlg::OnTimer(UINT_PTR nIDEvent)
//{
//	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
//
//	CDialogEx::OnTimer(nIDEvent);//�ѵ�ǰ����û�б��������Ϣid����Ĭ�ϵĴ�����������
//}

