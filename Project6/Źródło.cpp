#include <iostream>
#include <string>
#include <time.h>
#include <conio.h>
#include <Windows.h>

using namespace std;

enum Direction { STOP = 0, UPLEFT = 1, DOWNLEFT = 2, UPRIGHT = 3, DOWNRIGHT = 4 };

bool quit;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

class Ball
{
	int x, y;
	int startX, startY;
	Direction dir;

public:
	Ball(int posX, int posY)
	{
		startX = posX;
		startY = posY;
		x = posX;
		y = posY;
		dir = STOP;
	}

	void Reset()
	{
		x = startX;
		y = startY;
		dir = STOP;
	}

	void Newdirection(Direction a)
	{
		dir = a;
	}

	void RandomDir()
	{
		dir = (Direction)((rand() % 4) + 1);
	}

	inline int getX() { return x; }
	inline int getY() { return y; }
	inline Direction getDir() { return dir; }

	void Move()
	{
		switch (dir)
		{
		case STOP:
			break;
		case UPLEFT:
			x--;
			y--;
			break;
		case DOWNLEFT:
			x--;
			y++;
			break;
		case UPRIGHT:
			x++;
			y--;
			break;
		case DOWNRIGHT:
			x++;
			y++;
			break;
		default:
			break;
		}
	}
};

class Paddle
{
	int x, y;
	int startX, startY;

public:
	Paddle()
	{
		x = y = 0;
	}

	Paddle(int posX, int posY) :Paddle()
	{
		startX = posX;
		startY = posY;
		x = posX;
		y = posY;
	}

	inline void Reset() { x = startX; y = startY; }
	inline int getX() { return x; }
	inline int getY() { return y; }
	inline void moveUp() { y--; }
	inline void moveDown() { y++; }
};

class GM
{
	int width, height;
	int score1, score2;
	char up1, up2, down1, down2;
	Ball *ball;
	Paddle *player1;
	Paddle *player2;

public:
	GM(int w, int h)
	{
		srand(time(NULL));
		quit = false;
		up1 = 'w';
		up2 = 'i';
		down1 = 's';
		down2 = 'k';
		score1 = 0;
		score2 = 0;
		width = w;
		height = h;
		ball = new Ball(w / 2, h / 2);
		player1 = new Paddle(1, h / 2 - 3);
		player2 = new Paddle(w - 2, h / 2 - 3);
	}

	~GM()
	{
		delete ball, player1, player2;
	}

	void Score(Paddle *player)
	{
		if (player == player1)
			score1++;
		else if (player == player2)
			score2++;

		ball->Reset();
		player1->Reset();
		player2->Reset();
	}

