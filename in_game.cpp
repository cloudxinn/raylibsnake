#include "structs.h"
#include "global_var.h"
#include "raygui.h"
#include <vector>
#include <cstdio>
#include <string>
#include <iostream>
#include <chrono>
#include <ctime>


void update(void);
void draw_game(void);
void pause_game(void);
bool check_apple(_apple apple);


using std::chrono::steady_clock;

std::vector<_snake> snake_Old; // 保存上一帧的蛇身位置
static bool pause = false; // 游戏暂停
static std::chrono::steady_clock::time_point timeold; // 上一次更新时间点
int score = 0; // 游戏得分
int stepsSinceLastMine=0;
clock_t now; // 当前时钟时间




void in_game()
{	
	timeold = std::chrono::steady_clock::now();
	
	if (!gameover)
	{
		if (WindowShouldClose())
		{
			return;
		}
		
		if (IsKeyPressed(KEY_P) && !pause)
		{
			pause = true;
		}
		
		while (pause)
		{
			if (!pause)
				break;
			pause_game();
		}
		
		if (IsKeyPressed(KEY_W) && snake[0].direct <= 1)
		{
			snake[0].direct = 3;
		}
		if (IsKeyPressed(KEY_S) && snake[0].direct <= 1)
		{
			snake[0].direct = 2;
		}
		if (IsKeyPressed(KEY_A) && snake[0].direct > 1)
		{
			snake[0].direct = 1;
		}
		if (IsKeyPressed(KEY_D) && snake[0].direct > 1)
		{
			snake[0].direct = 0;
		}
		
		snake_Old.clear();
		for (unsigned i = 0; i < snake.size(); i++)
		{
			snake_Old.push_back(snake[i]);
		}
		
		// 控制输入处理
		
		for (unsigned i = 0; i < apple.size(); i++)
		{
			if ((snake[0].x < apple[i].x + 0.5 && (snake[0].x > apple[i].x - 0.5) &&
				(snake[0].y < (apple[i].y + 0.5) && (snake[0].y) > apple[i].y - 0.5)))
			{
				apple[i].ate = true;
			}
		}
		
		// 苹果碰撞
		
		for (unsigned i = 1; i < snake.size(); i++)
		{
			if ((snake[0].x == snake[i].x) && (snake[0].y == snake[i].y))
				gameover = true;
		}
		
		// 处理蛇自身碰撞
		for (unsigned i = 0; i < mines.size(); i++) {
			if (snake[0].x == mines[i].x && snake[0].y == mines[i].y) {
				if(mines[i].ty==0){
				gameover = true;
				}
				if(mines[i].ty==1){
					mines[i].active=0;
					buff=9;
				}
				if(mines[i].ty==2){
					mines[i].active=0;
					buff=1;
				}
			}
		}
		level = buff/ speed;
		
		
		if (obstacle.size())
		{
			for (auto cmp : obstacle)
			{
				if (snake[0].x == cmp.x && snake[0].y == cmp.y)
					gameover = true;
			}
		}
		
		// 处理蛇与障碍物碰撞
		
		
		bool isupdated = false;
		if (firststart)
		{
			update();
			firststart = false;
			now = clock();
		}
		
		if (clock() - now >= 1000 * level)
		{
			update();
			isupdated = true;
		}
		
		if (isupdated)
		{
			now = clock();
			isupdated = false;
		}
		
		// 更新游戏参数
		
		return;
	}
	else
	{
		BeginDrawing();
		ClearBackground(WHITE);
		EndDrawing();
		
		return;
	}
	
	return;
}

void draw_game()
{

	BeginDrawing();
	ClearBackground(WHITE);
	
	if (!gameover)
	{
		for (unsigned i = 0; i < wall[0].size(); i++)
		{
			DrawTexture(twall, p + wall[0][i].x * u, p + wall[0][i].y * u, WHITE);
			DrawTexture(twall, p + wall[1][i].x * u, p + wall[1][i].y * u, WHITE);
		}
		
		for (unsigned i = 0; i < wall[2].size(); i++)
		{
			DrawTexture(twall, p + wall[2][i].x * u, p + wall[2][i].y * u, WHITE);
			DrawTexture(twall, p + wall[3][i].x * u, p + wall[3][i].y * u, WHITE);
		}
		
		// 绘制墙体
		
		DrawTexture(thead, p + snake[0].x * u, p + snake[0].y * u, WHITE);
		for (unsigned i = 1; i < snake.size(); i++)
		{
			DrawTexture(tbody, p + snake[i].x * u, p + snake[i].y * u, WHITE);
		}
		
		// 绘制蛇
		
		for (auto appled : apple)
		{
			DrawTexture(tapple[appled.type], p + appled.x * u, p + appled.y * u, WHITE);
		}
		
		// 绘制苹果
		
		for (unsigned i = 0; i < obstacle.size(); i++)
		{
			DrawTexture(twall, p + obstacle[i].x * u, p + obstacle[i].y * u, WHITE);
		}
		
		for (auto mine : mines) {
			if (mine.active) {
				// 加载地雷图片并在地雷位置绘制
				DrawTexture(tmine[mine.ty], p + mine.x * u, p + mine.y * u, WHITE);	
			}
		}
		// 绘制障碍物
		
		DrawText("config:", 1120, 120, 50, BLACK);
		DrawText(configname, 1120, 200, 50, BLACK);
		DrawText("map:", 1120, 280, 50, BLACK);
		DrawText(mapname, 1120, 360, 50, BLACK);
		DrawText("score:", 1120, 520, 50, BLACK);
		DrawText(std::to_string(score).c_str(), 1120, 600, 50, BLACK);
		
		// 绘制文本信息
	}
	else
	{
		// 处理游戏结束
		
	}
	
	EndDrawing();
	
	/*
	UnloadTexture(thead);
	UnloadImage(imgsnake_head);
	UnloadTexture(tbody);
	UnloadImage(imgsnake_body);
	UnloadTexture(twall);
	UnloadImage(imgwall);
	UnloadTexture(tapple);
	UnloadImage(imgapple);
	*/
	
	return;
}

