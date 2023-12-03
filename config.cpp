#include"raylib.h"
#include"structs.h"
#include"global_var.h"
#include"raygui.h"
#include<fstream>
#include<iostream>
#include<cmath>
#include<vector>
using std::ifstream;
using std::ios;
using std::vector;
using std::cout;
using std::endl;
int width = 15, length =15;
int wall_status[4]={1};
int obstacle_num = 0;
double speed = 10;
int seed=-1;
int fruit_num = 1;
int furit_pro[3] = {6,3,1}; //10points express probability
void DrawStyleEditControls(void);
vector<vector<bool>> gameboard;
bool setmap(void)
{
	bool exit = false;
	while(!exit)
	{	
		BeginDrawing();
		ClearBackground(WHITE);
		exit =  GuiButton((Rectangle){ 800, 920, 680, 80}, "返回")||WindowShouldClose(); 
		EndDrawing();
	}
	ifstream map("maps/default.map",ios::in);
	if(!map) return false;
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
	return true;
}
bool setconfig(void)
{
	bool exit = false;
	ifstream _configlist("res/configs.list",ios::in);
	std::vector<std::string> configlist;
	while(_configlist)
	{
		std::string temp;
		_configlist >> temp;
		configlist.push_back(temp);
	}
	configlist.pop_back();
	bool con[configlist.size()]={false};
	std::cout << configlist.size()<<std::endl;
	bool lastpage=false;
	bool nextpage=false;
	unsigned next_num = 0;
	while(!exit)
	{	
	BeginDrawing();
	ClearBackground(WHITE);
		exit =  GuiButton((Rectangle){ 800, 920, 680, 80}, "返回")||WindowShouldClose(); 
		lastpage =  GuiButton((Rectangle){ 1240, 320, 320, 120}, "上一页")||WindowShouldClose();
		nextpage =  GuiButton((Rectangle){ 1240, 520, 320, 120}, "下一页")||WindowShouldClose();
		for(unsigned i=0;i<configlist.size();i++)
		{
			con[i]=false;
		}
		for(unsigned i=next_num;i<next_num+5&&i<configlist.size();i++)
		{
			con[i] = GuiButton((Rectangle){ 240, (float)200+(i-next_num)*120, 880, 120}, configlist[i].c_str());
		}
		if(nextpage)
		{
			next_num+=5;
			if(next_num>=configlist.size()) next_num-=5;
		}
		if(lastpage&&next_num>=5)
		{
			next_num-=5;
		}
		for(unsigned i=0;i<configlist.size();i++)
		{
			if(con[i]) 
			{
				configlist.push_back(configlist[i]);
				exit=true;
				break;
			}
		}
	EndDrawing();
	}
	std::string _filestring="config/";
	_filestring+=configlist.back();
	ifstream _config(_filestring.c_str(),ios::in);
	if(!_config) return false;
	_config >> speed >> seed >> fruit_num;
	furit_pro[0]=_config.get()*10;
	furit_pro[1]=_config.get()*10;
	furit_pro[2]=_config.get()*10;
	_config.close();
	_configlist.close();
	std::cout <<  speed << seed << fruit_num;
	return true;
}

bool create_config(void)
{
	bool exit = false;
	while(!exit)
	{	
		BeginDrawing();
		ClearBackground(WHITE);
		exit =  GuiButton((Rectangle){ 800, 920, 680, 80}, "返回")||WindowShouldClose(); 
		EndDrawing();
	}
	return true;
}

bool create_map(void)
{
	bool exit = false;
	int _width = 15;
	int _length = 15;
	Vector2 mouse; 
	Image imgwall = LoadImage("res/wall.png");
	Texture twall = LoadTextureFromImage(imgwall);
	for(int i=0;i<_width;i++)
	{
		vector<bool> s;
		for(int j=0;j<_length;j++)
		{
			s.push_back(false);
		}
		gameboard.push_back(s);
	}
	while(!exit)
	{	
		mouse = GetMousePosition();
		BeginDrawing();
		ClearBackground(WHITE);
		exit =  GuiButton((Rectangle){ 1160, 960, 360, 160}, "返回")||WindowShouldClose(); 
		DrawTextEx(font,"地图大小：",(Vector2){1040,120},80,5,BLACK);
		int _newwidth = GuiSliderBar((Rectangle){ 1160, 200, 400, 120 },"横：",TextFormat("%i", (int)_width), _width, 8, 20);
		int _newlength = GuiSliderBar((Rectangle){ 1160, 360, 400, 120 },"纵：",TextFormat("%i", (int)_length), _length, 8, 20);
		for(int i = 0; i < _width+1; i++)
		{
			DrawTexture(twall ,p+i*u, p, WHITE);
			DrawTexture(twall ,p+i*u, p+(_length+1)*u, WHITE);
		}
		for(int i = 0; i < _length+2; i++)
		{
			DrawTexture(twall ,p, p+i*u, WHITE);
			DrawTexture(twall ,p+(_width+1)*u, p+i*u, WHITE);
		}
		
		if(_newlength!=_length||_newwidth!=_width)
		{
			gameboard.clear();
			//if(gameboard.empty()) cout << gameboard.empty();
			for(int i=0;i<_newwidth;i++)
			{
				vector<bool> s;
				for(int j=0;j<_newlength;j++)
				{
					s.push_back(false);
				}
				gameboard.push_back(s);
				s.clear();
			}
			_length=_newlength;
			_width=_newwidth;
		}
	    
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		{
			int x = floor((mouse.x-160)/40);
			int y = floor((mouse.y-160)/40);
			cout << "x:"<<x << " " <<"y:"<< y << endl;
			cout << "_width:"<< _width << " " <<"_length:"<< _length << endl;
			if (y >= 0 && y < _length
				&& x >=0 && x < _width ) 
			{
				if(gameboard[x][y]) gameboard[x][y]=false;
				else gameboard[x][y]=true;
				for(auto i:gameboard)
				{
					for(auto j:i)
					{
						cout << j << " ";
					}
					cout << endl;
				}
				cout << _width << " " << _length <<endl;
			}
		}
		DrawText(TextFormat("Mouse Position: [ %.0f, %.0f ]", mouse.x, mouse.y), 10, 10, 50, DARKGRAY);
		for(int i=0;i<_width;i++)
		{
			for(int j=0;j<_length;j++)
			{
				if(gameboard[i][j]) DrawTexture(twall,p+(i+1)*u,p+(j+1)*u,WHITE);
			}
		}
		EndDrawing();
	}
	UnloadImage(imgwall);
	UnloadTexture(twall);
	return true;
}