	void Draw()
	{
		SetConsoleCursorPosition(console, COORD());

		SetConsoleTextAttribute(console, 4); //red color
		cout << "\t  \xDB\xDB\xDB\xDB \xDB\xDB\xDB\xDB \xDB\xDB  \xDB \xDB\xDB\xDB\xDB" << endl;
		cout << "\t  \xDB  \xDB \xDB  \xDB \xDB \xDB \xDB \xDB" << endl;
		cout << "\t  \xDB\xDB\xDB\xDB \xDB  \xDB \xDB  \xDB\xDB \xDB  \xDB\xDB" << endl;
		cout << "\t  \xDB    \xDB\xDB\xDB\xDB \xDB   \xDB \xDB\xDB\xDB\xDB" << endl << endl;

		SetConsoleTextAttribute(console, 15); //white color
		for (int i = 0; i < width + 2; i++)
			cout << "\xB2";
		cout << endl;

		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				int ballX = ball->getX();
				int ballY = ball->getY();
				int player1x = player1->getX();
				int player2x = player2->getX();
				int player1y = player1->getY();
				int player2y = player2->getY();

				if (j == 0)
					cout << "\xB2";

				SetConsoleTextAttribute(console, 4); //red color
				if (ballX == j && ballY == i)
				{
					SetConsoleTextAttribute(console, 15); //white
					cout << "O";
				}
				else if (player1x == j && player1y == i)
					cout << "\xDB";
				else if (player2x == j && player2y == i)
					cout << "\xDB";
				else if (player1x == j && player1y + 1 == i)
					cout << "\xDB";
				else if (player1x == j && player1y + 2 == i)
					cout << "\xDB";
				else if (player1x == j && player1y + 3 == i)
					cout << "\xDB";
				else if (player2x == j && player2y + 1 == i)
					cout << "\xDB";
				else if (player2x == j && player2y + 2 == i)
					cout << "\xDB";
				else if (player2x == j && player2y + 3 == i)
					cout << "\xDB";

				else
					cout << " ";

				SetConsoleTextAttribute(console, 15); //white color
				if (j == width - 1)
					cout << "\xB2";
			}
			cout << endl;
		}

		for (int i = 0; i < width + 2; i++)
			cout << "\xB2";
		cout << endl;

		cout << "Player1: " << score1 << "\t\t\t" << "Player2: " << score2 << endl;
	}
	void Input()
	{
		ball->Move();

		int ballX = ball->getX();
		int ballY = ball->getY();
		int player1x = player1->getX();
		int player2x = player2->getX();
		int player1y = player1->getY();
		int player2y = player2->getY();

		if (_kbhit())
		{
			char c = _getch();

			if (c == up1)
				if (player1y > 0)
					player1->moveUp();
			if (c == up2)
				if (player2y > 0)
					player2->moveUp();
			if (c == down1)
				if (player1y + 4 < height)
					player1->moveDown();
			if (c == down2)
				if (player2y + 4 < height)
					player2->moveDown();

			if (ball->getDir() == STOP)
				ball->RandomDir();
		}
	}
	void Logic()
	{
		int ballX = ball->getX();
		int ballY = ball->getY();
		int player1x = player1->getX();
		int player2x = player2->getX();
		int player1y = player1->getY();
		int player2y = player2->getY();

		// left paddle
		for (int i = 0; i < 4; i++)
			if (ballX == player1x + 1)
				if (ballY == player1y + i)
					ball->Newdirection((Direction)((rand() % 2) + 3)); // if coordinates of our ball and paddle meets - set new direction for ball

		// right paddle
		for (int i = 0; i < 4; i++)
			if (ballX == player2x - 1)
				if (ballY == player2y + i)
					ball->Newdirection((Direction)((rand() % 2) + 1)); // if coordinates of our ball and paddle meets - set new direction for ball

		//bottom wall
		if (ballY == height - 1)
			ball->Newdirection(ball->getDir() == DOWNRIGHT ? UPRIGHT : UPLEFT);

		/* if current direction is downright, ball direction after hitting wall will be set to upright
			if current direction is not downright, ball direction will be set to upleft
		*/

		//top wall
		if (ballY == 0)
			ball->Newdirection(ball->getDir() == UPRIGHT ? DOWNRIGHT : DOWNLEFT);

		/* if current direction is upright, ball direction after hitting wall will be set to downright
		if current direction is not upright, ball direction will be set to downleft
		*/

		//right wall
		if (ballX == width - 1) // if cordinates of ball will not meet the paddle increase the score for player1
			Score(player1);

		//left wall
		if (ballX == 0) // if cordinates of ball will not meet the paddle increase the score for player2
			Score(player2);

		if (score1 == 11)
		{
			SetConsoleTextAttribute(console, 4); //red color
			cout << endl << "player1 won" << endl;
			_getch();
			quit = true;
			score1 = 0;
			score2 = 0;
		}

		if (score2 == 11)
		{
			SetConsoleTextAttribute(console, 4); //red color
			cout << endl << "player2 won" << endl;
			_getch();
			quit = true;
			score1 = 0;
			score2 = 0;
		}
	}

	void Run()
	{
		while (!quit)
		{
			Draw();
			Input();
			Logic();
			Sleep(15);
		}
	}
};

int main()
{
	char decision;

	GM d(40, 20);

	while (true)
	{
		system("cls");

		SetConsoleTextAttribute(console, 4); //red color
		cout << " \xDB\xDB\xDB\xDB \xDB\xDB\xDB\xDB \xDB\xDB  \xDB \xDB\xDB\xDB\xDB" << endl;
		cout << " \xDB  \xDB \xDB  \xDB \xDB \xDB \xDB \xDB" << endl;
		cout << " \xDB\xDB\xDB\xDB \xDB  \xDB \xDB  \xDB\xDB \xDB  \xDB\xDB" << endl;
		cout << " \xDB    \xDB\xDB\xDB\xDB \xDB   \xDB \xDB\xDB\xDB\xDB" << endl << endl;

		SetConsoleTextAttribute(console, 15); //white color
		cout << "======================" << endl;
		cout << "\t1 Game" << endl;
		cout << "\t2 Exit" << endl;
		cout << "======================" << endl;
		SetConsoleTextAttribute(console, 4); //red color
		cout << "       Controls" << endl;
		SetConsoleTextAttribute(console, 15); //white color
		cout << "player1 w(up) s(down)" << endl;
		cout << "player2 i(up) k(down)" << endl;
		cout << "======================" << endl;

		decision = _getch();
		cout << endl;

		switch (decision)
		{
		case '1':
			system("cls");
			quit = false;
			d.Run();
			break;
		case '2':
			exit(0);
			break;
		default:
			cout << "wrong key";
			_getch();
			break;
		}
	}

	return 0;
}