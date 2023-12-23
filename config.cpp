#include "raylib.h"
#include "structs.h"
#include "global_var.h"
#include "raygui.h"
#include <fstream>
#include <iostream>
#include <cmath>
#include <vector>
#include <array>
#include <string>
#include <cstring>
#include <sstream>

using std::ofstream;
using std::ifstream;
using std::ios;
using std::vector;
using std::array;
using std::cout;
using std::endl;
using std::string;

// 变量初始化
int width = 20, length = 20;
int obstacle_num = 0;
double speed = 10;
char _seed[50] = "-1";
int seed = -1;
int _applepro[3]={1,3,6};
int fruit_num = 5;
int furit_pro[3] = {6, 3, 1}; // 10 points express probability
std::vector<position> obstacletemp;
char mapname[256] = "new.map";
char inputs[256] = "";
std::stringstream cli_stream;
string mapnamestring;
bool maptextBoxEditMode = false;
bool maptextBox0EditMode = false;
bool maptextBox1EditMode = false;
bool maptextBox2EditMode = false;
bool maptextBox3EditMode = false;
bool maptextBox4EditMode = false;

char configname[256] = "new.config";
string confignamestring;
bool configtextBoxEditMode = false;

// 游戏板和墙壁状态
vector<vector<bool>> gameboard;

//墙壁状态储存数组
array<bool,4> wallstatue;


void DrawStyleEditControls(void);

bool setmap(void);
bool setconfig(void);
bool create_config(void);
bool create_map(void);
void fault(){
	bool msg_box=true;
	while (msg_box)
	{
		BeginDrawing();
		ClearBackground(WHITE);	
		DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(RAYWHITE, 0.8f));
		int result = GuiMessageBox((Rectangle){ (float)GetScreenWidth()/2 - 200, (float)GetScreenHeight()/2 - 200, 640, 200 }, GuiIconText(ICON_CPU, "ERROR"), "非法输入", "返回");	
		if ((result == 1) || (result == 0)) msg_box = false;
		if(!msg_box)
		{
			setfont("res/font.ttf", 50);
		}
		EndDrawing();
	}
}
// 设置地图函数
bool setmap(void)
{
	bool exit = false;
	
	
	ifstream _maplist("maps/maps.list", ios::in);
	std::vector<std::string> maplist;
	while (_maplist)
	{
		std::string temp;
		_maplist >> temp;
		maplist.push_back(temp);
	}
	maplist.pop_back();
	bool con[maplist.size()] = {false};
	
	bool lastpage = false;
	bool nextpage = false;
	unsigned next_num = 0;
	
	// 显示配置地图界面
	while (!exit)
	{
		BeginDrawing();
		ClearBackground(WHITE);
		
		// 返回
		exit = GuiButton((Rectangle){800, 920, 680, 80}, "返回") || WindowShouldClose();
		
		// 上一页
		lastpage = GuiButton((Rectangle){1240, 320, 320, 120}, "上一页") || WindowShouldClose();
		
		// 下一页
		nextpage = GuiButton((Rectangle){1240, 520, 320, 120}, "下一页") || WindowShouldClose();
		
		// 绘制列表
		for (unsigned i = 0; i < maplist.size(); i++)
		{
			con[i] = false;
		}
		
		for (unsigned i = next_num; i < next_num + 5 && i < maplist.size(); i++)
		{
			con[i] = GuiButton((Rectangle){240, (float)200 + (i - next_num) * 120, 880, 120}, maplist[i].c_str());
		}
		
		// 翻页
		if (nextpage)
		{
			next_num += 5;
			if (next_num >= maplist.size())
				next_num -= 5;
		}
		
		if (lastpage && next_num >= 5)
		{
			next_num -= 5;
		}
		
		// 选中地图项
		for (unsigned i = 0; i < maplist.size(); i++)
		{
			if (con[i])
			{
				maplist.push_back(maplist[i]);
				exit = true;
				break;
			}
		}
		
		EndDrawing();
	}
	
	std::string _filestring = "maps/";
	strcpy(mapname,maplist.back().c_str());
	_filestring += maplist.back();
	ifstream _map(_filestring.c_str(), ios::in);
	// 读取地图文件
	if (!_map)
		return false;
	
	// 读取地图信息
	_map >> width >> length >> wallstatue[0] >> wallstatue[1] >> wallstatue[2] >> wallstatue[3] >> obstacle_num;
	obstacletemp.clear();
	// 读取障碍物位置
	for (int i = 0; i < obstacle_num; i++)
	{
		position ob;
		_map >> ob.x >> ob.y;
		obstacletemp.push_back(ob);
	}
	
	_map.close();
	return true;
}

