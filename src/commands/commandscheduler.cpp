#include <hub/commands/commandscheduler.h>

namespace sensorsystem
{

CommandScheduler::CommandScheduler()
{
}

void CommandScheduler::scheduleCommand(std::shared_ptr<Command> command)
{
    queue_lock.lock();
    queue.push(command);
    queue_lock.unlock();
}

void CommandScheduler::threadFunction()
{
    queue_lock.lock();
    bool empty = queue.empty();
    queue_lock.unlock();

    if(!empty)
    {
        queue_lock.lock();
        auto current_command = queue.top();
        queue.pop();
        queue_lock.unlock();
        current_command->execute();
    }
}


}