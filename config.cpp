#include"raylib.h"
#include"structs.h"
#include"global_var.h"
#include"raygui.h"
#include<fstream>
using std::ifstream;
using std::ios;
int width = 15, length =15;
int wall_status[4]={1};
int obstacle_num = 0;
double speed = 10;
int seed=-1;
int fruit_num = 1;
int furit_pro[3] = {6,3,1}; //10points express probability
bool setmap(void)
{
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
	while(!exit)
	{	
	BeginDrawing();
	ClearBackground(WHITE);
		exit =  GuiButton((Rectangle){ 520, 680, 1240, 880 }, "返回"); 
	EndDrawing();
	}
	ifstream config("config/default.config",ios::in);
	if(!config) return false;
	config >> speed >> seed >> fruit_num;
	furit_pro[0]=config.get()*10;
	furit_pro[1]=config.get()*10;
	furit_pro[2]=config.get()*10;
	config.close();
	return true;
}

bool create_config(void)
{
}

bool create_map(void)
{
	
}
