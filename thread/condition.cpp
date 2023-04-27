#include <thread/condition.h>

using namespace hexu::thread;

Condition::Condition()
{
    pthread_cond_init(&m_cond, NULL);//初始化条件变量
}

Condition::~Condition()
{
    pthread_cond_destroy(&m_cond);//销毁条件变量
}

int Condition::wait(Mutex* mutex)
{
    return pthread_cond_wait(&m_cond, &(mutex->m_mutex));//已初始化的条件变量，与条件变量配合使用的互斥锁
}

//可以借助以下俩个函数相它们发送"条件成立"信号，解除它们的"被阻塞"状态
int Condition::signal()
{
    return pthread_cond_signal(&m_cond);//至少解除一个
}

int Condition::broadcast()
{
    return pthread_cond_broadcast(&m_cond);//全部解除
}
