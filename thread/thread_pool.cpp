#include <thread/thread_pool.h>
#include <thread/worker_thread.h>
using namespace hexu::thread;

#include <utility/logger.h>
using namespace hexu::utility;

ThreadPool::ThreadPool() : m_threads(0)
{
}

ThreadPool::~ThreadPool()
{
}

void ThreadPool::create(int threads)
{
    AutoLock lock(&m_mutex);
    m_threads = threads;
    for (int i = 0; i < threads; i++)
    {
        Thread* thread = new WorkerThread();
        log_debug("create thread %x", thread);
        m_pool.push_back(thread);
        thread->start();
    }
}

Thread* ThreadPool::get()
{
    AutoLock lock(&m_mutex);
    while (m_pool.empty())//若线程池为空则通过调用m_cond.wait函数等待线程池中的线程可用
        m_cond.wait(&m_mutex);
    Thread * thread = m_pool.front();//当线程可用时，从线程池中取出
    m_pool.pop_front();
    return thread;//返还给调用者
}

void ThreadPool::put(Thread *thread)
{
    AutoLock lock(&m_mutex);
    m_pool.push_back(thread);//将线程返还给线程池
    m_cond.signal();//发出可用信号
}

bool ThreadPool::empty()//判断线程池是否为空
{
    AutoLock lock(&m_mutex);
    return m_pool.empty();
}

void ThreadPool::assign(Task *task)//获取一个Task对象，并将其分配给线程池中的线程
{
    if (task == nullptr)
    {
        log_error("assign a null task to thread pool");
        return;
    }

    log_debug("assign a task: %x to thread pool", task);
    Thread* thread = get();//调用get方法从池中检索获取线程
    if (thread != nullptr)
    {
        thread->set_task(task);
    }
    else
    {
        log_error("thread is null, assign a task failed");
    }
}
