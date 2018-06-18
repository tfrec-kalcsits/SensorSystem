#pragma once

#include <string>
#include <queue>
#include <curses.h>
#include <hub/compatibility.h>

namespace sensorsystem
{

class CursesUI
{
    public:
    CursesUI();
    ~CursesUI();

    void write(sv::string_view output);
    opt::optional<std::string> read();

    private:
    WINDOW * out;
    WINDOW * in;
    int lines, cols;
    std::string buffer;
    std::queue<std::string> input;
    
};

}