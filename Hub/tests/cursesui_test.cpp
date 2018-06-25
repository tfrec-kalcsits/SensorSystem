#include <hub/cursesui.h>

using namespace sensorsystem;

int main()
{
    CursesUI ui;
    bool quit = false;
    while(!quit)
    {
        auto in = ui.read();
        if(in && *in == "quit")
            quit = true;
        else
            ui.write(*in);
    }
}