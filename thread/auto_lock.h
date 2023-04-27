#pragma once

#include <thread/mutex.h>

namespace hexu {
namespace thread {

class AutoLock
{
public:
    AutoLock(Mutex* mutex);
    ~AutoLock();

private:
    Mutex* m_mutex;
};

}}
