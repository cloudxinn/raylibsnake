#include"structs.h"
#include"raylib.h"
#include<vector>
#include"global_var.h"
#include "raygui.h"
bool gameover = false;
bool firststart = true;
int snake_length;
std::vector<_snake> snake;
std::vector<position> wall[4];
std::vector<position> obstacle;
std::vector<_apple> apple;
void begin_game(int m, int n)
{ 
	snake.clear();
	snake_Old.clear();
	wall[0].clear();
	wall[1].clear();
	wall[2].clear();
	wall[3].clear();
	obstacle.clear();
	apple.clear();
	for(int i = 0;i<4;i++)
	{
	snake.push_back({(_snake){width/2-i,length/2,0}});
	}
	for(int i=0;i<m;i++)
	{
		wall[0].push_back({(position){i, 0}});
		wall[1].push_back({(position){i, n-1}});
	}//up and down
	for(int i=0;i<n;i++)
	{
		wall[2].push_back({(position){0, i}});
		wall[3].push_back({(position){m-1, i}});
	}//left and right
	snake_length = snake.size();
	apple.push_back({7,7,0,false});
	return;
}
