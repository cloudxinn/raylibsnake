#ifndef STRUCT_H
#define STRUCT_H
#include "raylib.h"
#include <vector>
struct position{
	int x;
	int y;
};
struct _snake{
	int x;
	int y;
	int direct;
};
struct _apple{
	int x;
	int y;
	int type=2;
	bool ate = false;
};
struct _mine {
	int x;
	int y;
	int ty=1;
	bool active;
};
void begin_game(int m, int n);
void in_game(void);
void end_game(void);
void draw_game(void);
void setfont(const char *fileName, int fontSize);
bool setmap(void);
bool setconfig(void);
bool create_config(void);
bool create_map(void);
_apple rand_apple();
position rand_position();
bool check_apple(_apple);
bool check_mine(_mine);
void replayrecord();
void fault();
//0-Right
//1-Left
//2-Up
//3-Down
#endif
