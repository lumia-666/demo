#include<unistd.h> //uni std
#include<arpa/inet.h>
#include<string.h>
#include<sys/epoll.h>

#define SOCKET int
#define INVALID_SOCKET  (SOCKET)(~0)
#define SOCKET_ERROR            (-1)

#include<stdio.h>
#include<vector>
#include<thread>
#include<algorithm>

std::vector<SOCKET> g_clients;
bool g_bRun = true;
void cmdThread()
{
	while (true)
	{
		char cmdBuf[256] = {};
		scanf("%s", cmdBuf);
		if (0 == strcmp(cmdBuf, "exit"))
		{
			g_bRun = false;
			printf("�˳�cmdThread�߳�\n");
			break;
		}
		else {
			printf("��֧�ֵ����\n");
		}
	}
}

int cell_epoll_ctl(int epfd, int op, SOCKET sockfd, uint32_t events)
{
	epoll_event ev;
	//�¼�����
	ev.events = events;
	//�¼�������socket����������
	ev.data.fd = sockfd;
	//��epoll����ע����Ҫ����������Socket�ļ�������
	//����˵�����ĵ��¼�
	//����0��������ɹ������ظ�ֵ����ʧ�� -1
	if (epoll_ctl(epfd, op, sockfd, &ev) == -1)
	{
		//if(events & EPOLLIN)
		// do something
		printf("error, epoll_ctl(%d,%d,%d)\n", epfd, op, sockfd);
	}
}

//������
char g_szBUff[4096] = {};
int g_nLen = 0;
int readData(SOCKET cSock)
{
	g_nLen = (int)recv(cSock, g_szBUff, 5, 0);
	return g_nLen;
}

int WriteData(SOCKET cSock)
{
	if (g_nLen > 0)
	{
		int nLen = (int)send(cSock, g_szBUff, g_nLen, 0);
		g_nLen = 0;
		return nLen;
	}
	return 1;
}

int clientLeave(SOCKET cSock)
{
	close(cSock);
	printf("�ͻ���<socket=%d>���˳�\n", cSock);
	auto itr = std::find(g_clients.begin(), g_clients.end(), cSock);
	g_clients.erase(itr);
}

int main()
{
	//����cmd�߳�
	std::thread t1(cmdThread);
	t1.detach();
	/////////////////////////////////
	//-- ��Socket API��������TCP�����
	// 1 ����һ��socket �׽���
	SOCKET _sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	// 2.1 bind �����ڽ��ܿͻ������ӵ�����˿�
	sockaddr_in _sin = {};
	_sin.sin_family = AF_INET;
	_sin.sin_port = htons(5889);//host to net unsigned short
	_sin.sin_addr.s_addr = INADDR_ANY;
	// 2.2
	if (SOCKET_ERROR == bind(_sock, (sockaddr*)&_sin, sizeof(_sin)))
	{
		printf("����,������˿�ʧ��...\n");
	}
	else {
		printf("������˿ڳɹ�...\n");
	}

	// 3 listen ��������˿�
	if (SOCKET_ERROR == listen(_sock, 64))
	{
		printf("����,��������˿�ʧ��...\n");
	}
	else {
		printf("��������˿ڳɹ�...\n");
	}
	const int maxClient = 60000;
	//linux 2.6.8 ��size��û��������
	//��epoll��̬�����������ֵΪfilemax
	//ͨ��cat /proc/sys/fs/file-max����ѯ
	int epfd = epoll_create(maxClient);

	//��epoll����ע����Ҫ����������Socket�ļ�������
	cell_epoll_ctl(epfd, EPOLL_CTL_ADD, _sock, EPOLLIN);
	//
	int msgCount = 0;
	int cCount = 0;
	//���ڽ��ռ�⵽�������¼�������
	epoll_event events[maxClient] = {};
	while (g_bRun)
	{
		//epfd epoll�����������
		//events ���ڽ��ռ�⵽�������¼�������
		//maxevents ��������Ĵ�С���ܹ����յ��¼�����
		//timeout
		//		t=-1 ֱ�����¼������ŷ���
		//		t= 0 �������� std::map
		//		t> 0 ���û���¼���ô�ȴ�t����󷵻ء�
		int n = epoll_wait(epfd, events, maxClient, -1);
		if (n < 0)
		{
			printf("error,epoll_wait ret=%d\n", n);
			break;
		}

		for (int i = 0; i < n; i++)
		{
			//�������socket�����¼�ʱ����ʾ���¿ͻ�������
			if (events[i].data.fd == _sock)
			{
				if (events[i].events & EPOLLIN)
				{
					// 4 accept �ȴ����ܿͻ�������
					sockaddr_in clientAddr = {};
					int nAddrLen = sizeof(sockaddr_in);
					SOCKET _cSock = INVALID_SOCKET;
					_cSock = accept(_sock, (sockaddr*)&clientAddr, (socklen_t*)&nAddrLen);
					cCount++;
					if (INVALID_SOCKET == _cSock)
					{
						printf("����,���ܵ���Ч�ͻ���SOCKET %d ���������%d��������Ϣ�ǡ�%s��...\n", cCount, errno, strerror(errno));
					}
					else
					{
						g_clients.push_back(_cSock);
						cell_epoll_ctl(epfd, EPOLL_CTL_ADD, _cSock, EPOLLIN | EPOLLET);
						printf("�¿ͻ��˼��룺socket = %d,IP = %s  %d\n", (int)_cSock, inet_ntoa(clientAddr.sin_addr), cCount);
					}
					continue;
				}
				// printf("other %d...\n",cCount);
			}
			//��ǰsocket�����ݿɶ���Ҳ�п���ʱ��������
			if (events[i].events & EPOLLIN)
			{
				//printf("EPOLLIN|%d\n",++msgCount);
				auto cSock = events[i].data.fd;
				int ret = readData(cSock);
				if (ret <= 0)
				{
					clientLeave(cSock);
				}
				else {
					printf("�յ��ͻ������ݣ�id = %d, socket = %d, len = %d\n", msgCount, cSock, ret);
				}
				//cell_epoll_ctl(epfd, EPOLL_CTL_MOD, cSock, EPOLLOUT);
			}
			//��ǰsocket�Ƿ��д����
			if (events[i].events & EPOLLOUT)
			{
				printf("EPOLLOUT|%d\n", msgCount);
				auto cSock = events[i].data.fd;
				int ret = WriteData(cSock);
				if (ret <= 0)
				{
					clientLeave(cSock);
				}
				if (msgCount < 5)
					cell_epoll_ctl(epfd, EPOLL_CTL_MOD, cSock, EPOLLIN);
				else
					cell_epoll_ctl(epfd, EPOLL_CTL_DEL, cSock, 0);
			}
			/*
			if(events[i].events & EPOLLERR)
			{
				auto cSock = events[i].data.fd;
				printf("EPOLLERR��id = %d, socket = %d\n",msgCount, cSock);
			}
			if(events[i].events & EPOLLHUP)
			{
				auto cSock = events[i].data.fd;
				printf("EPOLLHUP��id = %d, socket = %d\n",msgCount, cSock);
			}
			*/
		}
	}

	for (auto client : g_clients)
	{
		close(client);
	}
	close(epfd);
	close(_sock);
	printf("���˳���\n");
	return 0;
}


/*
cell_epoll_ctl(epfd, EPOLL_CTL_ADD, cSock, EPOLLOUT|EPOLLIN);
c++ �������� ��λ�� ��λ��
C/C++��������ʹ��λ������
https://www.zhihu.com/question/23814540/answer/25745880
https://blog.csdn.net/sinat_29003361/article/details/52713749
*/