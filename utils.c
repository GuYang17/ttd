#include <ncurses.h>
#include "cursor.h"

void draw_border()
{
    mvaddch(0, 0, ACS_ULCORNER); // 左上角
    for (int i = 1; i < COLS - 1; i++)
    {
        mvaddch(0, i, ACS_HLINE); // 顶部
    }
    mvaddch(0, COLS - 1, ACS_URCORNER); // 右上角
    for (int i = 1; i < LINES - 1; i++)
    {
        mvaddch(i, 0, ACS_VLINE);        // 左侧
        mvaddch(i, COLS - 1, ACS_VLINE); // 右侧
    }
    mvaddch(LINES - 2, 0, ACS_LLCORNER); // 左下角
    for (int i = 1; i < COLS - 1; i++)
    {
        mvaddch(LINES - 2, i, ACS_HLINE); // 底部
    }
    mvaddch(LINES - 2, COLS - 1, ACS_LRCORNER); // 右下角
}

void draw_info(Cursor *cursor, int color, char symbol)
{
    move(LINES - 1, 0);
    clrtoeol();
    mvprintw(LINES - 1, 0, "(%d, %d)", cursor->y, cursor->x);

    attron(COLOR_PAIR(color));
    mvaddch(LINES - 1, COLS - 2, symbol);
    attroff(COLOR_PAIR(color));

    move(cursor->y, cursor->x);
    refresh();
}