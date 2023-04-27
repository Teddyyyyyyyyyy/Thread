// 修复 windows 系统 min,max 宏冲突
#ifndef NOMINMAX
#define NOMINMAX
#endif

#include <iostream>
#include <unistd.h>
#include <utility/logger.h>
#include <utility/singleton.h>
using namespace hexu::utility;

// pthread 版本线程池
#include <thread/task.h>
#include <thread/task_dispatcher.h>
using namespace hexu::thread;

#include <task/echo_task.h>
using namespace hexu::task;

int main()
{
    // init logger
    Logger::instance()->open("./main.log");

    // init the task queue and thread pool
    int threads = 4;
    Singleton<TaskDispatcher>::instance()->init(threads);//创建TaskDispatcher并初始化
//采用饿汉模式,避免线程不安全
    for (int i = 0; i < 10; i++)
    {
        int * num = new int;
        *num = i;
        Task * task = new EchoTask(num);//十个任务创建
        Singleton<TaskDispatcher>::instance()->assign(task);//通过assign方法交给任务分发
    }

    while (!Singleton<TaskDispatcher>::instance()->empty())
    {
        sleep(1000);
    }
    return 0;
}

