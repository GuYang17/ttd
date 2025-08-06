#include <string.h>
#include <ctype.h>
#include <ncurses.h>
#include "cursor.h"
#include "commands.h"

void parse_and_exec_cmd(const char *cmd, Cursor *cursor, int color, char symbol)
{
    if (strncmp(cmd, "draw", 4) == 0)
    {
        const char *arg = cmd + 4;
        while (*arg == ' ')
            arg++;
        if (*arg == '\0')
        {
            cursor_draw(cursor, color, symbol);
        }
        else if (*arg == '+' || *arg == '-')
        {
            int dir = (*arg == '+') ? 1 : -1;
            arg++;
            if (isdigit(*arg))
            {
                int n = atoi(arg);
                for (int i = 0; i < n; i++)
                {
                    if (dir == 1 && cursor->x < COLS - 2)
                    {
                        cursor_move_right(cursor);
                        cursor_draw(cursor, color, symbol);
                    }
                    else if (dir == -1 && cursor->x > 1)
                    {
                        cursor_move_left(cursor);
                        cursor_draw(cursor, color, symbol);
                    }
                    else
                    {
                        break;
                    }
                }
            }
            else if (*arg == '*')   // 持续绘制直到边界
            {
                while ((dir == 1 && cursor->x < COLS - 2) || (dir == -1 && cursor->x > 1))
                {
                    if (dir == 1)
                        cursor_move_right(cursor);
                    else
                        cursor_move_left(cursor);
                    cursor_draw(cursor, color, symbol);
                }
            }
        }
        else if (*arg == '(' || *arg == ')')
        {
            int dir = (*arg == '(') ? -1 : 1; // ( 向上, ) 向下
            arg++;
            if (isdigit(*arg))
            {
                int n = atoi(arg);
                for (int i = 0; i < n; i++)
                {
                    if (dir == 1 && cursor->y < LINES - 3)
                    {
                        cursor_move_down(cursor);
                        cursor_draw(cursor, color, symbol);
                    }
                    else if (dir == -1 && cursor->y > 1)
                    {
                        cursor_move_up(cursor);
                        cursor_draw(cursor, color, symbol);
                    }
                    else
                    {
                        break;
                    }
                }
            }
            else if (*arg == '*')   // 持续绘制直到边界
            {
                while ((dir == 1 && cursor->y < LINES - 3) || (dir == -1 && cursor->y > 1))
                {
                    if (dir == 1)
                        cursor_move_down(cursor);
                    else
                        cursor_move_up(cursor);
                    cursor_draw(cursor, color, symbol);
                }
            }
        }
    }
    else if (strncmp(cmd, "move", 4) == 0)
    {
        const char *arg = cmd + 4;
        while (*arg == ' ') arg++;
        if (*arg == '\0') {
            cursor->y = 1;
            cursor->x = 1;
            cursor_move(cursor);
        } else {
            int y = 1, x = 1;
            if (sscanf(arg, "%d %d", &y, &x) == 2) {
                if (y < 1) y = 1;
                if (x < 1) x = 1;
                if (y > LINES-3) y = LINES-3;
                if (x > COLS-2) x = COLS-2;
                cursor->y = y;
                cursor->x = x;
                cursor_move(cursor);
            }
        }
    }
    else if (strncmp(cmd, "quit", 4) == 0)
    {
        endwin();
        exit(0);
    }
}
