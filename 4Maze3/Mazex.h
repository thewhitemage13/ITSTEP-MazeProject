#include <iostream>
#include <ctime> 
#include <Windows.h> 
#include <conio.h> 
#include <string>
using namespace std;

enum MazeObject { HALL, WALL, COIN, ENEMY, BORDER };
enum Color { DARKGREEN = 2, YELLOW = 14, RED = 12, BLUE = 9, WHITE = 15, DARKYELLOW = 6, DARKRED = 4, PURPUR = 13, GREEN = 10 };
enum KeyCode { ENTER = 13, ESCAPE = 27, SPACE = 32, LEFT = 75, RIGHT = 77, UP = 72, DOWN = 80 };

HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE); 

void SetCursor(int x, int y, int color, string text)
{
    COORD position;
    position.X = x;
    position.Y = y;
    SetConsoleCursorPosition(h, position);
    SetConsoleTextAttribute(h, color);
    cout << text;
}

void System(const char* str)
{
    system(str);
}

void Console()
{
    CONSOLE_CURSOR_INFO info;
    info.bVisible = false;
    info.dwSize = 100; 
    SetConsoleCursorInfo(h, &info);
}

void Message(LPCSTR text, LPCSTR text2)
{
    MessageBoxA(0, text, text2, MB_OK);
}

void SetCursorChar(int x, int y, int color, char text)
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE); //уникальный номер окна консоли (дескриптор)
    COORD position;
    position.X = x; // настройка координат
    position.Y = y;
    SetConsoleCursorPosition(h, position); // установка курсора в координату
    SetConsoleTextAttribute(h, color); // установка цвета
    cout << text; // вывод строки текста
}

void walls(int x, int y, int width, int height, int arr[][60], int elem) {
    if (x == 0 || y == 0 || x == width - 1 || y == height - 1) {
        arr[y][x] = elem;
    }
}

void mazeexit(int x, int y, int width, int height, int arr[][60], int elem) {
    if (x == 0 && y == 2 || x == 1 && y == 2 || x == 2 && y == 2 || x == width - 1 && y == height - 3 || x == width - 2 && y == height - 3 || x == width - 3 && y == height - 3) {
        arr[y][x] = elem;
    }
}

void reduction(int x, int y, int arr[][60], int item, int elem, int probability) {
    if (arr[y][x] == item) {
        int r;
        r = rand() % probability;
        if (r != 0)
        {
            arr[y][x] = elem;
        }
    }
}

