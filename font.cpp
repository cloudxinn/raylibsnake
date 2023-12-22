#include "raylib.h"
#include "structs.h"
#include "global_var.h"
#include "raygui.h"
char guitests[1000];
int codepointsCount;
int *codepoints;
Font font;
void setfont(const char *fileName, const int fontSize)
{
	char guitests[1500] = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM分墙虚实开始非法输入游戏暂停继续放地图设置配创建返回上一页下左右大小保存纵横难度种子食物数量-生成概率:：；.1234567890确定回放速度";
	
	// 将字符串中的字符逐一转换成Unicode码点，得到码点表
	codepoints = LoadCodepoints(guitests, &codepointsCount);
	
	// 读取仅含码点表中各字符的字体
	font = LoadFontEx(fileName, fontSize, codepoints, codepointsCount);
	GuiSetFont(font);
	
	// 释放码点表
	UnloadCodepoints(codepoints);
	
	// 设置字体
	GuiSetFont(font);
	GuiSetStyle(DEFAULT, fontSize, 20);
	
	return;
}
