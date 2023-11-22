#include"raylib.h"
#include"structs.h"
#include"global_var.h"
#include<vector>
#include<iostream>
#include<fstream>
#include<string>
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
const int u = 40;
const int p = 120;
static bool gamestart = false;
std::vector<position> obstacle;
int width = 15, length =15;
double level = 1.0/10;
using namespace std; 
Vector2 mouse;//TODO unused??
int main()
{
	ifstream map("maps/default.map",ios::in);
	ifstream config("config/default.config",ios::in);
	//open file
	//TODO NEED function to check if input valid
	if(!map) return 1;
	InitWindow(1600, 1200, "SNAKE"); 
	int wall_status[4]={1};
	int obstacle_num = 0;
	//mute value
	map >> width >> length
		>> wall_status[0] >> wall_status[1]
		>> wall_status[2] >> wall_status[3]
		>> obstacle_num;
	for(int i=0;i<obstacle_num;i++)
	{
		position ob;
		map >> ob.x >> ob.y;
		obstacle.push_back(ob);
	}
	map.close();
	begin_game(width+2,length+2);
	SetTargetFPS(60);
	Image bg = LoadImage("res/tittle.png");
	Texture tbg = LoadTextureFromImage(bg);
	setfont("res/font.ttf",200);
	while(!gamestart)
	{
		
		BeginDrawing();
		ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR))); 
		DrawTexture(tbg,0,0,WHITE);
		gamestart = GuiButton((Rectangle){ 368, 792, 736, 195 }, "开始游戏"); 
		EndDrawing();
		
		if(WindowShouldClose())
		{
			return 0;
		}
	}
	UnloadImage(bg);
	UnloadTexture(tbg);
	while(!WindowShouldClose())
	{
		if(!gameover)
		{
		in_game();
		draw_game();
		}
		else
		{
			BeginDrawing();
			ClearBackground(WHITE);
			DrawText("score:",560,280,120,BLACK);
			DrawText(std::to_string(score).c_str(),600,520,160,BLACK);
			EndDrawing();
		}
	}
	//end_game();
	config.close();
	//TODO use costom config
	return 0;
}
