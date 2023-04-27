#pragma once

#include <pthread.h>

namespace hexu {
namespace thread {
//解决了线程直接竞争的关系，互斥锁的类（封装了pthread中的mutex）
class Mutex
{
    friend class Condition;

public:
    Mutex();
    ~Mutex();

    // lock
    int lock();

    // try to lock
    int try_lock();

    // unlock
    int unlock();

private:
    pthread_mutex_t     m_mutex;
};

}}
