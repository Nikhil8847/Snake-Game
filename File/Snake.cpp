#include <iostream>
#include <Windows.h>
#include <stdlib.h>
#include <thread>
#include <chrono>
#include <conio.h>
using namespace std;

bool gameOver; // Check if the game is Over
const int width = 20;	// Bounding box width
const int height = 20;	// Bounding box height
int x, y;	// Location of head of snake
int tailX[50], tailY[50];
int tailLen;
int fruitX, fruitY, Score;	// Location of fruit and score

enum eDirection {STOP=0, LEFT, RIGHT, UP, DOWN};
eDirection dir;


void Settings() {
	gameOver = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	fruitX = rand() % width;
	fruitY = rand() % height;
	Score = 0;
}

void setFruitLocation() {
	fruitX = rand() % width;
	fruitY = rand() % height;
}

void Visual() {
	system("cls");
	
	// Upper boundary
	for (int i = 0; i <= width+1; i++) {
		cout << '#';
	}
	cout << endl;
	
	// Left and Right boundary
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (j == 0)
				cout << '#';

			if (i == y and j == x)
				cout << "O";
			else if (i == fruitY and j == fruitX)
				cout << '*';
			else {
				bool tailPrint = false;
				for (int k = 0; k < tailLen; k++) {
					if (tailX[k] == j and tailY[k] == i) {
						cout << "o";
						tailPrint = true;
					}
				}
				if(!tailPrint)
					cout << ' ';
			}
			if (j == width - 1)
				cout << '#';
		}
		cout << endl;
	}

	// Bottom boundary
	for (int i = 0; i <= width+1; i++) {
		cout << '#';
	}
	cout << endl;
	cout << "Score : " << Score << endl;
}

void Logic() {
	int prevX = tailX[0];
	int prevY = tailY[0];
	int _prevX, _prevY;
	tailX[0] = x;
	tailY[0] = y;

	for (int i = 1; i < tailLen; i++) {
		_prevX = tailX[i];
		_prevY = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = _prevX;
		prevY = _prevY;
	}

	switch (dir)
	{
	case LEFT:
		x = (x - 1 + width)%width;
		break;
	case RIGHT:
		x = (x + 1) % width;
		break;
	case UP:
		y = (y - 1 + height) % height;
		break;
	case DOWN:
		y = (y + 1) % height;
		break;
	default:
		break;
	}
	for (int i = 0; i < tailLen; i++) {
		if (tailX[i] == x and tailY[i] == y) {
			gameOver = true;
			cout << "GAMEOVER...." << endl;
		}
	}
	if (x == fruitX and y == fruitY) {
		Score++;
		tailLen++;
		setFruitLocation();
	}

}

void input() {

	if (_kbhit()) {

		switch (tolower(_getch()))
		{
		case 'a':
			if(dir != RIGHT)
				dir = LEFT;
			break;
		case 'd':
			if(dir != LEFT)
				dir = RIGHT;
			break;
		case 'w':
			if(dir != DOWN)
				dir = UP;
			break;
		case 's':
			if(dir != UP)
				dir = DOWN;
			break;	
		case 'x':
			gameOver = true;
		default:
			break;
		}
	}

}

int main() {

	Settings();
	while (!gameOver) {
		Visual();
		input();
		Logic();
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
	return 0;
}
