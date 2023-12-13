#include "structs.h" 
#include "raylib.h" 
#include <vector> 
#include "global_var.h" 
#include "raygui.h" 

bool gameover = false; 
bool firststart = true; 
int snake_length; // 蛇的长度
std::vector<_snake> snake; // 蛇的信息
std::vector<position> wall[4]; // 四个方向墙壁的向量
std::vector<position> obstacle; // 障碍物
std::vector<_apple> apple; // 苹果

void begin_game(int m, int n)
{ 
	//清空历史信息
	snake.clear(); 
	snake_Old.clear(); 
	wall[0].clear(); 
	wall[1].clear(); 
	wall[2].clear(); 
	wall[3].clear();  
	apple.clear(); 
	
	for (int i = 0; i < 4; i++)
	{
		snake.push_back({(_snake){width / 2 - i, length / 2, 0}}); // 初始化蛇的位置
	}
	
	for (int i = 0; i < m; i++)
	{
		wall[0].push_back({(position){i, 0}}); 
		wall[1].push_back({(position){i, n - 1}}); 
	} // 初始化上下墙壁
	
	for (int i = 0; i < n; i++)
	{
		wall[2].push_back({(position){0, i}}); 
		wall[3].push_back({(position){m - 1, i}}); 
	} // 初始化左右墙壁
	
	obstacle=obstacletemp;
	snake_length = snake.size(); // 获取蛇的初始长度
	apple.push_back({3, 2, 0, false}); // 初始化一个苹果的位置
	return;
}
