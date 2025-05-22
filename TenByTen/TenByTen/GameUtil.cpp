#include "GameUtil.h"
#include "KeyDef.h"
#include <Windows.h>
#include <conio.h>

using namespace std;

void gotoxy(int x, int y) {
    COORD pos = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void cursor_view(bool playing)
{
    CONSOLE_CURSOR_INFO cursorInfo = { 0, };
    cursorInfo.dwSize = 1;
    cursorInfo.bVisible = playing;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void clear_screen() {
    COORD cursorPosition;
    cursorPosition.X = 0;
    cursorPosition.Y = 0;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
}

int key_control() {
    char key;
    while (1) {
        if (_kbhit()) {
            key = _getch();
            switch (key) {
            case 72: return 1; // k_up
            case 80: return 2; // k_down
            case 75: return 3; // k_left
            case 77: return 4; // k_right
            case 13: return 5; // k_enter
            case '1': return 6; // k_1
            case '2': return 7; // k_2
            case '3': return 8; // k_3
            case 8:  return 9; // k_back
            default: break;
            }
        }
    }
}
