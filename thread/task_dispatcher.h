#pragma once

#include <pthread.h>
#include <signal.h>
#include <list>
#include <thread/thread.h>
#include <thread/thread_pool.h>
#include <thread/task.h>

namespace hexu {
namespace thread {

class TaskDispatcher : public Thread
{
public:
    TaskDispatcher();
    ~TaskDispatcher();

    void init(int threads);
    void assign(Task* task);//保存到任务队列
    void handle(Task* task);
    bool empty();
    virtual void run();

protected:
    std::list<Task *> m_tasks;//任务队列
};

}}
