#pragma once

#include <pthread.h>
#include <thread/mutex.h>
//条件变量
namespace hexu {
namespace thread {

class Condition
{
public:
    Condition();
    ~Condition();

    int wait(Mutex* mutex);
    int signal();
    int broadcast();

protected:
    pthread_cond_t      m_cond;
    //pthread_condattr_t  m_attr;

};

}}
