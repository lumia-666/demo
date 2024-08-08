#pragma once
#define FD_SETSIZE      1024
#include "SocketClient.h"
#include "xspsc_queue.h"
#include <iostream>
#include <string>
#include <map>
#include <thread>
#include <queue>
#include <mutex>
#include <functional>
#include <condition_variable>
//�߳������࣬ÿ������ӹ�һ�������Ŀͻ���
//ʹ��selectģ����ͻ��˽���IO����

struct RecvBufferData
{
	SOCKET sock;
	std::string buf;
	RecvBufferData() {};
	RecvBufferData(SOCKET sockArg, std::string bufArg) :sock(sockArg), buf(bufArg) {}
};
using ringQueue = x_spsc_queue_t< RecvBufferData, 100 >;

struct RecvLock
{
	ringQueue* recvBuffer;
	std::mutex *mutex;
	std::condition_variable *cv;
};

class ThreadTask
{
public:
	ThreadTask(RecvLock recvLock);
	ThreadTask(RecvLock recvLock, std::function<void (SOCKET)> cbDelete);
	~ThreadTask();
	//��ȡ���߿ͻ�������
	uint16_t getClientNum();
	//����һ���ͻ���
	void addClient(SOCKET sock);
	//ɾ��һ���ͻ���
	void deleteClient(SOCKET sock);
	//�����߳�
	void Start();
	//�����߳�,��ʱ�Զ��˳�
	bool PushSendData(RecvBufferData &sendData);
private:
	void Work();
	std::function<void (SOCKET)> cbDelete_;
	//���߿ͻ��˵ļ���
	std::map<SOCKET, SocketClient*> onlineClients_;
	//������ɾ�ͻ����̰߳�ȫ
	std::mutex clientsMutex_;
	//�����߳���ͣ
	time_t emptyContinueTime_;
	const uint16_t EMPTYOVERTIME = 3600;
	ringQueue* recvQueue_;
	std::condition_variable *cv_;
	std::condition_variable clientCv_;
	std::mutex* recvMutex_;
	std::atomic_bool startFlg_;
};