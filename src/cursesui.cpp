#include <hub/cursesui.h>

namespace sensorsystem
{

CursesUI::CursesUI()
{
    initscr();
    cbreak();
    nodelay(stdscr, TRUE);
    getmaxyx(stdscr, lines, cols);
    out = newwin(lines - 2, cols - 1, 0, 0);
    in = newwin(1, cols - 1, lines - 1, 0);
    nodelay(in, TRUE);
    wmove(in, 0, 0);
    waddstr(in, "> ");
    refresh();
}

void CursesUI::write(sv::string_view output)
{
    waddstr(out, output.data());
    wrefresh(out);
}

opt::optional<std::string> CursesUI::read()
{
    bool quit = false;
    while(!quit)
    {
        int ch = wgetch(in);
        switch(ch)
        {
            case ERR: quit = true;
                break;
            case 10:
                input.push(buffer);
                buffer = "";
                werase(in);
                break;
            default:
                buffer += (char)ch;
        }
    }

    if(!input.empty())
    {
        std::string ret = input.front();
        input.pop();
        return {ret};
    }

    return {};
}

CursesUI::~CursesUI()
{
    delwin(in);
    delwin(out);
    endwin();
}

}