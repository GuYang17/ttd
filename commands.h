#ifndef COMMANDS_H
#define COMMANDS_H
#include "cursor.h"

void parse_and_exec_cmd(const char *cmd, Cursor *cursor, int color, char symbol);

#endif
