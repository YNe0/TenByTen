#include<iostream>
#include<Windows.h>
#include<conio.h>
#include<vector>
#include<math.h>
#include<array>
#include<cstdlib>
#include<ctime>
#include<string>
#include <fstream>




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
#define test_key 10


/*
void textcolor(int foreground, int background)
{
	int color = foreground + background * 16;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
*/


void gotoxy(int x, int y) {
	COORD pos = { (SHORT)x, (SHORT)y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

int show_point(int point, int& high_score) {
	int x = 70;
	int y = 0;
	gotoxy(x, y);
	cout << "Point : ";
	gotoxy(x + 8, y);
	cout << point;

	// 하이스코어 업데이트
	if (point > high_score) {
		high_score = point;
		gotoxy(x, y + 1);
		cout << "New High Score!";
	}

	gotoxy(x, y + 2);
	cout << "High Score : " << high_score;

	point++;
	return point;
}

void save_high_score(int high_score) {
	ofstream file("highscore.txt");
	if (file.is_open()) {
		file << high_score;
		file.close();
	}
}
int load_high_score() {
	ifstream file("highscore.txt");
	int high_score = 0;
	if (file.is_open()) {
		file >> high_score;
		file.close();
	}
	return high_score;
}




void cursor_view(bool playing)
{
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = playing;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}



int key_control() {
	char key;
	while (1) {
		if (_kbhit) {
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
		if (key == 92) {
			return test_key;
		}
	}
}

void draw_board(char*** board);
void main_board(char*** board);
int draw_info();
int showRanking();
void draw_title();
int main_menu();
int game_menu();
int move_menu(int x, int y, int le);
void main_block(char*** block);
void show_block(char*** f_block, char*** s_block, char*** t_block, bool* block_used);
void create_block(char*** block);
void draw_block(int x, int y, char*** block);
void input_ranking(string name, int score);
void move_and_place_block(char*** board, char*** block);
int main() {
	int key = -1;
	bool playing = true;
	bool block_used[3] = { true, true, true };

	int high_score = load_high_score(); // 하이스코어 로드
	int total_point = 0;

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
	main_block(f_block);
	main_block(s_block);
	main_block(t_block);
	cursor_view(false);

	while (1) {
		system("cls");
		//draw_title();
		//int menu_num = main_menu();
		int menu_num = 0; //스킵용
		if (menu_num == 0) {
			//draw_title();
			//int game_num = game_menu();
			int game_num = 0; //스킵용
			if (game_num == 0) {
				total_point = 0; // 스코어 초기화
				while (1) {
					draw_board(m_board);
					total_point = show_point(total_point, high_score);
					if (block_used[0] && block_used[1] && block_used[2]) {
						create_block(f_block);
						create_block(s_block);
						create_block(t_block);
						block_used[0] = false;
						block_used[1] = false;
						block_used[2] = false;
					}

					show_block(f_block, s_block, t_block, block_used);
					key = key_control();
					if (key == k_1) {
						move_and_place_block(m_board, f_block);
						block_used[0] = true;
						main_block(f_block);
					}
					else if (key == k_2) {
						move_and_place_block(m_board, s_block);
						block_used[1] = true;
						main_block(s_block);
					}
					else if (key == k_3) {
						move_and_place_block(m_board, t_block);
						block_used[2] = true;
						main_block(t_block);
					}
					else if (key == k_back) {
						break;
					}
				}
			}
		}

		else if (menu_num == 1) {
			while (1) {
				int info_num = draw_info();
				if (info_num == 9)
					break;
			}
		}

		else if (menu_num == 2) {
			cout << "랭킹 : ";

			while (1) {
				int info_num = showRanking();
				if (info_num == 9)
					break;
			}

		}

		else if (menu_num == 3) {
			save_high_score(high_score); // 프로그램 종료 시 하이스코어 저장
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
	int le = 4; // 메뉴 갯수 증가 (4개)
	gotoxy(x - 2, y);
	cout << "> 게임시작";
	gotoxy(x, y + 1);
	cout << "게임정보"; // 기존 메뉴
	gotoxy(x, y + 2);
	cout << "점수보기"; // 새로운 메뉴 추가   cout << "게임정보";
	gotoxy(x, y + 3);
	cout << "  종료  ";

	int i = move_menu(x, y, le);
	return i;
}

int game_menu() {
	int x = 57;
	int y = 16;
	int le = 4;
	gotoxy(x - 2, y);
	cout << "> 클래식 모드";
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
			if (y1 < y + le - 1) { // 위로 이동
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

void show_block(char*** f_block, char*** s_block, char*** t_block, bool* block_used) {
	int x = 70;
	int y = 6;
	if (!block_used[0]) {
		gotoxy(x, y);
		cout << "1";
		draw_block(x, y, f_block);
	}
	if (!block_used[1]) {
		gotoxy(x, y + 9);
		cout << "2";
		draw_block(x, y + 9, s_block);
	}
	if (!block_used[2]) {
		gotoxy(x, y + 18);
		cout << "3";
		draw_block(x, y + 18, t_block);
	}
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
int draw_info() {
	system("cls");
	int x = 50;
	int y = 8;
	gotoxy(x, y);
	cout << "→ ← ↑ ↓ ? 1 2 3";
	int key = key_control();
	return key;
}

void clean_board(char*** board) {
	for (int i = 0; i < board_row; i++) {
		for (int j = 0; j < board_col; j++) {
			if (board[i][j] == "□") {
				board[i][j] = (char*)" ";
			}
		}
	}
}

void put_block(char*** board, char*** block, int x, int y) {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (block[i][j] == "■") {
				board[x + j - 2][y + i - 2] = (char*)"□";
			}
		}
	}
}

void set_block(char*** board) {
	for (int i = 0; i < board_row; i++) {
		for (int j = 0; j < board_col; j++) {
			if (board[i][j] == "□") {
				board[i][j] = (char*)"■";
			}
		}
	}
}

void move_and_place_block(char*** m_board, char*** block) {
	int x = 5;
	int y = 5;

	while (1) {
		clean_board(m_board);
		put_block(m_board, block, x, y);
		draw_board(m_board);

		int move_k = key_control();

		if (move_k == k_up) {
			x--;
			if (x < 0) x++;
		}
		else if (move_k == k_down) {
			x++;
			if (x > 9) x--;
		}
		else if (move_k == k_right) {
			y--;
			if (y < 0) y++;
		}
		else if (move_k == k_left) {
			y++;
			if (y > 9) y--;
		}
		else if (move_k == k_enter) {
			set_block(m_board);
			draw_board(m_board);
			break;
		}
		else if (move_k == k_back) {
			break;
		}
	}
}

struct Ranking {
	string name;
	int score;
};


int showRanking() {
	system("cls");

	vector<Ranking> rankings;
	ifstream fin("ranking.txt");
	Ranking r;
	while (fin >> r.name >> r.score) {
		rankings.push_back(r);
	}
	fin.close();

	// 점수 기준 내림차순 정렬 (버블 정렬)
	for (size_t i = 0; i < rankings.size(); i++) {
		for (size_t j = 0; j < rankings.size() - 1; j++) {
			if (rankings[j].score < rankings[j + 1].score) {
				Ranking temp = rankings[j];
				rankings[j] = rankings[j + 1];
				rankings[j + 1] = temp;
			}
		}
	}

	cout << "=== 랭킹 ===" << endl;
	for (size_t i = 0; i < rankings.size() && i < 10; i++) {
		cout << i + 1 << "위: " << rankings[i].name << " - " << rankings[i].score << "점" << endl;
	}

	cout << "\nbackspace를 눌러 뒤로 가기" << endl;
	int key;
	while (1) {
		key = key_control();
		if (key == 9)
			return 9;
	}
}

void input_ranking(string name, int score) {
	ofstream fout("ranking.txt", ios::app); // 추가 모드
	if (fout.is_open()) {
		fout << name << " " << score << endl;
		fout.close();
	}
}