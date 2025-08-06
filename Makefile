main: main.c
	gcc main.c cursor.c utils.c commands.c -o ttd -lncurses