// 配置函数
bool setconfig(void)
{
	bool exit = false;

	ifstream _configlist("config/configs.list", ios::in);
	std::vector<std::string> configlist;
	while (_configlist)
	{
		std::string temp;
		_configlist >> temp;
		configlist.push_back(temp);
	}
	configlist.pop_back();
	bool con[configlist.size()] = {false};
	bool lastpage = false;
	bool nextpage = false;
	unsigned next_num = 0;
	
	// 显示配置设置界面
	while (!exit)
	{
		BeginDrawing();
		ClearBackground(WHITE);
		
		// 返回
		exit = GuiButton((Rectangle){800, 920, 680, 80}, "返回") || WindowShouldClose();
		
		// 上一页
		lastpage = GuiButton((Rectangle){1240, 320, 320, 120}, "上一页") || WindowShouldClose();
		
		// 下一页
		nextpage = GuiButton((Rectangle){1240, 520, 320, 120}, "下一页") || WindowShouldClose();
		
		// 绘制列表
		for (unsigned i = 0; i < configlist.size(); i++)
		{
			con[i] = false;
		}
		
		for (unsigned i = next_num; i < next_num + 5 && i < configlist.size(); i++)
		{
			con[i] = GuiButton((Rectangle){240, (float)200 + (i - next_num) * 120, 880, 120}, configlist[i].c_str());
		}
		
		// 翻页
		if (nextpage)
		{
			next_num += 5;
			if (next_num >= configlist.size())
				next_num -= 5;
		}
		
		if (lastpage && next_num >= 5)
		{
			next_num -= 5;
		}
		
		// 选中配置项
		for (unsigned i = 0; i < configlist.size(); i++)
		{
			if (con[i])
			{
				configlist.push_back(configlist[i]);
				exit = true;
				break;
			}
		}
		
		EndDrawing();
	}
	
	// 构造配置文件
	std::string _filestring = "config/";
	strcpy(configname,configlist.back().c_str());
	_filestring += configlist.back();
	ifstream _config(_filestring.c_str(), ios::in);
	
	if (!_config)
		return false;
	
	// 读取配置信息
	_config >> speed >> seed >> fruit_num;
	furit_pro[0] = _config.get() * 10;
	furit_pro[1] = _config.get() * 10;
	furit_pro[2] = _config.get() * 10;
	
	_config.close();
	_configlist.close();
	
	std::cout << speed << seed << fruit_num;
	return true;
}

