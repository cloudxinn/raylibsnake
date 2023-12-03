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
position rand_position(int seed);

using std::chrono::steady_clock;

std::vector<_snake> snake_Old; // 保存上一帧的蛇身位置
static bool pause = false; // 游戏暂停
static std::chrono::steady_clock::time_point timeold; // 上一次更新时间点
int score = 0; // 游戏得分
clock_t now; // 当前时钟时间

void in_game()
{	
	timeold = std::chrono::steady_clock::now();
	std::srand(time(NULL));
	
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
		
		if (((snake[0].x) > width) ||
			((snake[0].y) > length) ||
			(snake[0].x < 0) || (snake[0].y < 0))
		{
			gameover = true;
		}
		
		// 处理蛇与边界碰撞
		
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
	Image imgsnake_body = LoadImage("res/snake_body.png");
	Image imgsnake_head = LoadImage("res/snake_head.png");
	Image imgwall = LoadImage("res/wall.png");
	Image imgapple = LoadImage("res/apple.png");
	Texture twall = LoadTextureFromImage(imgwall);
	Texture tbody = LoadTextureFromImage(imgsnake_body);
	Texture thead = LoadTextureFromImage(imgsnake_head);
	Texture tapple = LoadTextureFromImage(imgapple);
	
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
		
		for (auto applef : apple)
		{
			DrawTexture(tapple, p + applef.x * u, p + applef.y * u, WHITE);
		}
		
		// 绘制苹果
		
		for (unsigned i = 0; i < obstacle.size(); i++)
		{
			DrawTexture(twall, p + obstacle[i].x * u, p + obstacle[i].y * u, WHITE);
		}
		
		// 绘制障碍物
		
		DrawText("config:", 1120, 120, 50, BLACK);
		DrawText(" default.config", 1120, 200, 50, BLACK);
		DrawText("map:", 1120, 280, 50, BLACK);
		DrawText(" default.map", 1120, 360, 50, BLACK);
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
	switch (snake[0].direct)
	{
	case 0:
		snake[0].x += 1;
		break;
	case 1:
		snake[0].x -= 1;
		break;
	case 2:
		snake[0].y += 1;
		break;
	default:
		snake[0].y -= 1;
		break;
	}
	
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
				position temp = rand_position(time(NULL));
				apple[i].x = temp.x;
				apple[i].y = temp.y;
				if (check_apple(apple[i]))
					break;
			}
			apple[i].ate = false;
			score += 3;
		}
		
		for (unsigned int i = 1; i < snake.size(); i++)
		{
			snake[i] = snake_Old[i - 1];
		}
	}
	
	// 更新苹果位置
	
	return;
}

position rand_position(int seed)
{
	std::srand(seed);
	int x1 = (std::rand() % 14 + 1);
	int y1 = (std::rand() % 14 + 1);
	
	return (position){x1, y1};
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

bool check_apple(_apple apple)
{
	for (auto i : snake)
	{
		if (i.x == apple.x && i.y == apple.y)
			return false;
	}
	
	for (auto i : obstacle)
	{
		if (i.x == apple.x && i.y == apple.y)
			return false;
	}
	
	return true;
}
