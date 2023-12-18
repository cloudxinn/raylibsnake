#include "structs.h"
#include "global_var.h"
#include <string>
#include <cstdio>
void end_game()
{
	// 绘制画面
	BeginDrawing();
	// 绘制得分文本
	DrawText("score:",560,280,120,BLACK);
	DrawText(std::to_string(score).c_str(),600,520,160,BLACK);
	BeginDrawing();
	//TODO free space
	return;
}
