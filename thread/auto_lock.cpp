#include <thread/auto_lock.h>
using namespace hexu::thread;
//自动锁
AutoLock::AutoLock(Mutex* mutex)
{
    m_mutex = mutex;
    m_mutex->lock();
}

AutoLock::~AutoLock()
{
    m_mutex->unlock();
}