// 创建配置文件函数
bool create_config(void)
{
	bool exit = false;
	bool save = false;
	int _level=1;
	int _applenum=1;
	
	bool msg_box = false;
	//char _apple_pro[3][50]{"0.1","0.3","0.6"};
	
	
	while (!exit)
	{
		BeginDrawing();
		ClearBackground(WHITE);
		
		// 返回
		exit = GuiButton((Rectangle){960, 1000, 360, 160}, "返回") || WindowShouldClose();
		
		// 保存
		save = GuiButton((Rectangle){240, 1000, 360, 160}, "保存") || WindowShouldClose();
		
		// 绘制界面
		int _newlevel = GuiSliderBar((Rectangle){240, 160, 880, 120}, "难度：", TextFormat("%i", (int)_level), _level, 1, 10);
		int _newapplenum = GuiSliderBar((Rectangle){240, 320, 880, 120}, "食物数量：", TextFormat("%i", (int)_applenum), _applenum, 1, 5);
		
		_applepro[0] = GuiSliderBar((Rectangle){240, 640, 240, 120}, "1分", TextFormat("%.1f", (double)_applepro[0]/10.0), _applepro[0], 1, 10);
		_applepro[1] = GuiSliderBar((Rectangle){640, 640, 240, 120}, "2分", TextFormat("%.1f", (double)_applepro[1]/10.0), _applepro[1], 1, 10);
		_applepro[2] = GuiSliderBar((Rectangle){1080, 640, 240, 120}, "3分", TextFormat("%.1f", (double)_applepro[2]/10.0), _applepro[2], 1, 10);
		
		if (GuiTextBox((Rectangle){240, 800, 880, 120}, configname, 120, maptextBox0EditMode))
			maptextBox0EditMode = !maptextBox0EditMode;
		if (GuiTextBox((Rectangle){240, 480, 880, 120}, _seed, 120, maptextBox1EditMode))
			maptextBox1EditMode = !maptextBox1EditMode;
		/*if (GuiTextBox((Rectangle){240, 640, 240, 120}, _apple_pro[0], 120, maptextBox2EditMode))
			maptextBox2EditMode = !maptextBox2EditMode;
		if (GuiTextBox((Rectangle){600, 640, 240, 120}, _apple_pro[1], 120, maptextBox3EditMode))
			maptextBox3EditMode = !maptextBox3EditMode;
		if (GuiTextBox((Rectangle){960, 640, 240, 120}, _apple_pro[2], 120, maptextBox4EditMode))
			maptextBox4EditMode = !maptextBox4EditMode;*/
		
		DrawTextEx(font, "食物生成概率", (Vector2){0, 640}, 40, 5, BLACK);
		DrawTextEx(font, "种子", (Vector2){0, 480}, 80, 5, BLACK);
		//DrawTextEx(font, "配置名称", (Vector2){0, 800}, 80, 5, BLACK);
		confignamestring = configname;
		

		if (_newlevel != _level || _newapplenum != _applenum)
		{
			_level = _newlevel;
			_applenum = _newapplenum;
		}
		
		if(msg_box)
		{
			DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(RAYWHITE, 0.8f));
			int result = GuiMessageBox((Rectangle){ (float)GetScreenWidth()/2 - 200, (float)GetScreenHeight()/2 - 200, 640, 200 }, GuiIconText(ICON_CPU, "ERROR"), "非法输入", "返回");
			printf("%d",result);
			if ((result == 1) || (result == 0)) msg_box = false;
			if(!msg_box)
			{
				setfont("res/font.ttf", 50);
			}
		}
		EndDrawing();
		
		// 保存
		if (save)
		{
			bool flag = false;
			if(_seed[0]=='-') flag = false;
			else if(_seed[0]>='0'&&_seed[0]<='9') flag =false;
			else flag=true;
			for(int i=1;i<50;i++)
			{
				if(_seed[i]=='\0') break;
				if(_seed[i]<'0'||_seed[i]>'9') flag = true;
			}
			if(_applepro[0]+_applepro[1]+_applepro[2]!=10||flag)
			{
				save = false;
				msg_box = true;
				setfont("res/font.ttf", 35);
			}
			if(save)
			{
			if(_seed[1]=='\0') 
			{
				_seed[1]='1';
				_seed[2]='\0';
			}
			std::ofstream configmenu("res/configs.list", ios::app);
			configmenu << endl <<confignamestring;
			confignamestring = "config/" + confignamestring;
			std::ofstream outconfig(confignamestring.c_str(), ios::out);
			outconfig << _level << endl
			<< _seed << endl
			<< _applenum << endl
			<< _applepro[0]/10.0 << " " << _applepro[1]/10.0 << " " << _applepro[2]/10.0; 
			configmenu.close();
			outconfig.close();
			return true;
			}
		}
	}
}

