#include "structs.h" 
#include "raylib.h" 
#include <fstream>
#include <iostream>
#include <vector> 
#include <cstdlib>
#include "global_var.h" 
#include "raygui.h" 
static std::chrono::steady_clock::time_point timeold;
using std::ifstream;
using std::ios;
bool close = false;
static void reupdate();
static ifstream rec;
void replayrecord()
{	
	rec.open("record/new.rec", ios::in);
	rec >> configname;
	std::string config_filestring = "config/";
	config_filestring += configname;
	ifstream _config(config_filestring.c_str(), ios::in);
	_config >> speed >> seed >> fruit_num;
	furit_pro[0] = _config.get() * 10;
	furit_pro[1] = _config.get() * 10;
	furit_pro[2] = _config.get() * 10;
	_config.close();
	
	rec >> mapname;
	std::string map_filestring = "maps/";
	map_filestring += mapname;
	ifstream _map(map_filestring.c_str(), ios::in);
	_map >> width >> length >> wallstatue[0] >> wallstatue[1] >> wallstatue[2] >> wallstatue[3] >> obstacle_num;
	obstacletemp.clear();
	for (int i = 0; i < obstacle_num; i++)
	{
		position ob;
		_map >> ob.x >> ob.y;
		obstacletemp.push_back(ob);
	}
	_map.close();
	
	begin_game(width + 2, length + 2);
	while(!close)
	{
		if (WindowShouldClose())
		{
			close = true;
		}
		snake_Old.clear();
		for (unsigned i = 0; i < snake.size(); i++)
		{
			snake_Old.push_back(snake[i]);
		}
		level = 0.1;
		if (clock() - now >= 1000 * level)
		{
			reupdate();
			now = clock();
		}
		draw_game();
	}
	close = false;
	rec.close();
	return;
}
void reupdate()
{
	char tempc='\0';
	int temp[3]{0};
	apple.clear();
	mines.clear();
	
	while(tempc!='N')
	{
		if(!rec) 
		{
			close = true;
			return;
		}
		rec >> tempc;
		std::cout << tempc << std::endl;
		switch (tempc)
		{
		case 'F':
			rec >> temp[0] >> temp[1] >> temp[2];
			std::cout << temp[0] << temp[1] << temp[2] << std::endl;
			apple.push_back({temp[0],temp[1],temp[2],false});
			break;
		case 'M':
			rec >> temp[0] >> temp[1] >> temp[2];
			std::cout << temp[0] << temp[1] << temp[2] << std::endl;
			mines.push_back({temp[0],temp[1],temp[2],true});
			break;
		case 'A':
			snake[0].x -= 1;
			break;
		case 'W':
			snake[0].y -= 1;
			break;	
		case 'D':
			snake[0].x += 1;
			break;
		case 'S':
			snake[0].y += 1;
			break;
		case '+':
			snake.push_back(snake_Old.back());
			break;
			default:break;
		}	
	}
	if (snake[0].x > width )
	{
		snake[0].x = snake[0].x - width;
	}
	if (snake[0].x <1 )
	{
		snake[0].x = snake[0].x +width;
	}
	// 如果蛇头超出屏幕宽度范围，（虚墙）将蛇头移到另一侧（实墙）游戏结束
	
	if (snake[0].y > length )
	{
		snake[0].y = snake[0].y - length;
	}
	if (snake[0].y <1 )
	{
		snake[0].y = snake[0].y + length;
	}
	// 如果蛇头超出屏幕高度范围，（虚墙）将蛇头移到另一侧（实墙）游戏结束
	for (unsigned int i = 1; i < snake.size(); i++)
	{
		snake[i] = snake_Old[i - 1];
	}
}
