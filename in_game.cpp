#include "structs.h"
#include"global_var.h"
#include "raygui.h"
#include<vector>
#include<cstdio>
#include<string>
#include<iostream>
#include<chrono>
#include<ctime>
void update(void);
void draw_game(void);
void pause_game(void);
bool check_apple(void);
position rand_position(int seed);
using std::chrono::steady_clock;
std::vector<_snake> snake_Old;
static position apple=(position){15,15};
static bool Is_apple_eat = 0;
static bool pause = false; 
static std::chrono::steady_clock::time_point timeold;
int score=0;
clock_t now; 
void in_game()
{	
	timeold = std::chrono::steady_clock::now();
	std::srand(time(NULL));
	if(!gameover)
	{
		if(WindowShouldClose())
		{
			return;
		}
		if(IsKeyPressed(KEY_P)&&!pause)
		{
			pause = true;
		}
		while(pause)
		{
			if(!pause) break;
			pause_game();
		}
		if(IsKeyPressed(KEY_W)&&snake[0].direct<=1)
		{
			snake[0].direct=3;
		}
		if(IsKeyPressed(KEY_S)&&snake[0].direct<=1)
		{
			snake[0].direct=2;
		}
		if(IsKeyPressed(KEY_A)&&snake[0].direct>1)
		{
			snake[0].direct=1;
		}
		if(IsKeyPressed(KEY_D)&&snake[0].direct>1)
		{
			snake[0].direct=0;
		}
		snake_Old.clear();
		for(unsigned i = 0;i < snake.size();i++)
		{
			snake_Old.push_back(snake[i]);
		}
		//control
		
		if((snake[0].x < apple.x +0.5 && (snake[0].x > apple.x-0.5) &&
			(snake[0].y < (apple.y+0.5) && (snake[0].y) > apple.y+-0.5)))
		{
			Is_apple_eat = 1;
			snake.push_back(snake_Old.back());
		}
		//apple collision
		
		for (unsigned i = 1; i < snake.size(); i++)
		{
			if ((snake[0].x == snake[i].x) && (snake[0].y == snake[i].y)) gameover = true;
		}
		//self collision
		
		if (((snake[0].x) > width) ||
			((snake[0].y) > length) ||
			(snake[0].x < 0) || (snake[0].y < 0))
		{
			gameover = true;
		}
		//wall collision
		if(obstacle.size())
		{
			for(auto cmp:obstacle)
			{
				if(snake[0].x==cmp.x&&snake[0].y==cmp.y)
					gameover=true;
			}
		}
		//obstacle collision

		bool isupdated = false;
		if(firststart)
		{
			update();
			firststart = false;
			now=clock();
		}
		if(clock()-now>=1000*level)
		{
			update();
			isupdated = true;
		}
		if(isupdated)
		{
			now=clock();
			isupdated = false;
		}
		//parement update
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
		if(!gameover)
		{	
			for(unsigned i = 0; i < wall[0].size(); i++)
			{
				DrawTexture(twall ,p+wall[0][i].x*u, p+wall[0][i].y*u, WHITE);
				DrawTexture(twall ,p+wall[1][i].x*u, p+wall[1][i].y*u, WHITE);
			}
			for(unsigned i = 0; i < wall[2].size(); i++)
			{
				DrawTexture(twall ,p+wall[2][i].x*u, p+wall[2][i].y*u, WHITE);
				DrawTexture(twall ,p+wall[3][i].x*u, p+wall[3][i].y*u, WHITE);
			}
			//Draw wall
			
			DrawTexture(thead ,p+snake[0].x*u, p+snake[0].y*u, WHITE);
			for(unsigned i = 1; i < snake.size(); i++)
			{
				DrawTexture(tbody ,p+snake[i].x*u, p+snake[i].y*u, WHITE);
			}//Draw sanke
			
			DrawTexture(tapple, p+apple.x*u, p+apple.y*u, WHITE);
			//draw apple
			
			for(unsigned i = 0; i < obstacle.size(); i++)
			{
				DrawTexture(twall ,p+obstacle[i].x*u, p+obstacle[i].y*u, WHITE);
			}
			//Draw obstacle
			
			DrawText("config:",1120,120,50,BLACK);
			DrawText(" default.config",1120,200,50,BLACK);
			DrawText("map:",1120,280,50,BLACK);
			DrawText(" default.map",1120,360,50,BLACK);
			DrawText("score:",1120,520,50,BLACK);
			DrawText(std::to_string(score).c_str(),1120,600,50,BLACK);
			//Draw text
		}
		else
		{
		
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
	switch(snake[0].direct)
	{
	case 0:
		snake[0].x+=1;
		break;
	case 1:
		snake[0].x-=1;
		break;
	case 2:
		snake[0].y+=1;
		break;
	default:
		snake[0].y-=1;
		break;
	}
	for(unsigned int i = 1; i < snake.size(); i++)
	{
		snake[i]=snake_Old[i-1];
	}
	//snake position update
	score+=1;
	if(Is_apple_eat) 
	{
		while(1)
		{
			apple=rand_position(time(NULL));
			if(check_apple()) break;
		}
		Is_apple_eat = 0;
		score+=3;
	}
	//apple update
	return;
}

position rand_position(int seed)
{
	std::srand(seed);
	int x1 = (std::rand()%14+1);
	int y1 = (std::rand()%14+1);
	//float x2 = (std::rand()/float(RAND_MAX));
	//float y2 = (std::rand()/float(RAND_MAX));
	return (position){x1, y1};
}

void pause_game(void)
{
	while(pause)
	{
		BeginDrawing();
			ClearBackground(WHITE);
			pause = !GuiButton((Rectangle){ 240, 240, 1000, 440 }, "继续");
			//if(!IsKeyReleased(KEY_P)) pause = false;
		EndDrawing();
	}
	return;
}

bool check_apple(void)
{
	for (auto i : snake)
	{
		if(i.x==apple.x&&i.y==apple.y) return false;
	}
	for (auto i : obstacle)
	{
		if(i.x==apple.x&&i.y==apple.y) return false;
	}
	return true;
}
