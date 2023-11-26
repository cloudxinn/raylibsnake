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
	ifstream config("config/default.config",ios::in);
	if(!config) return false;
	config.close();
	return true;
}

bool create_config(void)
{
}

bool create_map(void)
{
	
}
