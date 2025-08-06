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
                cursor_move_up(&cursor);
                break;
            case KEY_DOWN:
            case 'j':
                cursor_move_down(&cursor);
                break;
            case KEY_LEFT:
            case 'h':
                cursor_move_left(&cursor);
                break;
            case KEY_RIGHT:
            case 'l':
                cursor_move_right(&cursor);
                break;
            case ' ':
                cursor_draw(&cursor);
                break;
            case 'q':
                goto end;
        }

        draw_yx(&cursor);
    }

end:
    /* 退出 */
    endwin();
    return 0;
}