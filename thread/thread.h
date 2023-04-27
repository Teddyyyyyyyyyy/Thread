#pragma once
//对Linux下pthread进行了一层封装
#include <pthread.h>
#include <thread/mutex.h>
#include <thread/condition.h>
#include <thread/task.h>

namespace hexu {
namespace thread {

class Thread
{
public:
    Thread();
    virtual ~Thread();

    virtual void run() = 0;

    void start();
    void stop();

    void set_task(Task* task);
    Task* get_task();

protected:
    static void* thread_func(void* ptr);

protected:
    pthread_t           m_tid;//线程ID
    Task*               m_task;//任务
    Mutex               m_mutex;
    Condition           m_cond;
};

}}
