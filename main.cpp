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
static bool mapset = false;
static bool configset = false;
static bool mapset_create = false;
static bool configset_create = false;
double level = 1.0/speed;
using namespace std; 
Vector2 mouse;//TODO unused??
int main()
{
	InitWindow(1600, 1200, "SNAKE"); 
	SetTargetFPS(60);
	Image bg = LoadImage("res/tittle.png");
	Texture tbg = LoadTextureFromImage(bg);
	setfont("res/font.ttf",50);
	while(!gamestart)
	{
		BeginDrawing();
		ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR))); 
		DrawTexture(tbg,0,0,WHITE);
		gamestart = GuiButton((Rectangle){ 360, 700, 720, 100 }, "开始游戏"); 
		mapset = GuiButton((Rectangle){ 360, 850, 300, 100 }, "地图"); 
		configset = GuiButton((Rectangle){ 360, 1000, 300, 100 }, "配置"); 
		mapset_create = GuiButton((Rectangle){ 800, 850, 280, 100 }, "创建地图"); 
		configset_create = GuiButton((Rectangle){ 800, 1000, 280, 100 }, "创建配置"); 
		EndDrawing();
		if(mapset)
		{
			setmap();
		}
		if(configset)
		{
			setconfig();
		}
		if(mapset_create)
		{
			create_map();
		}
		if(configset_create)
		{
			create_config();
		}
		if(WindowShouldClose())
		{
			return 0;
		}
	}
	UnloadImage(bg);
	UnloadTexture(tbg);
	begin_game(width+2,length+2);
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
	UnloadFont(font);
	//end_game()
	return 0;
}
