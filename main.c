#include <ncurses.h>
#include <string.h>
#include <ctype.h>
#include "cursor.h"
#include "utils.h"
#include "commands.h"

#define CMD_BUF_SIZE 128

int mode = 0; // 0: normal, 1: command
char cmd_buf[CMD_BUF_SIZE] = {0};
int cmd_len = 0;

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

    int pen_size = 1;

    curs_set(1); // 始终显示光标

    char symbols[] = {'#', '*', '@', '%', '&', '$', '!'};
    int symbol_count = sizeof(symbols) / sizeof(symbols[0]);
    int symbol_index = 0;

    draw_border();

    Cursor cursor = {1, 1};
    cursor_move(&cursor);
    draw_info(&cursor, current_color, symbols[symbol_index], pen_size);

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
                cursor_draw(&cursor, current_color, symbols[symbol_index], pen_size);
                break;

            // 橡皮
            case 'i':
                cursor_draw(&cursor, current_color, ' ', pen_size);
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

            // 减小画笔粗细
            case 'n':
                if (pen_size > 1)
                {
                    pen_size--;
                }
                break;
            
            // 增大画笔粗细
            case 'm':
                if (pen_size < 10)
                {
                    pen_size++;
                }
                break;
            
            // 重置画笔粗细
            case 'b':
                pen_size = 1;
                break;

            // 退出
            case 'x':
                goto end;
            }
            draw_info(&cursor, current_color, symbols[symbol_index], pen_size);
        }
        else
        {
            // 命令模式
            if (ch == 27)
            { // ESC
                mode = 0;
                draw_info(&cursor, current_color, symbols[symbol_index], pen_size);
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
                draw_info(&cursor, current_color, symbols[symbol_index], pen_size);
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