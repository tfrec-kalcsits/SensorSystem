#pragma once


#include <thread>
#include <atomic>
#include <functional>

namespace sensorsystem
{

class ThreadProcess
{
    public:
    ThreadProcess(bool autostart=true);

    ~ThreadProcess();

    void startThreadProcess();

    void endThreadProcess();

    protected:
    virtual void thread_function() = 0;

    private:
    std::thread proc_thread;
    std::atomic_bool quit_proc;

    void mainProcLoop();
}

}