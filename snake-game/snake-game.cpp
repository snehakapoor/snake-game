#include <iostream>
#include <stdlib.h>
#include<conio.h>
#include<Windows.h>

using namespace std;
bool gameover;
const int width = 20;
const int height = 20;
int x, y, fruitx, fruity, score;
int tailX[100], tailY[100];
int ntail=0;
enum edirection { STOP = 0, LEFT , RIGHT , UP , DOWN };
edirection dir;
void setup()
{
	gameover = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	fruitx = rand() % width;
	fruity = rand() % height;
	score = 0;
}
void draw()
{
	system("cls");
	for (int i = 0; i <= width + 1; i++)
		cout << "#";
	cout << endl;
	for (int i = 0; i<height; i++)
	{
		for (int j = 0; j<width; j++)
		{
			if (j == 0)
				cout << "#";
			if (i == y && j == x)
				cout << "O";
			else if (i == fruity && j == fruitx)
				cout << "F";
			else
			{
				bool print=false;
				for (int k = 0; k < ntail; k++)
				{
					if (tailX[k] == j && tailY[k] == i)
					{
						cout << "o";
						print = true;
					
					}
					
				}
				if(!print)
				cout << " ";
			}

			if (j == width - 1)
				cout << "#";
		}
		cout << endl;

	}
	for (int i = 0; i <= width + 1; i++)
		cout << "#";
	cout << endl;
	cout << "score:" << score << endl;
}
void input()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a':
			dir = LEFT ;
			break;
		case 'd':
			dir = RIGHT ;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'w':
			dir = UP;
			break;
		case 'x':
			gameover = true;
			break;

		}
	}
}
void logic()
{
	int prevx = tailX[0];
	int prevy = tailY[0];
	int prev2x, prev2y;
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < ntail; i++)
	{
		prev2x = tailX[i];
		prev2y = tailY[i];
		tailX[i] = prevx;
		tailY[i] = prevy;
		prevx = prev2x;
		prevy = prev2y;
	}
	switch (dir)
	{
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	default:
		break;
	}
	//if (x > width || x<0 || y>height || y < 0) //snake can't pass through walls
		//gameover = true;
	if (x >= width)x = 0;  //snake can pass through walls
	else if (x < 0) x = width - 1;
	if (y >= height) y = 0;
	else if (y < 0)y = height - 1;
	for (int i = 0; i < ntail; i++)
	{
		if (tailX[i] == x && tailY[i] == y)
			gameover = true;
	}
	if (x == fruitx && y == fruity)
	{
		
		score += 10;
		fruitx = rand() % width;
		fruity = rand() % height;
		ntail++;

	}

}
int main()
{
	setup();
	while (!gameover)
	{
		draw();
		input();
		logic();
		Sleep(50); //to control snake speed
	}
	return 0;
}
