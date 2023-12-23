#include "structs.h" 
#include "raylib.h" 
#include <fstream>
#include <iostream>
#include <vector> 
#include <cstdlib>
#include <cstring>
#include "global_var.h" 
#include "raygui.h" 
static std::chrono::steady_clock::time_point timeold;
using std::ifstream;
using std::ios;
bool close = false;
static void reupdate();
static ifstream rec;
double recordspeed=0;
void replayrecord()
{	
	bool lastpage = false;
	bool nextpage = false;
	bool next =false;
	unsigned next_num = 0;
	ifstream _recordlist("record/record.list", ios::in);
	std::vector<std::string> recordlist;
	while (_recordlist)
	{
		std::string temp;
		_recordlist >> temp;
		recordlist.push_back(temp);
	}
	_recordlist.close();
	recordlist.pop_back();
	bool con[recordlist.size()] = {false};
	
	while (!next)
	{	
		BeginDrawing();
		ClearBackground(RAYWHITE);
		recordspeed = GuiSliderBar((Rectangle){200, 920, 300, 60}, "回放速度", TextFormat("%.2f", recordspeed), recordspeed, 0.5, 2.0);
		DrawText("0.5x--2x", 200, 880, 40, BLACK);
		next = GuiButton((Rectangle){800, 920, 680, 80}, "继续") || WindowShouldClose();	
		if(next) break;
		// 上一页
		lastpage = GuiButton((Rectangle){1240, 320, 320, 120}, "上一页") || WindowShouldClose();
		// 下一页
		nextpage = GuiButton((Rectangle){1240, 520, 320, 120}, "下一页") || WindowShouldClose();
		// 绘制列表
		
		for (unsigned i = 0; i < recordlist.size(); i++)
		{
			con[i] = false;
		}
		for (unsigned i = next_num; i < next_num + 5 && i < recordlist.size(); i++)
		{
			con[i] = GuiButton((Rectangle){240, (float)200 + (i - next_num) * 120, 880, 120}, recordlist[i].c_str());
		}
			
		// 翻页
		if (nextpage)
		{
			next_num += 5;
			if (next_num >= recordlist.size())
				next_num -= 5;
		}
			
		if (lastpage && next_num >= 5)
		{
			next_num -= 5;
		}
		for (unsigned i = 0; i < recordlist.size(); i++)
		{
			if (con[i])
			{
				recordlist.push_back(recordlist[i]);
				next = true;
				break;
			}
		}
		EndDrawing();
	}
		
	std::string _filestring = "record/";
	_filestring += recordlist.back();
	rec.open(_filestring.c_str(), ios::in);
	rec >> configname;
	std::string config_filestring = "config/";
	config_filestring += configname;
	ifstream _config(config_filestring.c_str(), ios::in);
	_config >> speed >> seed >> fruit_num;
	furit_pro[0] = _config.get() * 10;
	furit_pro[1] = _config.get() * 10;
	furit_pro[2] = _config.get() * 10;
	_config.close();
	
	
	level = (recordspeed*buff)/speed;
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
		level=0.5;
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
	int applescore=0;
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
			rec >> applescore;
			score+=applescore;
			break;
		case 'X':
			return;
			break;
			default:break;
		}	
	}
	for (unsigned int i = 1; i < snake.size(); i++)
	{
		snake[i] = snake_Old[i - 1];
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

}


