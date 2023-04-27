#include <thread/mutex.h>
using namespace hexu::thread;

Mutex::Mutex()//
{
    pthread_mutexattr_t attr; 
    pthread_mutexattr_init(&attr);//用于设置互斥锁属性
    pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_ERRORCHECK);//设置互斥锁的属性：互斥锁是带错误检查的
    pthread_mutex_init(&m_mutex, &attr);//指向互斥锁变量的指针
    pthread_mutexattr_destroy(&attr);
}

Mutex::~Mutex()//销毁锁
{
    pthread_mutex_destroy(&m_mutex);
}

int Mutex::lock()//上锁
{
    return pthread_mutex_lock(&m_mutex);
}

int Mutex::try_lock()//测试加锁
{
    return pthread_mutex_trylock(&m_mutex);
}

int Mutex::unlock()//下锁
{
    return pthread_mutex_unlock(&m_mutex);
}
