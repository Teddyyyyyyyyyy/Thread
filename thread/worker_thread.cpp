#include <thread/worker_thread.h>
#include <thread/task.h>
#include <thread/thread_pool.h>
using namespace hexu::thread;

#include <utility/logger.h>
#include <utility/singleton.h>
using namespace hexu::utility;

WorkerThread::WorkerThread() : Thread()
{
}

WorkerThread::~WorkerThread()
{
}

void WorkerThread::cleanup(void* ptr)
{
    log_info("worker thread cleanup handler: %x", ptr);
}

void WorkerThread::run()
{
    sigset_t mask;
    if (0 != sigfillset(&mask))
    {
        log_error("worker thread sigfillset faile!");
    }
    if (0 != pthread_sigmask(SIG_SETMASK, &mask, NULL))
    {
        log_error("worker thread pthread_sigmask failed");
    }
    pthread_cleanup_push(cleanup, this);//为了避免主线程主动终止子线程，但子线程有未被释放的资源从而造成内存泄漏

    while (true)
    {
        m_mutex.lock();
        while (m_task == nullptr)
            m_cond.wait(&m_mutex);//等待信号
        m_mutex.unlock();

        int rc = 0;
        int old_state = 0;//保留之前状态
        rc = pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, &old_state);//工作开始执行，状态设为ENABLE

        log_debug("worker thread run: thread=%x, task=%x", this, m_task);
        m_task->run();//任务执行
        m_task->destroy();//资源释放
        m_task = nullptr;

        Singleton<ThreadPool>::instance()->put(this);//将当前线程放回线程池

        rc = pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, &old_state);//工作执行完可以被取消，状态设为enabled
        pthread_testcancel(); // cancel-point  检查在disabled状态时是否有取消请求发送给本线程，若有则取消
    }
    pthread_cleanup_pop(1);
}
