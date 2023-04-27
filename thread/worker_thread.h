#pragma once

#include <pthread.h>
#include <signal.h>

#include <thread/thread.h>

namespace hexu {
namespace thread {

class WorkerThread : public Thread
{
public:
    WorkerThread();
    virtual ~WorkerThread();

    virtual void run();

    static void cleanup(void* ptr);
};

}}
