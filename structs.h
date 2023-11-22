#ifndef STRUCT_H
#define STRUCT_H
#include "raylib.h"
#include<vector>
void begin_game(int m, int n);
void in_game(void);
void end_game(void);
void draw_game(void);
void setfont(const char *fileName, int fontSize);
struct position{
	int x;
	int y;
};
struct _snake{
	int x;
	int y;
	int direct;
};
//0-Right
//1-Left
//2-Up
//3-Down
#endif
