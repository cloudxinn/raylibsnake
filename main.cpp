#include "raylib.h"          
#include "structs.h"         
#include "global_var.h"       
#include <vector>            
#include <iostream>          
#include <fstream>            
#include <string>             
#define RAYGUI_IMPLEMENTATION 
#include "raygui.h"           

const int u = 40;               // 单元格大小
const int p = 120;              // 边距
static bool gamestart = false;  
static bool mapset = false;     
static bool configset = false; 
static bool mapset_create = false;   
static bool configset_create = false; 
double level = buff/ speed;          // 游戏速度

using namespace std; 
Vector2 mouse;

int main()
{
	InitWindow(1600, 1200, "SNAKE"); // 初始化窗口
	
	SetTargetFPS(60); // 设置帧率
	
	Image bg = LoadImage("res/tittle.png");  // 加载标题图像
	Texture tbg = LoadTextureFromImage(bg); // 从图像创建纹理
	setfont("res/font.ttf", 50);             // 设置字体
	
	// 游戏开始

	while (!gamestart)
	{
		BeginDrawing(); // 绘制
		
		ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR))); // 清空背景
		
		DrawTexture(tbg, 0, 0, WHITE); // 绘制标题
		
		// 绘制按钮
		gamestart = GuiButton((Rectangle){360, 700, 720, 100}, "开始游戏");
		mapset = GuiButton((Rectangle){360, 850, 300, 100}, "地图");
		configset = GuiButton((Rectangle){360, 1000, 300, 100}, "配置");
		mapset_create = GuiButton((Rectangle){800, 850, 280, 100}, "创建地图");
		configset_create = GuiButton((Rectangle){800, 1000, 280, 100}, "创建配置");
		
		EndDrawing(); // 结束绘制
		
		// 处理用户选择
		if (mapset)
		{
			setmap();
		}
		
		if (configset)
		{
			setconfig();
		}
		
		if (mapset_create)
		{
			create_map();
		}
		
		if (configset_create)
		{
			create_config();
		}
		
		if (WindowShouldClose())
		{
			return 0;
		}
	}
	
	UnloadImage(bg);    // 卸载标题
	UnloadTexture(tbg);
	
	begin_game(width + 2, length + 2); // 游戏初始化
	cout << width << endl << length;
	
	// 主循环
	
	while (!WindowShouldClose())
	{
		
		if (!gameover)
		{
			in_game();    //进行游戏
			draw_game();  // 绘制游戏界面
		}
		else
		{
			BeginDrawing(); // 开始绘制
			
			ClearBackground(WHITE); // 清空背景
			
			DrawText("score:", 560, 280, 120, BLACK);            
			DrawText(std::to_string(score).c_str(), 600, 520, 160, BLACK); // 绘制得分
			gameover = !GuiButton((Rectangle){520, 760, 560, 200}, "Once Again");
			if(!gameover) begin_game(width + 2, length + 2);
			EndDrawing(); // 结束绘制
		}
	}
	
	UnloadFont(font); 
	// end_game()
	return 0;
}
