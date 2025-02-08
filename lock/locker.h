#ifndef LOCKER_H
#define LOCKER_H

#include <exception>
#include <pthread.h>
#include <semaphore.h>

class sem{//信号量是一种用于控制多个线程对共享资源访问的同步机制
public:
    sem()
    {
        if(sem_init(&m_sem,0,0) != 0){//初始化信号量为0
            throw std::exception();
        }
    }
    sem(int num)
    {
        if(sem_init(&m_sem,0,num)!= 0){//初始化信号量为num
            throw std::exception();
        }
    }
    ~sem()
    {
        sem_destroy(&m_sem);//销毁信号量，释放资源
    }
    bool wait()//p操作，信号量值减1
    {
        return sem_wait(&m_sem) == 0;
    }
    bool post()//v操作，信号量值加1
    {
        return sem_post(&m_sem) == 0;
    }
private:
    sem_t m_sem;
};
class locker
{
private:
    pthread_mutex_t m_mutex;
public:
    locker()
    {
        if (pthread_mutex_init(&m_mutex,NULL) != 0){
            throw std::exception();
        }
    }
    ~locker(){
        pthread_mutex_destroy(&m_mutex);
    }
    bool lock()
    {
        return pthread_mutex_lock(&m_mutex) == 0;
    }
    bool unlock(){
        return pthread_mutex_unlock(&m_mutex) == 0;
    }
    pthread_mutex_t *get(){
        return &m_mutex;
    }
};
class cond
{
public:
    cond(){
        if(pthread_cond_init(&m_cond,NULL)!=0)
        {
            throw std::exception();
        }
        
    }
    ~cond()
    {
        pthread_cond_destroy(&m_cond);
    }
    bool wait(pthread_mutex_t *m_mutex){
        int ret = 0;
        ret = pthread_cond_wait(&m_cond,m_mutex);
        return ret = 0;
    }

    bool timewait(pthread_mutex_t *m_mutex,struct timespec t){
        int ret;
        ret = pthread_cond_timedwait(&m_cond,m_mutex,&t);
        return ret == 0;
    }

    bool signal(){
        return pthread_cond_signal(&m_cond)==0;
    }
    bool broadcast()
    {
        return pthread_cond_broadcast(&m_cond) == 0;
    }
private:
    pthread_cond_t m_cond;
};


#endif