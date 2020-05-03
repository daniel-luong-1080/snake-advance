#include <iostream>
#include <conio.h>
#include <Windows.h>
using namespace std;


bool gameOver;
const int width = 30;
const int height = 30;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int lenghtTail;
enum direction { STOP, UP, DOWN, LEFT, RIGHT };
direction dir;


void clrscr() {
  COORD cursorPosition;	cursorPosition.X = 0;	cursorPosition.Y = 0;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
}


void showCursor(bool state) {
  HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

  CONSOLE_CURSOR_INFO     cursorInfo;
  GetConsoleCursorInfo(out, &cursorInfo);
  cursorInfo.bVisible = state; // set the cursor visibility
  SetConsoleCursorInfo(out, &cursorInfo);
}


void adjustWindow(int x, int y) {
  HWND console = GetConsoleWindow();
  RECT r;
  GetWindowRect(console, &r); //stores the console's current dimensions

  MoveWindow(console, r.left, r.top, x, y, TRUE);
}


void setup()
{
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
}


void render()
{
    clrscr();
    for (int i = 0; i < width+31; i++)
        cout << "-";
        cout << endl;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0)
                cout << "|";
            else
                cout << " ";
            if (i == y && j == x)
            {
                cout << "\b";
                cout << "o";
            }
            else if (i == fruitY && j == fruitX)
            {
                cout << "\b";
                cout << "f";
            }
            else
                for (int k = 0; k < lenghtTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << "\b";
                        cout << "+";
                    }
                }
                cout << " ";
            if (j == width - 1)
                cout << "|";
        }
        cout << endl;
    }

    for (int i = 0; i < width+31; i++)
        cout << "-";
        cout << endl;

        cout << "Score:" << score << endl;
}


void logic()
{
    int prev2X, prev2Y;
    int prevX = tailX[0];
    int prevY = tailY[0];
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < lenghtTail; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (dir)
    {
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    default:
        break;
    }

    if (x < 0)
        x = width;
    if (x > width)
        x = 0;
    if (y < 0)
        y = height;
    if (y > height)
        y = 0;

    for (int i = 0; i < lenghtTail; i++)
      if (tailX[i] == x && tailY[i] == y)
        gameOver = true;

    if (x == fruitX && y == fruitY)
    {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        lenghtTail++;

    }
}


void input()
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'q':
            gameOver = true;
            break;
        }
    }
}


void gameplay() {
  setup();
  while (!gameOver)
  {
      render();
      logic();
      input();
      Sleep(30);
  }
}


void welcome() {
  bool welcomeLoop = true;
  while (welcomeLoop)
  {
    system("cls");
    cout << "Welcome to Snake\n";
    cout << "Play\n";
    cout << "Quit\n";
    cout << "Version: Alpha v0.0.1\n";
    cout << "Input goes here: ";

    string welcomeInput;
    cin >> welcomeInput;
    if (welcomeInput == "play")
    {
      gameplay();
    }
    if (welcomeInput == "quit")
    {
      system("cls");
      cout << "Exiting the game...";
      Sleep(1000);
      system("cls");
      exit(0);
    }
    else
    {
      cout << "Invalid input, please try again";
      Sleep(0);
      clrscr();
    }
  }
}


int main()
{
  adjustWindow(500,600);
  showCursor(false);
    welcome();
    return 0;
}
