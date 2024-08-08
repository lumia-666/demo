#pragma once
#define SEND_BUFF_MAXSIZE 1024*8
#include "xspsc_queue.h"
#include <WinSock2.h>
#include <string>
#include <atomic>
//�ͻ��˷�װ��
class SocketClient
{
	using ringQueue = x_spsc_queue_t< std::string, 10 >;
public:
	SocketClient(SOCKET sock);
	~SocketClient();
	//���黺������Ƿ���ֵ
	bool hasSendData();
	//��ȡ����һ�������͵�����
	std::string getSendData();
	//��ȡ����ʱ��
	time_t getOffLineTime();
	SOCKET GetSock();
	int PushSendData(std::string &sendData);
private:
	//socket�׽��֣�ÿ��SocketClient��Ӧһ��socket
	SOCKET sock_;
	//���ͻ�����
	ringQueue sendBuff_;
	//�ϴη�����Ϣ���ݵ�ʱ�䣬���ڼ�ʱ������
	time_t dtSend_;
	bool sendFlg_ = false;
};