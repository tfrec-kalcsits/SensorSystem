#pragma once

#include <hub/threadprocess.h>


namespace sensorsystem
{

ThreadProcess::ThreadProcess(bool autostart)
{
    if(autostart)
        startThreadProcess();
}

ThreadProcess::~ThreadProcess()
{
    endThreadProcess();
}

void ThreadProcess::startThreadProcess()
{
    if(!proc_thread.joinable())
    {
        quit_proc = false;
        proc_thread = std::thread(&ThreadProcess::mainProcLoop, this);
    }
}

void ThreadProcess::endThreadProcess()
{
    if(proc_thread.joinable())
    {
        quit_proc = true;
        proc_thread.join();
    }
}

void ThreadProcess::mainProcLoop()
{
    while(!quit_proc)
        threadFunction();
}
    
} // sensorsystem