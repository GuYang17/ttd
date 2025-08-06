#include <ncurses.h>
#include "cursor.h"
#include "utils.h"

int main() {
    
    /* 初始化 */
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK); // 白色
    init_pair(2, COLOR_RED, COLOR_BLACK);   // 红色
    init_pair(3, COLOR_GREEN, COLOR_BLACK); // 绿色
    init_pair(4, COLOR_BLUE, COLOR_BLACK);  // 蓝色
    init_pair(5, COLOR_YELLOW, COLOR_BLACK); // 黄色
    init_pair(6, COLOR_MAGENTA, COLOR_BLACK); // 品红
    init_pair(7, COLOR_CYAN, COLOR_BLACK);  // 青色
    int current_color = 1;

    curs_set(1);    // 始终显示光标

    draw_border();

    Cursor cursor = {1, 1};
    cursor_move(&cursor);
    draw_yx(&cursor);

    while (1) {
        int ch = getch();
        switch (ch) {
            case KEY_UP:
            case 'k':
            case 'w':
                cursor_move_up(&cursor);
                break;
            case KEY_DOWN:
            case 'j':
            case 's':
                cursor_move_down(&cursor);
                break;
            case KEY_LEFT:
            case 'h':
            case 'a':
                cursor_move_left(&cursor);
                break;
            case KEY_RIGHT:
            case 'l':
            case 'd':
                cursor_move_right(&cursor);
                break;
            case ' ':
                cursor_draw(&cursor, current_color);
                break;
            case 'q':
                current_color--;
                if (current_color < 1) {
                    current_color = 7;
                }
                break;
            case 'e':
                current_color++;
                if (current_color > 7) {
                    current_color = 1;
                }
                break;
            case 'o':
                current_color = 1;
                break;
            case 'p':
                current_color = 7;
                break;
            case 'x':
                goto end;
        }

        draw_yx(&cursor);
    }

end:
    /* 退出 */
    endwin();
    return 0;
}