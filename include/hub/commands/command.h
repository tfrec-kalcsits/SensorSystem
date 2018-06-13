#pragma once

namespace sensorsystem
{

class Command
{
    public:
    virtual void execute() = 0;
    bool operator>(const Command& other) const;
    bool operator<(const Command& other) const;
    int getPriority() const;
    void setPriority();

    private:
    int priority;
};

}