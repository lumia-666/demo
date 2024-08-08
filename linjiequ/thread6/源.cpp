#include<iostream>
#include<thread>
#include<string>
#include<vector>
#include<list>
#include<mutex>
#include<Windows.h>
using namespace std;
#define __WINDOWSJQ_
vector<int>g_v = { 1,2,3 };
void myprint(int inum) {
    //cout << "myprint��ʼִ����" << endl;
    cout << "�߳�idΪ��" << this_thread::get_id() << "��ӡg_vֵ��" << g_v[0] << g_v[1] << g_v[2] << endl;
    return;
    //cout << "myprintִ�������" << endl;
}
class A {
public:
    void inMsgRecvQueue() {
        for (int i = 0; i < 10000; i++) {
            cout << "inMsgRecvQueue()ִ�У�����һ��Ԫ��:" << i << endl;
            unique_lock<mutex>sbguard1(my_mutex1);
            //�� unique_lock ��ͨ�û����װ���������ӳ���������������ʱ�޳��ԡ��ݹ�����������Ȩת�ƺ�����������һͬʹ�á�
            //unique_lock��lock_guardʹ�ø��������ܸ���ǿ��ʹ��unique_lock��Ҫ���������ʱ�䡢���ܳɱ���
            msgRecvQueue.push_back(i);
            my_cond.notify_one();//����wait
        }
        return;
    }
    //bool outMsgLULproc(int& command) {
    //    /* lock_guard<mutex>sbguard(my_mutex1);*/
    //     //my_mutex.lock();
    //    if (!msgRecvQueue.empty()) {
    //        unique_lock<mutex>sbguard1(my_mutex1);
    //        if (!msgRecvQueue.empty()) {
    //            int command = msgRecvQueue.front();
    //            msgRecvQueue.pop_front();
    //            /*   my_mutex.unlock();*///ÿ����֧��ֻҪ�����ˣ���������unlock
    //            return true;
    //        }
    //    }
    //    return false;
    //}
    void outMsgRecvQueue() {
        int command = 0;
        while (true) {
            unique_lock<mutex>sbguard1(my_mutex1);
            my_cond.wait(sbguard1, [this] {//һ��lambda���ǿɵ��ö���
                if (!msgRecvQueue.empty())
                    return true;
                return false;
                }); //����ڶ�������lambda����ֵ��true,waitֱ�ӷ���
            //����ڶ�������lambda����ֵ��false,wait�����������������������У�ֱ������ĳ���̵߳���nitify_oneΪֹ
            //���waitû�еڶ�����������ôЧ��������lambda����false
            //�����Ѻ󲻶ϳ������»�ȡ���������������ȡ���������̿���wait���Ż�ȡ
            //��������������������һ�������ŵ�
            //Ҳ���ǵȴ���Ϣ�����Ƿ�Ϊ�յ�֪ͨ��ȡ��ԭ�����жϣ�����С
            int command = msgRecvQueue.front();
            msgRecvQueue.pop_front();
            sbguard1.unlock();//unique_lock��ʱ��������
            cout << "outMsgRecvQueue()ִ��,ȡ��һ��Ԫ��" << command << endl;
        }


        //for (int i = 0; i < 10000; i++) {
        //    bool result = outMsgLULproc(command);
        //    if (result == true) {
        //        cout << "outMsgRecvQueue()ִ��,ȡ��һ��Ԫ��" << command << endl;
        //    }
        //    else {
        //        cout << "outMsgRecvQueue()ִ��,��Ŀǰ��Ϣ����Ϊ��" << i << endl;
        //    }
        //}
        //cout << "end" << endl;
    }
    A() {
#ifdef  __WINDOWSJQ_
        InitializeCriticalSection(&my_winsec);//���ٽ���ǰ�ȳ�ʼ��
#endif
    }
private:
    list<int>msgRecvQueue;//�ѹ���������ס������������������ݵı���ȴ���������ס������������
    mutex my_mutex1;
    condition_variable my_cond;//����������������
#ifdef  __WINDOWSJQ_
    CRITICAL_SECTION my_winsec;//windows�е��ٽ������ǳ�������c++�е�mutex
#endif

};
int main() {
	g_v.erase()
    //condition_variable:ʵ������һ���࣬�ȴ�������ɣ��뻥�������ʹ�ã�Ҫ������Ķ���
    A myobja;
    thread myOut(&A::outMsgRecvQueue, &myobja);//�ڶ������������ñ�֤�����߳��õ�ͬһ������
    thread myIn(&A::inMsgRecvQueue, &myobja);
    myOut.join();
    myIn.join();
    system("pause");
    return 0;
}
