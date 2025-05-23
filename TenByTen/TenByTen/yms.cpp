<<<<<<< HEAD:1234/1234/yms.cpp
﻿#include<iostream>
#include<Windows.h>
#include<conio.h>
#include<vector>
#include<math.h>
#include<array> 
#include<cstdlib> 
#include<ctime>
#include<string>

using namespace std;
constexpr int board_row = 10;
constexpr int board_col = 10;
constexpr int block_row = 5;
constexpr int block_col = 5;

#define k_up 1
#define k_down 2
#define k_left 3
#define k_right 4
#define k_enter 5
#define k_1 6
#define k_2 7
#define k_3 8
#define k_back 9

/*
void textcolor(int foreground, int background)
{
	int color = foreground + background * 16;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
*/	

void cursor_view(bool playing)
{
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = playing;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void gotoxy(int x, int y) {
	COORD pos = {x, y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

int key_control() {
	char key = ' ';
	while (1) {
		if (_kbhit()) {
			key = _getch();
		}
		if (key == 72) { // 위
			return k_up;
		}
		if (key == 80) { // 아래
			return k_down;
		}
		if (key == 75) { // 오른쪽
			return k_right;
		}
		if (key == 77) { // 왼쪽
			return k_left;
		}
		if (key == 13) { // enter
			return k_enter;
		}
		if (key == 49) { // 1
			return k_1;
		}
		if (key == 50) { // 2
			return k_2;
		}
		if (key == 51) { // 3
			return k_3;
		}
		if (key == 8) { // backspace
			return k_back;
		}
	}
}

void draw_board(char*** board);
void main_board(char*** board);
int draw_info();
void draw_title();
int main_menu();
int game_menu();
int move_menu(int x, int y, int le);
int show_point(int point);
void main_block(char*** block);
void show_block(char*** f_block, char*** s_block, char*** t_block);
void create_block(char*** block);
void draw_block(int x, int y, char*** block);
void put_block(char*** board, char*** block, int x, int y);
void clean_board(char*** board);
void set_block(char*** board);
bool move_block(int& x, int& y, char*** board, char*** block);
bool can_put_block(char*** block, int x, int y);

int main() {
	int key = -1;
	bool playing = true;

	char*** m_board = new char** [board_row]; // 메인 보드
	for (int i = 0; i < board_row; i++)
		m_board[i] = new char* [board_col];

	char*** f_block = new char** [block_row]; // 1번 블럭
	for (int i = 0; i < block_row; i++)
		f_block[i] = new char* [block_col];

	char*** s_block = new char** [block_row]; // 2번 블럭
	for (int i = 0; i < block_row; i++)
		s_block[i] = new char* [block_col];

	char*** t_block = new char** [block_row]; // 3번 블럭
	for (int i = 0; i < block_row; i++)
		t_block[i] = new char* [block_col];

	main_board(m_board);
	cursor_view(false);

	while (1) {
		system("cls");
		draw_title();
		int menu_num = main_menu();

		if (menu_num == 0) {
			draw_title();
			int game_num = game_menu();
			if (game_num == 0) {
				int total_point = 0;
				int x = 5;
				int y = 5;
				while (1) {
					draw_board(m_board);
					main_block(f_block);
					main_block(s_block);
					main_block(t_block);
					total_point = show_point(total_point);
					create_block(f_block);
					create_block(s_block);
					create_block(t_block);
					show_block(f_block, s_block, t_block);
					key = key_control();
					if (key == k_1) {
						put_block(m_board, f_block, 5, 5);
						bool playing_block = true;
						while (playing_block) {
							clean_board(m_board);
							put_block(m_board, f_block, x, y);
							draw_board(m_board);
							playing_block = move_block(x, y, m_board, f_block);
						}
					}
					else if (key == k_2) {
						put_block(m_board, s_block, 5, 5);
						bool playing_block = true;
						while (playing_block) {
							clean_board(m_board);
							put_block(m_board, s_block, x, y);
							draw_board(m_board);
							playing_block = move_block(x, y, m_board, s_block);
						}
					}
					else if (key == k_3) {
						put_block(m_board, t_block, 5, 5);
						bool playing_block = true;
						while (playing_block) {
							clean_board(m_board);
							put_block(m_board, t_block, x, y);
							draw_board(m_board);
							playing_block = move_block(x, y, m_board, t_block);
						}
					}
					else if (key == k_back) {
						break;
					}
				}
			}
		}

		else if(menu_num == 1){
			while (1) {
				int info_num = draw_info();
				if (info_num == 9)
					break;
			}
		}

		else if (menu_num == 2) {
			break;
		}
	}
}

void draw_title() {
	system("cls");
	cout << "                                                                                             \n";
	cout << "                                                                                             \n";
	cout << "                                                                                             \n";
	cout << "                                                                                             \n";
	cout << "                                 ■■■■■■■ ■■■■■ ■     ■   ■           ■■■■■■■ ■■■■■ ■     ■   \n";
	cout << "                                    ■    ■     ■■    ■   ■              ■    ■     ■■    ■   \n";
	cout << "                                    ■    ■     ■ ■   ■   ■              ■    ■     ■ ■   ■   \n";
	cout << "                                    ■    ■■■■■ ■  ■  ■   ■■■■  ■   ■    ■    ■■■■■ ■  ■  ■   \n";
	cout << "                                    ■    ■     ■   ■ ■   ■   ■ ■   ■    ■    ■     ■   ■ ■   \n";
	cout << "                                    ■    ■     ■    ■■   ■   ■ ■   ■    ■    ■     ■    ■■   \n";
	cout << "                                    ■    ■■■■■ ■     ■   ■■■■   ■■■■    ■    ■■■■■ ■     ■   \n";
	cout << "                                                                   ■                         \n";
	cout << "                                                                   ■                         \n";
	cout << "                                                                 ■■                          \n";
	cout << "                                                                                             \n";
}

int main_menu() {
	int x = 58;
	int y = 16;
	int le = 3; // 메뉴 갯수
	gotoxy(x - 2, y);
	cout << "> 게임시작";
	gotoxy(x, y + 1);
	cout << "게임정보";
	gotoxy(x, y + 2);
	cout << "  종료  ";
	int i = move_menu(x, y, le);
	return i;
}

int game_menu() {
	int x = 57;
	int y = 16;
	int le = 4;
	gotoxy(x - 2, y);
	cout << "> 클레식 모드";
	gotoxy(x, y + 1);
	cout << "하 드 모 드 ";
	gotoxy(x, y + 2);
	cout << "스피드 모드";
	gotoxy(x, y + 3);
	cout << "   뒤로   ";
	int i = move_menu(x, y, le);
	return i;
}

int move_menu(int x, int y, int le) {
	int y1 = y;
	while (1) {
		int key = key_control();
		switch (key) {
		case k_up: {
			if (y1 > y) { // 아래 이동
				gotoxy(x - 2, y1);
				printf(" ");
				gotoxy(x - 2, --y1);
				cout << ">";
			}
			break;
		}
		case k_down: {
			if (y1 < y+le-1) { // 위로 이동
				gotoxy(x - 2, y1);
				printf(" ");
				gotoxy(x - 2, ++y1);
				cout << ">";
			}
			break;
		}
		case k_enter: { // 입력
			return y1 - y;
		}
		}
	}
}

void main_board(char*** board) {
	for (int i = 0; i < board_row; i++) {
		for (int j = 0; j < board_col; j++) {
			board[i][j] = (char*)" ";
		}
	}
}

void main_block(char*** block) {
	for (int i = 0; i < block_row; i++) {
		for (int j = 0; j < block_col; j++) {
			block[i][j] = (char*)" ";
		}
	}
}

void draw_board(char*** board) {
	system("cls");
	cout << " ";
	for (int i = 0; i < board_row; ++i) {
		cout << "_____ ";
	}
	cout << endl;

	for (int i = 0; i < board_col; ++i) {
		cout << "|";
		for (int j = 0; j < board_row; ++j) {
			cout << "     |";
		}
		cout << endl;

		cout << "|";
		for (int j = 0; j < board_row; ++j) {
			cout << "  " << board[i][j] << "  |";
		}
		cout << endl;

		cout << "|";
		for (int i = 0; i < board_row; ++i) {
			cout << "_____|";
		}	
		cout << endl;
	}
}

void show_block(char*** f_block, char*** s_block, char*** t_block) {
	int x = 70;
	int y = 6;
	gotoxy(x, y);
	cout << "1";
	draw_block(x, y, f_block);
	gotoxy(x, y+9);
	cout << "2";
	draw_block(x, y+9, s_block);
	gotoxy(x, y+18);
	cout << "3";
	draw_block(x, y+18, t_block);
}

void draw_block(int x, int y, char*** block) { // 보드에 블럭 그리기
	for (int i = 0; i < block_row; i++) {
		for (int j = 0; j < block_col; j++) {
			gotoxy(x + 5 + i, y - 2 + j);
			cout << block[i][j];
		}
	}
}

void create_block(char*** block) { //블럭 생성
	int block_num = rand() % 19 + 1;
	switch (block_num) {
	case 1:
		block[2][2] = (char*)"■";
		break;
	case 2:
		block[1][2] = (char*)"■";
		block[2][2] = (char*)"■";
		break;
	case 3:
		block[1][2] = (char*)"■";
		block[2][2] = (char*)"■";
		block[3][2] = (char*)"■";
		break;
	case 4:
		block[0][2] = (char*)"■";
		block[1][2] = (char*)"■";
		block[2][2] = (char*)"■";
		block[3][2] = (char*)"■";
		break;
	case 5:
		block[0][2] = (char*)"■";
		block[1][2] = (char*)"■";
		block[2][2] = (char*)"■";
		block[3][2] = (char*)"■";
		block[4][2] = (char*)"■";
		break;
	case 6:
		block[2][1] = (char*)"■";
		block[2][2] = (char*)"■";
		break;
	case 7:
		block[2][1] = (char*)"■";
		block[2][2] = (char*)"■";
		block[2][3] = (char*)"■";
		break;
	case 8:
		block[2][0] = (char*)"■";
		block[2][1] = (char*)"■";
		block[2][2] = (char*)"■";
		block[2][3] = (char*)"■";
		break;
	case 9:
		block[2][0] = (char*)"■";
		block[2][1] = (char*)"■";
		block[2][2] = (char*)"■";
		block[2][3] = (char*)"■";
		block[2][4] = (char*)"■";
		break;
	case 10:
		block[1][1] = (char*)"■";
		block[1][2] = (char*)"■";
		block[2][2] = (char*)"■";
		break;
	case 11:
		block[2][1] = (char*)"■";
		block[2][2] = (char*)"■";
		block[3][1] = (char*)"■";
		break;
	case 12:
		block[2][2] = (char*)"■";
		block[3][2] = (char*)"■";
		block[3][3] = (char*)"■";
		break;
	case 13:
		block[1][3] = (char*)"■";
		block[2][2] = (char*)"■";
		block[2][3] = (char*)"■";
		break;
	case 14:
		block[1][1] = (char*)"■";
		block[1][2] = (char*)"■";
		block[2][1] = (char*)"■";
		block[2][2] = (char*)"■";
		break;
	case 15:
		block[1][1] = (char*)"■";
		block[1][2] = (char*)"■";
		block[1][3] = (char*)"■";
		block[2][3] = (char*)"■";
		block[3][3] = (char*)"■";
		break;
	case 16:
		block[1][1] = (char*)"■";
		block[1][2] = (char*)"■";
		block[1][3] = (char*)"■";
		block[2][1] = (char*)"■";
		block[3][1] = (char*)"■";
		break;
	case 17:
		block[1][1] = (char*)"■";
		block[2][1] = (char*)"■";
		block[3][1] = (char*)"■";
		block[3][2] = (char*)"■";
		block[3][3] = (char*)"■";
		break;
	case 18:
		block[1][3] = (char*)"■";
		block[2][3] = (char*)"■";
		block[3][1] = (char*)"■";
		block[3][2] = (char*)"■";
		block[3][3] = (char*)"■";
		break;
	case 19:
		block[1][1] = (char*)"■";
		block[1][2] = (char*)"■";
		block[1][3] = (char*)"■";
		block[2][1] = (char*)"■";
		block[2][2] = (char*)"■";
		block[2][3] = (char*)"■";
		block[3][1] = (char*)"■";
		block[3][2] = (char*)"■";
		block[3][3] = (char*)"■";
		break;
	}
}

int show_point(int point) {
	int x = 70;
	int y = 0;
	gotoxy(x, y);
	cout << "Point : ";
	gotoxy(x + 8, y);
	cout << point;
	point++;
	return point;
}

void clean_board(char*** board) {
	for (int i = 0; i < board_row; i++) {
		for (int j = 0; j < board_col; j++) {
			if (board[i][j] == "□") {
				board[i][j] = (char*)" ";
			}
			else if (board[i][j] == "▣") {
				board[i][j] = (char*)"■";
			}

		}
	}
}

void put_block(char*** board, char*** block, int x, int y) {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (block[i][j] == "■") {
				int block_x = x + j - 2;
				int block_y = y + i - 2;
				// 배열 인덱스 범위 체크 (보드 밖 접근 방지)
				if (block_x >= 0 && block_x < board_row && block_y >= 0 && block_y < board_col) {
					// 이미 확정된 "■"가 아니면 임시 "□"로 마킹
					if (board[block_x][block_y] != (char*)"■") {
						board[block_x][block_y] = (char*)"□";
					}
					else if (board[block_x][block_y] == (char*)"■") {
						board[block_x][block_y] = (char*)"▣";
					}
				}
			}
		}
	}
}

void set_block(char*** board){
	for (int i = 0; i < board_row; i++) {
		for (int j = 0; j < board_col; j++) {
			if (board[i][j] == "□") {
				board[i][j] = (char*)"■";
			}
		}
	}
}

int draw_info() {
	system("cls");
	int x = 50;
	int y = 8;
	gotoxy(x, y);
	cout << "→ ← ↑ ↓ ↲ 1 2 3";
	int key = key_control();
	return key;
}

bool move_block(int& x, int& y, char*** board, char*** block) {
	int prev_x = x, prev_y = y;
	int move_k = key_control();
	if (move_k == k_up) x--;
	else if (move_k == k_down) x++;
	else if (move_k == k_left) y++;
	else if (move_k == k_right) y--;

	// 이동 후 보드 범위 밖으로 나가는지 확인
	if (!can_put_block(block, x, y)) {
		// 범위 밖이면 원래대로 돌림
		x = prev_x;
		y = prev_y;
	}

	if (move_k == k_enter) {
		set_block(board);
		draw_board(board);
		return false;
	}
	return true;
}

bool can_put_block(char*** block, int x, int y) {
	for (int i = 0; i < block_row; ++i) {
		for (int j = 0; j < block_col; ++j) {
			if (block[i][j] == (char*)"■") {
				int bx = x + j - 2;
				int by = y + i - 2;
				// 보드 밖이면 false
				if (bx < 0 || bx >= board_row || by < 0 || by >= board_col) {
					return false;
				}
			}
		}
	}
	return true;
}
=======
﻿
>>>>>>> origin/TenByTen:TenByTen/TenByTen/yms.cpp
