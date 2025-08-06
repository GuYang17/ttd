#include "cursor.h"
#include <ncurses.h>

void cursor_move_up(Cursor *cursor)
{
    if (cursor->y > 1)
    {
        cursor->y--;
        move(cursor->y, cursor->x);
    }
}

void cursor_move_down(Cursor *cursor)
{
    if (cursor->y < LINES - 3)
    {
        cursor->y++;
        move(cursor->y, cursor->x);
    }
}

void cursor_move_left(Cursor *cursor)
{
    if (cursor->x > 1)
    {
        cursor->x--;
        move(cursor->y, cursor->x);
    }
}

void cursor_move_right(Cursor *cursor)
{
    if (cursor->x < COLS - 2)
    {
        cursor->x++;
        move(cursor->y, cursor->x);
    }
}

void cursor_move(Cursor *cursor)
{
    move(cursor->y, cursor->x);
}

void cursor_draw(Cursor *cursor, int color, char ch, int pen_size) {
    attron(COLOR_PAIR(color));
    int half = pen_size / 2;
    for (int dy = -half; dy <= half; dy++) {
        for (int dx = -half; dx <= half; dx++) {
            int y = cursor->y + dy;
            int x = cursor->x + dx;
            if (y >= 1 && y < LINES - 2 && x >= 1 && x < COLS - 1) {
                mvaddch(y, x, ch);
            }
        }
    }
    attroff(COLOR_PAIR(color));
}