void update(void)
{
	move++;
	record.push_back(std::to_string(move));
	record.back()+='\n';
	
	stepsSinceLastMine++;
	if (stepsSinceLastMine > 15) {
		position minePos;  
		int ty;
		ty=rand()%3;
		while (1) {
			minePos = rand_position();
			if (check_mine({minePos.x, minePos.y,ty, true}))
				break;
		}
		
		if (!mines.empty()) {
			mines.erase(mines.begin()); // 移除第一个炸弹
		}
		mines.push_back({minePos.x, minePos.y, ty,true});
		stepsSinceLastMine = 0; // 重置计数器
	}
	switch (snake[0].direct)
	{
	case 0:
		snake[0].x += 1;
		record.back()+='D';
		record.back()+='\n';
		break;
	case 1:
		snake[0].x -= 1;
		record.back()+='A';
		record.back()+='\n';
		break;
	case 2:
		snake[0].y += 1;
		record.back()+='S';
		record.back()+='\n';
		break;
	default:
		snake[0].y -= 1;
		record.back()+='W';
		record.back()+='\n';
		break;
	}
	
	if (snake[0].x > width )
	{
		if(!wallstatue[3])
			snake[0].x = snake[0].x - width;
		else gameover = true;
	}
	if (snake[0].x <1 )
	{
		if(!wallstatue[2])
			snake[0].x = snake[0].x +width;
		else gameover = true;
	}
	// 如果蛇头超出屏幕宽度范围，（虚墙）将蛇头移到另一侧（实墙）游戏结束
	
	if (snake[0].y > length )
	{
		if(!wallstatue[0])
			snake[0].y = snake[0].y - length;
		else gameover = true;
	}
	if (snake[0].y <1 )
	{
		if(!wallstatue[1]) 
			snake[0].y = snake[0].y + length;
		else gameover = true;
	}
	// 如果蛇头超出屏幕高度范围，（虚墙）将蛇头移到另一侧（实墙）游戏结束
	
	// 更新蛇头位置
	
	for (auto i : apple)
	{
		if (i.ate)
		{
			snake.push_back(snake_Old.back());
			i.ate = false;
			break;
		}
	}
	
	// 吃到苹果的情况
	
	for (unsigned i = 0; i < apple.size(); i++)
	{
		if (apple[i].ate)
		{
			while (1)
			{
				apple[i]=rand_apple();
				if (check_apple(apple[i]))
					break;
			}
			apple[i].ate = false;
			score += apple[i].type+1;
		}
		
		for (unsigned int i = 1; i < snake.size(); i++)
		{
			snake[i] = snake_Old[i - 1];
		}
	}
	
	// 更新苹果位置
	for(unsigned i = 0;i<apple.size();i++)
	{
		record.back()+="F ";
		record.back()+=std::to_string(apple[i].x);
		record.back()+=' ';
		record.back()+=std::to_string(apple[i].y);
		record.back()+=' ';
		record.back()+=std::to_string(apple[i].type);
		record.back()+='\n';
	}
	return;
}

position rand_position()
{
	int x1 = (std::rand() % 14 + 1);
	int y1 = (std::rand() % 14 + 1);
	
	return (position){x1, y1};
}

_apple rand_apple()
{
	position temp = rand_position();
	int type=0;
	type = rand()%3;
	return _apple{temp.x,temp.y,type,true};
}
void pause_game(void)
{
	while (pause)
	{
		BeginDrawing();
		ClearBackground(WHITE);
		pause = !GuiButton((Rectangle){240, 240, 1000, 440}, "继续");
		EndDrawing();
	}
	return;
}

bool check_apple(_apple appled)
{
	for (auto i : snake)
	{
		if (i.x == appled.x && i.y == appled.y)
			return false;
	}
	
	for (auto i : obstacle)
	{
		if (i.x == appled.x && i.y == appled.y)
			return false;
	}
	
	for(unsigned i=0;i<apple.size();i++)
	{
		for(unsigned j=i+1;j<apple.size();j++)
		{
			if (apple[i].x == apple[j].x && apple[i].y == apple[j].y)
				return false;
		}
	}
	return true;
}
bool check_mine(_mine mined)
{
	for (auto i : snake)
	{
		if (i.x == mined.x && i.y == mined.y)
			return false;
	}
	
	for (auto i : obstacle)
	{
		if (i.x == mined.x && i.y == mined.y)
			return false;
	}
	
	for(unsigned i=0;i<mines.size();i++)
	{
		for(unsigned j=i+1;j<mines.size();j++)
		{
			if (mines[i].x == mines[j].x && mines[i].y == mines[j].y)
				return false;
		}
	}
	return true;
}
