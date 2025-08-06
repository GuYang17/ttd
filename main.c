#include <ncurses.h>
#include <string.h>
#include <ctype.h>
#include "cursor.h"
#include "utils.h"

#define CMD_BUF_SIZE 128

int mode = 0; // 0: normal, 1: command
char cmd_buf[CMD_BUF_SIZE] = {0};
int cmd_len = 0;

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
            else if (*arg == '*')
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
    }
}

int main()
{

    /* 初始化 */
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);   // 白色
    init_pair(2, COLOR_RED, COLOR_BLACK);     // 红色
    init_pair(3, COLOR_GREEN, COLOR_BLACK);   // 绿色
    init_pair(4, COLOR_BLUE, COLOR_BLACK);    // 蓝色
    init_pair(5, COLOR_YELLOW, COLOR_BLACK);  // 黄色
    init_pair(6, COLOR_MAGENTA, COLOR_BLACK); // 品红
    init_pair(7, COLOR_CYAN, COLOR_BLACK);    // 青色
    int current_color = 1;

    curs_set(1); // 始终显示光标

    char symbols[] = {'#', '*', '@', '%', '&', '$', '!'};
    int symbol_count = sizeof(symbols) / sizeof(symbols[0]);
    int symbol_index = 0;

    draw_border();

    Cursor cursor = {1, 1};
    cursor_move(&cursor);
    draw_info(&cursor, current_color, symbols[symbol_index]);

    while (1)
    {
        int ch = getch();
        if (mode == 0)
        {
            if (ch == ':')
            {
                mode = 1;
                cmd_len = 0;
                cmd_buf[0] = '\0';
                move(LINES - 1, 0);
                clrtoeol();
                mvprintw(LINES - 1, 0, ":");
                move(LINES - 1, 1);
                refresh();
                continue;
            }
            switch (ch)
            {

            // 向上
            case KEY_UP:
            case 'w':
                cursor_move_up(&cursor);
                break;

            // 向下
            case KEY_DOWN:
            case 's':
                cursor_move_down(&cursor);
                break;

            // 向左
            case KEY_LEFT:
            case 'a':
                cursor_move_left(&cursor);
                break;

            // 向右
            case KEY_RIGHT:
            case 'd':
                cursor_move_right(&cursor);
                break;

            // 绘制
            case ' ':
                cursor_draw(&cursor, current_color, symbols[symbol_index]);
                break;

            // 向前切换颜色
            case 'q':
                current_color--;
                if (current_color < 1)
                {
                    current_color = 7;
                }
                break;

            // 向后切换颜色
            case 'e':
                current_color++;
                if (current_color > 7)
                {
                    current_color = 1;
                }
                break;

            // 切换为第一个颜色
            case 'o':
                current_color = 1;
                break;

            // 切换为最后一个颜色
            case 'p':
                current_color = 7;
                break;

            // 向前切换符号
            case 'z':
                symbol_index--;
                if (symbol_index < 0)
                {
                    symbol_index = symbol_count - 1;
                }
                break;

            // 向后切换符号
            case 'c':
                symbol_index++;
                if (symbol_index >= symbol_count)
                {
                    symbol_index = 0;
                }
                break;

            // 切换为第一个符号
            case 'k':
                symbol_index = 0;
                break;

            // 切换为最后一个符号
            case 'l':
                symbol_index = symbol_count - 1;
                break;

            // 退出
            case 'x':
                goto end;
            }
            draw_info(&cursor, current_color, symbols[symbol_index]);
        }
        else
        {
            // 命令模式
            if (ch == 27)
            { // ESC
                mode = 0;
                draw_info(&cursor, current_color, symbols[symbol_index]);
                continue;
            }
            else if (ch == KEY_BACKSPACE || ch == 127)
            {
                if (cmd_len > 0)
                {
                    cmd_len--;
                    cmd_buf[cmd_len] = '\0';
                }
            }
            else if (ch == '\n' || ch == '\r')
            {
                parse_and_exec_cmd(cmd_buf, &cursor, current_color, symbols[symbol_index]);
                mode = 0;
                draw_info(&cursor, current_color, symbols[symbol_index]);
                continue;
            }
            else if (isprint(ch) && cmd_len < CMD_BUF_SIZE - 1)
            {
                cmd_buf[cmd_len++] = ch;
                cmd_buf[cmd_len] = '\0';
            }
            move(LINES - 1, 0);
            clrtoeol();
            mvprintw(LINES - 1, 0, ":%s", cmd_buf);
            move(LINES - 1, 1 + cmd_len);
            refresh();
        }
    }

end:
    /* 退出 */
    endwin();
    return 0;
}