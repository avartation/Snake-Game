#include<iostream>
#include<ctime>
#include<cstdlib>
#include<iomanip>
#include<conio.h>
bool gameOver;
static const int width = 15;
static const int height = 30;
int head_X, head_Y, tail_X, tail_Y, frute_X, frute_Y, score = 1;
int snake[100][2] = {};
char yard[width][height];
enum Diraction { STOP = 0, UP, RIGHT, DOWN, LEFT };
Diraction d;
void step(int x)
{
	if (x == 0)
	{
		yard[snake[0][0]][snake[0][1]] = ' ';
		int i;
		for (i = 0; snake[i + 1][0] != 0; i++)
		{
			snake[i][0] = snake[i + 1][0];
			snake[i][1] = snake[i + 1][1];
		}
		snake[i][0] = head_X;
		snake[i][1] = head_Y;
		for (int i = 0; snake[i][0] != 0; i++)
			yard[snake[i][0]][snake[i][1]] = 'o';
		return;
	}
	int i = 0;
	while (5)
	{
		if (snake[i][0] == 0)
		{
			snake[i][0] = head_X;
			snake[i][1] = head_Y;
			return;
		}
		i++;
	}
}
void Setup()
{
	srand(time(0));
	gameOver = false;
	head_X = width / 2;
	head_Y = height / 2;
	frute_X = rand() % 30;
	frute_Y = rand() % 15;
	do {
		frute_X = rand() % width;
		frute_Y = rand() % height;
	} while (frute_X == 0 || frute_Y == 0 || frute_X == width - 1 || frute_Y == height - 1);
	for (int i = 0; i != width; i++)
		for (int j = 0; j != height; j++)
			yard[i][j] = ' ';
	for (int i = 0; i != width; i++)
	{
		yard[i][0] = '.';
		yard[i][height - 1] = '.';
	}
	for (int j = 0; j != height; j++)
	{
		yard[0][j] = '.';
		yard[width - 1][j] = '.';
	}
	yard[head_X][head_Y] = 'O';
	yard[frute_X][frute_Y] = '*';
	d = STOP;
}
void Draw()
{
	system("cls");
	for (int i = 0; i != width; i++)
	{
		for (int j = 0; j != height; j++)
			std::cout << yard[i][j] << ' ';
		std::cout << std::endl;
	}
	std::cout << "Your score : " << score << std::endl;
}
void Input()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'w':
			if (d != DOWN)
				d = UP;
			break;
		case'a':
			if (d != RIGHT)
				d = LEFT;
			break;
		case'd':
			if (d != LEFT)
				d = RIGHT;
			break;
		case's':
			if (d != UP)
				d = DOWN;
			break;
		case'p':
			gameOver = true;
			break;
		default:
			break;
		}
	}
}
void Logic()
{
	switch (d)
	{
	case UP:
		if (yard[head_X - 1][head_Y] == ' ' || yard[head_X - 1][head_Y] == '*')
		{
			head_X--;
		}
		else if (yard[head_X - 1][head_Y] != 'o' && yard[width - 2][head_Y] != 'o')
			head_X = width - 2;
		else
			gameOver = 1;
		break;
	case DOWN:
		if (yard[head_X + 1][head_Y] == ' ' || yard[head_X + 1][head_Y] == '*')
		{
			head_X++;
		}
		else if (yard[head_X + 1][head_Y] != 'o' && yard[1][head_Y] != 'o')
			head_X = 1;
		else
			gameOver = 1;
		break;
	case LEFT:
		if (yard[head_X][head_Y - 1] == ' ' || yard[head_X][head_Y - 1] == '*')
			head_Y--;
		else if (yard[head_X][head_Y - 1] != 'o' && yard[head_X][height - 2] != 'o')
			head_Y = height - 2;
		else
			gameOver = 1;
		break;
	case RIGHT:
		if (yard[head_X][head_Y + 1] == ' ' || yard[head_X][head_Y + 1] == '*')
			head_Y++;
		else if (yard[head_X][head_Y + 1] != 'o' && yard[head_X][1] != 'o')
			head_Y = 1;
		else
			gameOver = 1;
		break;
	}
	if (frute_X == head_X && frute_Y == head_Y)
	{
		std::cout << "\a";
		step(1);
		yard[head_X][head_Y] = 'O';
		do {
			frute_X = rand() % width;
			frute_Y = rand() % height;
		} while (yard[frute_X][frute_Y] != ' ');
		yard[frute_X][frute_Y] = '*';
		score++;
		return;
	}
	step(0);
	yard[head_X][head_Y] = 'O';
}
int main()
{
	Setup();
	while (!gameOver)
	{
		Draw();
		Input();
		Logic();
	}
	std::cout << "You lost!" << std::endl;
	system("pause");
}