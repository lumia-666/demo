#pragma once
#include <iostream>
#include <pthread.h>

// ���廥��������������
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

// ����future��promise
template <typename T>
class Future {
public:
    Future() : m_value(), m_ready(false) {}

    T get() {
        // ����
        pthread_mutex_lock(&mutex);
        // ���ֵδ׼���ã���ȴ���������
        while (!m_ready) {
            pthread_cond_wait(&cond, &mutex);
        }
        // ����
        pthread_mutex_unlock(&mutex);
        // ����ֵ
        return m_value;
    }

    void set(T value) {
        // ����
        pthread_mutex_lock(&mutex);
        // ����ֵ
        m_value = value;
        m_ready = true;
        // �������������ź�
        pthread_cond_signal(&cond);
        // ����
        pthread_mutex_unlock(&mutex);
    }

private:
    T m_value;
    bool m_ready;
};

template <typename T>
class Promise {
public:
    Promise() : m_future() {}

    Future<T>& get_future() {
        return m_future;
    }

    void set_value(T value) {
        m_future.set(value);
    }

private:
    Future<T> m_future;
};

void* thread_func(void* arg)
{
    Promise<int>* promise = (Promise<int>*)arg;
    // ����1 + 2������������õ�promise��
    promise->set_value(1 + 2);
    return NULL;
}

int main()
{
    Promise<int> promise;
    Future<int>& future = promise.get_future();

    pthread_t thread;
    pthread_create(&thread, NULL, thread_func, (void*)&promise);

    // �ȴ�future��ֵ����������
    std::cout << "Result: " << future.get() << std::endl;

    pthread_join(thread, NULL);

    return 0;
}

