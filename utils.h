#ifndef UTILS_H
#define UTILS_H

#include <ncurses.h>
#include "cursor.h"

void draw_border();
void draw_info(Cursor *cursor, int color, char symbol, int pen_size);

#endif
