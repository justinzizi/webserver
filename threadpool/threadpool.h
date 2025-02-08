#ifndef THREADPOOL_H
#define THREADPOOL_H
#include <list>
#include <cstdio>
#include <exception>
#include <pthread.h>

template <typename T>
class threadpool
{
private:
    static void *worker(void *arg);
    void run();
private:
    int m_thread_number; //线程池中的线程数
    int m_max_requests;  //请求队列中允许的最大请求数
    pthread_t *m_threads;//描述线程池的数组
    std::list<T *> m_workqueue;//请求队列
    locker m_queuelocker;  //保护请求队列的互斥锁
    sem m_queueestat;    //是否有任务需要处理
    connection_pool *m_connPool; //数据库
    int m_actor_model;  //模型切换

public:
    threadpool(int actor_model, connection_pool *connPool,int thread_number = 8; int max_request = 1000);
    ~threadpool();
};
template<typename T>
threadpool<T>::threadpool(int actor_model, connection_pool *connPool,int thread_number, int max_request)
: m_actor_model(actor_model), m_thread_number(thread_number), m_max_requests(max_request),m_threads(NULL),m_connPool(connPool)
{
    if(thread_number <= 0 || max_request <=0)
        throw std::exception();//检查参数，防止无效的线程池配置
        m_threads = new pthread_t[m_thread_number];
        if(!m_threads){
            throw std::exception();
        }
        for(int i = 0; i< thread_number;++i){
            if(pthread_create(m_threads + i))
        }
}
template <typename T>
threadpool<T>::~threadpool()
{
}




#endif