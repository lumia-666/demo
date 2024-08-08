#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <pthread.h>
#include <unistd.h>

using namespace std;

void* myThreadID1(void*)
{
    cout << "thread_ID1" << "\n";
}

void* myThreadID2(void*)
{
    cout << "thread_ID2" << "\n";
}

int main()
{
    int i = 0, ret = 0;
    pthread_t id1, id2;//�����߳�ID

    ret = pthread_create(&id1, NULL, myThreadID1, NULL); //������ִ���߳�id1
    if (ret == -1) {
        printf("Create pthread error!\n");
        return 1;
    }

    ret = pthread_create(&id2, NULL, myThreadID2, NULL); //������ִ���߳�id2
    if (ret == -1) {
        printf("Create pthread error!\n");
        return 1;
    }

    pthread_join(id1, NULL);  //�������̣߳�ֱ��id1�����ŽӴ���
    pthread_join(id2, NULL);

    cout << "all thread done!"<<endl;
    return 0;
}

