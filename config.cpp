#include"raylib.h"
#include"structs.h"
#include"global_var.h"
#include"raygui.h"
#include<fstream>
#include<iostream>
using std::ifstream;
using std::ios;
int width = 15, length =15;
int wall_status[4]={1};
int obstacle_num = 0;
double speed = 10;
int seed=-1;
int fruit_num = 1;
int furit_pro[3] = {6,3,1}; //10points express probability
void DrawStyleEditControls(void);
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
	unsigned display_num = 0;
	unsigned next_num = 0;
	while(!exit)
	{	
	BeginDrawing();
	ClearBackground(WHITE);
		exit =  GuiButton((Rectangle){ 800, 920, 680, 80}, "返回")||WindowShouldClose(); 
		lastpage =  GuiButton((Rectangle){ 1240, 320, 320, 120}, "上一页")||WindowShouldClose();
		nextpage =  GuiButton((Rectangle){ 1240, 520, 320, 120}, "下一页")||WindowShouldClose();
		display_num = 0;
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
	while(!exit)
	{	
		BeginDrawing();
		ClearBackground(WHITE);
		exit =  GuiButton((Rectangle){ 800, 920, 680, 80}, "返回")||WindowShouldClose(); 
		EndDrawing();
	}
	return true;
}

