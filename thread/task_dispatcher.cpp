#include <thread/task_dispatcher.h>
using namespace hexu::thread;

#include <utility/logger.h>
#include <utility/singleton.h>
using namespace hexu::utility;

TaskDispatcher::TaskDispatcher()
{
}

TaskDispatcher::~TaskDispatcher()
{
}

void TaskDispatcher::init(int threads)
{
    Singleton<ThreadPool>::instance()->create(threads);
    start();
}

void TaskDispatcher::assign(Task* task)
{
    log_debug("task dispatcher assign task: %x", task);
    m_mutex.lock();
    m_tasks.push_back(task);//放入任务队列
    m_mutex.unlock();
    m_cond.signal();//通知线程有可用资源
}

void TaskDispatcher::handle(Task* task)
{
    log_debug("task dispatcher handle task");
    ThreadPool * pool = Singleton<ThreadPool>::instance();
    if (!pool->empty())
    {
        pool->assign(task);//若线程池中有线程可用，则调用assign
    }
    else
    {
        AutoLock lock(&m_mutex);
        m_tasks.push_front(task);//放入任务列表中
        log_debug("all threads are busy!");
    }
}

bool TaskDispatcher::empty()
{
    AutoLock lock(&m_mutex);
    return m_tasks.empty();//返回任务队列是否为空
}

void TaskDispatcher::run()
{
    sigset_t mask;
    if (0 != sigfillset(&mask))
    {
        log_error("thread manager sigfillset failed!");
        return;
    }
    if (0 != pthread_sigmask(SIG_SETMASK, &mask, NULL))
    {
        log_error("thread manager pthread_sigmask failed!");
        return;
    }
    while (true)
    {
        // log_debug("task list: %d", m_tasks.size());
        m_mutex.lock();
        while (m_tasks.empty())//任务队列为空，则线程等待
            m_cond.wait(&m_mutex);
        Task* task = m_tasks.front();
        m_tasks.pop_front();//从任务队列中拿出一个任务
        m_mutex.unlock();
        handle(task);//处理任务
    }
}