// 创建地图
bool create_map(void)
{
	bool exit = false;
	bool save = false;
	int _width = 15;
	int _length = 15;
	wallstatue.fill(true);
	char ctemp;
	int itemp[3];
	Vector2 mouse;
	
	// 初始化游戏板
	for (int i = 0; i < _width; i++)
	{
		vector<bool> s;
		for (int j = 0; j < _length; j++)
		{
			s.push_back(false);
		}
		gameboard.push_back(s);
	}
	
	// 显示地图界面
	while (!exit)
	{
		mouse = GetMousePosition();
		BeginDrawing();
		ClearBackground(WHITE);
		// 返回
		exit = GuiButton((Rectangle){1160, 960, 360, 160}, "返回") || WindowShouldClose();
		
		// 保存
		save = GuiButton((Rectangle){1160, 760, 360, 160}, "保存") || WindowShouldClose();
		
		// 绘制界面
		DrawTextEx(font,"命令行", (Vector2){1040, 650}, 80, 5, BLACK);
		DrawTextEx(font, "地图大小：", (Vector2){1040, 120}, 80, 5, BLACK);
		DrawTextEx(font, "墙虚实：", (Vector2){0, 1000}, 80, 5, BLACK);
		int _newwidth = GuiSliderBar((Rectangle){1160, 200, 400, 120}, "横：", TextFormat("%i", (int)_width), _width, 8, 20);
		int _newlength = GuiSliderBar((Rectangle){1160, 360, 400, 120}, "纵：", TextFormat("%i", (int)_length), _length, 8, 20);
		
		//绘制勾选框（墙壁虚实）
		wallstatue[0] = GuiCheckBox((Rectangle){ 120, 1080, 100, 100 }, "上", wallstatue[0]);
		wallstatue[1] = GuiCheckBox((Rectangle){ 320, 1080, 100, 100 }, "下", wallstatue[1]);
		wallstatue[2] = GuiCheckBox((Rectangle){ 520, 1080, 100, 100 }, "左", wallstatue[2]);
		wallstatue[3] = GuiCheckBox((Rectangle){ 720, 1080, 100, 100 }, "右", wallstatue[3]);
		
		if (GuiTextBox((Rectangle){1040, 520, 520, 120}, inputs, 120, maptextBoxEditMode))
			maptextBoxEditMode = !maptextBoxEditMode;
		
		if(IsKeyPressed(KEY_ENTER))
		{
			cli_stream.clear();
			cli_stream << inputs;
			strcpy(inputs,"\0");
			cli_stream >> ctemp;
			int x,y;
			switch (ctemp) 
			{
			case 'n':
				cli_stream >> itemp[0];
				cli_stream >> itemp[1];
				if (itemp[0] > 7 && itemp[0] < 21 && itemp[1] > 7 && itemp[1] < 21) {
					_newwidth = itemp[0];
					_newlength = itemp[1];
				} else {
					fault();
				}
				break;

			case 'o':
				
				cli_stream >> x;
				cli_stream >> y;
				if (x>=0 && x < _newwidth && y >=0 && y < _newlength) {
					gameboard[x-1][y-1]=1;
				} else {
					fault();
				}
				break;
				
				
			case 'p':
				
				cli_stream >> x;
				cli_stream >> y;
				if (x>=0 && x < _newwidth && y >=0 && y < _newlength && gameboard[x-1][y-1]==1) {
					gameboard[x-1][y-1]=0;
				} else {
					fault();
				}
				break;
			case 'w':
				cli_stream >> x;
				if(x==0||x==1){
				wallstatue[0]=x;
				}
				else{
					fault();
				}
				break;
			case 'a':
				cli_stream >> x;
				if(x==0||x==1){
					wallstatue[2]=x;
				}
				else{
					fault();
				}
				break;
			case 's':
				cli_stream >> x;
				if(x==0||x==1){
					wallstatue[1]=x;
				}
				else{
					fault();
				}
				break;
			case 'd':
				cli_stream >> x;
				if(x==0||x==1){
					wallstatue[3]=x;
				}
				else{
					fault();
				}
				break;
			default:
				fault();
				break;
			}
		}
		strcpy(mapname,inputs);
		mapnamestring = mapname;
		
		// 绘制地图
		for (int i = 0; i < _width + 1; i++)
		{
			DrawTexture(twall, p + i * u, p, WHITE);
			DrawTexture(twall, p + i * u, p + (_length + 1) * u, WHITE);
		}
		
		for (int i = 0; i < _length + 2; i++)
		{
			DrawTexture(twall, p, p + i * u, WHITE);
			DrawTexture(twall, p + (_width + 1) * u, p + i * u, WHITE);
		}
		
		if (_newlength != _length || _newwidth != _width)
		{
			gameboard.clear();
			for (int i = 0; i < _newwidth; i++)
			{
				vector<bool> s;
				for (int j = 0; j < _newlength; j++)
				{
					s.push_back(false);
				}
				gameboard.push_back(s);
				s.clear();
			}
			_length = _newlength;
			_width = _newwidth;
		}
		

		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		{
			int x = floor((mouse.x - 160) / 40);
			int y = floor((mouse.y - 160) / 40);
			
			if (y >= 0 && y < _length && x >= 0 && x < _width)
			{
				if (gameboard[x][y])
					gameboard[x][y] = false;
				else
					gameboard[x][y] = true;
			}
		}
		
		// 绘制鼠标位置
		DrawText(TextFormat("Mouse Position: [ %.0f, %.0f ]", mouse.x, mouse.y), 10, 10, 50, DARKGRAY);
		
		// 绘制地图
		for (int i = 0; i < _width; i++)
		{
			for (int j = 0; j < _length; j++)
			{
				if (gameboard[i][j])
					DrawTexture(twall, p + (i + 1) * u, p + (j + 1) * u, WHITE);
			}
		}
		
		EndDrawing();
		
		// 保存
		if (save)
		{
			std::ofstream mapmenu("res/maps.list", ios::app);
			mapmenu << endl <<mapnamestring;
			mapnamestring = "maps/" + mapnamestring;
			std::ofstream outmap(mapnamestring.c_str(), ios::out);
			outmap << _width << " " << _length << endl;
			
			// 写入墙壁状态
			for (auto out : wallstatue)
			{
				outmap << out << " ";
			}
			
			int count = 0;
			
			// 障碍物个数
			for (unsigned i = 0; i < gameboard.size(); i++)
			{
				for (unsigned j = 0; j < gameboard[i].size(); j++)
				{
					if (gameboard[i][j])
						count++;
				}
			}
			
			outmap << endl << count << endl;
			
			// 写入障碍物位置
			for (unsigned i = 0; i < gameboard.size(); i++)
			{
				for (unsigned j = 0; j < gameboard[i].size(); j++)
				{
					if (gameboard[i][j])
						outmap << i << " " << j << endl;
				}
			}
			mapmenu.close();
			outmap.close();
			return true;
		}
	}
	return true;
}
