#ifndef GLOBAL_VAR_H
#define GLOBAL_VAR_H
#include<vector>
#include<chrono>
#include"structs.h"
#include"raylib.h"

extern std::vector<_snake> snake;
extern std::vector<_snake> snake_Old;
extern std::vector<position> wall[4];
extern std::vector<position> obstacle;
extern std::vector<_apple> apple;
extern bool gameover;
extern int snake_length;
extern const int u;
extern const int p;
extern int score;
extern int width;
extern int length;
extern int obstacle_num;
extern double level;
extern bool firststart;
extern clock_t now;

extern double speed;
extern int seed;
extern int fruit_num;
extern int furit_pro[3];

extern char guitests[50];
extern int codepointsCount;
extern int *codepoints;
extern Font font;
#endif
