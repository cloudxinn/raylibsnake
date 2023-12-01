#include"raylib.h"
#include"structs.h"
#include"global_var.h"
#include "raygui.h"
char guitests[50];
int codepointsCount;
int *codepoints;
Font font;
void setfont(const char *fileName,const int fontSize)
{
	char guitests[1000]="qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM开始游戏暂停继续地图设置配创建返回上一页下.1234567890";
	// 将字符串中的字符逐一转换成Unicode码点，得到码点表
	codepoints=LoadCodepoints(guitests,&codepointsCount);
	// 读取仅含码点表中各字符的字体
	Font font = LoadFontEx(fileName,fontSize,codepoints,codepointsCount);
	GuiSetFont(font);
	UnloadCodepoints(codepoints);
	// 释放码点表
	GuiSetFont(font);
	GuiSetStyle(DEFAULT,fontSize,20);
	//设置字体
	return;
}
