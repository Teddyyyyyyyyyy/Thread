#include <thread/thread.h>
#include <thread/auto_lock.h>
using namespace hexu::thread;

Thread::Thread() : m_tid(0), m_task(nullptr)
{
}

Thread::~Thread()
{
}

void Thread::start()
{
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);//将其设置为绑定
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);//设置为已分离状态（不需要pthread_join），防止出现内存泄漏
    pthread_create(&m_tid, &attr, thread_func, (void *)this);
    pthread_attr_destroy(&attr);
}

void Thread::stop()
{
    pthread_exit(PTHREAD_CANCELED);
}

void* Thread::thread_func(void* ptr)
{
    Thread* thread = (Thread *)ptr;
    thread->run();
    return ptr;
}

void Thread::set_task(Task* task)
{
    AutoLock lock(&m_mutex);
    m_task = task;
    m_cond.signal();//发出信号表示可以执行
}

Task* Thread::get_task()
{
    AutoLock lock(&m_mutex);
    return m_task;
}
