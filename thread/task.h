#pragma once

namespace hexu {
namespace thread {
//任务接口
class Task
{
public:
    Task();
    Task(void* data);
    virtual ~Task();

    void* get_data();
    void set_data(void* data);

//在EchoTask中要实现这俩个方法
    virtual void run() = 0;
    virtual void destroy() = 0;

protected:
    void*       m_data;
};

}}
