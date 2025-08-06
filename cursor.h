#ifndef CURSOR_H
#define CURSOR_H

typedef struct {
    int y, x;
} Cursor;

void cursor_move_up(Cursor *cursor);
void cursor_move_down(Cursor *cursor);
void cursor_move_left(Cursor *cursor);
void cursor_move_right(Cursor *cursor);
void cursor_move(Cursor *cursor);
void cursor_draw(Cursor *cursor, int color);

#endif