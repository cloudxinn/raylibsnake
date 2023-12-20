#ifndef GLOBAL_VAR_H
#define GLOBAL_VAR_H
#include <vector>
#include <array>
#include <chrono>
#include <string>
#include "structs.h"
#include "raylib.h"
extern Image imgsnake_body;
extern Image imgsnake_head;
extern Image imgwall;
extern Image imgapple0;
extern Image imgapple1;
extern Image imgapple2;
extern Image imgmine;
extern Image imgmine2;
extern Image imgmine3;

extern std::vector<_snake> snake;
extern std::vector<_mine> mines;
extern std::vector<_snake> snake_Old;
extern std::vector<position> wall[4];
extern std::vector<position> obstacle;
extern std::vector<position> obstacletemp;
extern std::vector<_apple> apple;
extern std::array<bool,4> wallstatue;
extern bool gameover;
extern int snake_length;
extern const int u;
extern const int p;
extern int score;
extern int stepsSinceLastMine;
extern int width;
extern int length;
extern int obstacle_num;
extern double level;
extern bool firststart;
extern clock_t now;
extern char mapname[256];
extern char configname[256];
extern double speed;
extern char _seed[50];
extern int fruit_num;
extern int furit_pro[3];
extern int seed;
extern double buff;
extern char guitests[1000];
extern int codepointsCount;
extern int *codepoints;
extern Font font;
#endif
