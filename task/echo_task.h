#pragma once

#include <thread/task.h>
using namespace hexu::thread;

namespace hexu {
namespace hexu {

class EchoTask : public Task
{
public:
    EchoTask(int * num) : Task((void *)num) {}
    virtual ~EchoTask() {}

    virtual void run()
    {
        printf("task run\n");
        int * input = static_cast<int *>(m_data);
        printf("num: %d\n", *input);
    }

    virtual void destroy()
    {
        printf("task destory\n");
        delete static_cast<int *>(m_data);
        delete this;
    }
};

}}
