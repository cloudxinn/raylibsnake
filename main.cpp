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
static bool replay = false;
static bool save_record = false;
char recordname[255];
char input[255]="new.rec";
double level = buff/ speed;          // 游戏速度
using namespace std; 
Vector2 mouse;

Image imgsnake_body = LoadImage("res/snake_body.png");
Image imgsnake_head = LoadImage("res/snake_head.png");
Image imgwall = LoadImage("res/wall.png");
Image imgapple[3] = {LoadImage("res/apple_0.png"),LoadImage("res/apple_1.png"),LoadImage("res/apple_2.png")};
Image imgmine[3] = {LoadImage("res/mine.png"),LoadImage("res/mine2.png"),LoadImage("res/mine3.png")};
Texture twall;
Texture tbody;
Texture thead;
Texture tmine[3];
Texture tapple[3];
clock_t now = clock();
int main()
{

	InitWindow(1600, 1200, "SNAKE"); // 初始化窗口
	SetTargetFPS(60); // 设置帧率
	Image bg = LoadImage("res/tittle.png");  // 加载标题图像
	Texture tbg = LoadTextureFromImage(bg); // 从图像创建纹理
	twall = LoadTextureFromImage(imgwall);
	setfont("res/font.ttf", 50);             // 设置字体
	//加载资源
	tbody = LoadTextureFromImage(imgsnake_body);
	thead = LoadTextureFromImage(imgsnake_head);
	for(int i=0;i<3;i++)
	{
		tmine[i] = LoadTextureFromImage(imgmine[i]);
		tapple[i] = LoadTextureFromImage(imgapple[i]);
	}
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
		replay = GuiButton((Rectangle){1120, 1000, 280, 100}, "游戏回放");

		EndDrawing(); // 结束绘制
		if(replay)
		{
			replayrecord();
		}
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
	now = clock();
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
			if(GuiButton((Rectangle){520, 960, 560, 200}, GuiIconText(ICON_FILE_SAVE, "Save File"))) 
			{
				save_record = true;
				setfont("res/font.ttf", 30);
			}
			if(save_record)
			{
			
				DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(RAYWHITE, 0.8f));
				int result = GuiTextInputBox((Rectangle){ (float)GetScreenWidth()/2 - 120, (float)GetScreenHeight()/2 - 60, 400, 200 }, "Save", GuiIconText(ICON_FILE_SAVE, "Save file as..."), "Ok;Cancel", input, 255, NULL);
				if (result == 1)
				{
					strcpy(recordname, input);
					std::string _filerecord = "record/";
					_filerecord+=recordname;
					ofstream _record(_filerecord.c_str(),ios::out);
					for(auto out:record)
					{
						_record << out;
					}
					_record.close();
					ofstream recordlist("record/record.list",ios::app);
					recordlist << recordname << endl;
					recordlist.close();
				}
				if ((result == 0) || (result == 1) || (result == 2))
				{
					save_record = false;
					strcpy(input, "\0");
				}
			}
			if(!gameover) 
			{
				begin_game(width + 2, length + 2);
				setfont("res/font.ttf", 50);
			}
			EndDrawing(); // 结束绘制
		}
	}

	UnloadImage(imgsnake_body);
	UnloadImage(imgsnake_head);
	UnloadImage(imgwall);
	for(int i=0;i<3;i++)
	{
	UnloadImage(imgapple[i]);
	UnloadImage(imgmine[i]);
	UnloadTexture(tmine[i]);
	UnloadTexture(tapple[i]);
	}
	UnloadTexture(twall);
	UnloadTexture(tbody);
	UnloadTexture(thead);
	UnloadFont(font); 
	return 0;
}
