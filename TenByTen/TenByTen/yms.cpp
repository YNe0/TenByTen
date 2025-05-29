#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <vector>
#include <math.h>
#include <array>
#include <cstdlib>
#include <ctime>
#include <string>
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
            case 72: return k_up; // 위
            case 80: return k_down; // 아래
            case 75: return k_left; // 왼쪽
            case 77: return k_right; // 오른쪽
            case 13: return k_enter; // Enter
            case '1': return k_1; // 숫자 1
            case '2': return k_2; // 숫자 2
            case '3': return k_3; // 숫자 3
            case 8:  return k_back; // Backspace
            default: break; // 다른 키는 무시
            }
        }
    }
}

void allocate_board(char**** board) {
    *board = new char** [board_row];
    for (int i = 0; i < board_row; i++) {
        (*board)[i] = new char* [board_col];
        for (int j = 0; j < board_col; j++) {
            (*board)[i][j] = new char[4];
            strcpy_s((*board)[i][j], 4, " ");
        }
    }
}

void allocate_block(char**** block) {
    *block = new char** [block_row];
    for (int i = 0; i < block_row; i++) {
        (*block)[i] = new char* [block_col];
        for (int j = 0; j < block_col; j++) {
            (*block)[i][j] = new char[4];
            strcpy_s((*block)[i][j], 4, " ");
        }
    }
}

void deallocate_board(char*** board) {
    for (int i = 0; i < board_row; i++) {
        for (int j = 0; j < board_col; j++) {
            delete[] board[i][j];
        }
        delete[] board[i];
    }
    delete[] board;
}

void deallocate_block(char*** block) {
    for (int i = 0; i < block_row; i++) {
        for (int j = 0; j < block_col; j++) {
            delete[] block[i][j];
        }
        delete[] block[i];
    }
    delete[] block;
}

void main_board(char*** board) {
    for (int i = 0; i < board_row; i++) {
        for (int j = 0; j < board_col; j++) {
            strcpy_s(board[i][j], 4, " ");
        }
    }
}

void main_block(char*** block) {
    for (int i = 0; i < block_row; i++) {
        for (int j = 0; j < block_col; j++) {
            strcpy_s(block[i][j], 4, " ");
        }
    }
}

void draw_title() {
    system("cls");
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

int move_menu(int x, int y, int le) {
    int y1 = y;
    gotoxy(x - 2, y1);
    cout << ">";
    while (1) {
        int key = key_control();
        switch (key) {
        case k_up:
            if (y1 > y) {
                gotoxy(x - 2, y1);
                printf(" ");
                gotoxy(x - 2, --y1);
                cout << ">";
            }
            break;
        case k_down:
            if (y1 < y + le - 1) {
                gotoxy(x - 2, y1);
                printf(" ");
                gotoxy(x - 2, ++y1);
                cout << ">";
            }
            break;
        case k_enter:
            return y1 - y;
        }
    }
}

int main_menu() {
    int x = 58;
    int y = 16;
    int le = 4;
    gotoxy(x, y);
    cout << "게임시작";
    gotoxy(x, y + 1);
    cout << "게임정보";
    gotoxy(x, y + 2);
    cout << "점수보기";
    gotoxy(x, y + 3);
    cout << "  종료  ";
    return move_menu(x, y, le);
}

int game_menu() {
    int x = 57;
    int y = 16;
    int le = 4;
    gotoxy(x, y);
    cout << "클래식 모드";
    gotoxy(x, y + 1);
    cout << "하 드 모 드 ";
    gotoxy(x, y + 2);
    cout << "스피드 모드";
    gotoxy(x, y + 3);
    cout << "   뒤로   ";
    return move_menu(x, y, le);
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

void draw_block(int x, int y, char*** block) {
    for (int i = 0; i < block_row; i++) {
        for (int j = 0; j < block_col; j++) {
            gotoxy(x + j, y + i); // j가 x축, i가 y축
            cout << block[i][j];
        }
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

void create_block(char*** block) { //블럭 생성
    main_block(block);
    int block_num = rand() % 19 + 1;
    switch (block_num) {
    case 1:
        strcpy_s(block[2][2], 4, "■");
        break;
    case 2:
        strcpy_s(block[1][2], 4, "■");
        strcpy_s(block[2][2], 4, "■");
        break;
    case 3:
        strcpy_s(block[1][2], 4, "■");
        strcpy_s(block[2][2], 4, "■");
        strcpy_s(block[3][2], 4, "■");
        break;
    case 4:
        strcpy_s(block[0][2], 4, "■");
        strcpy_s(block[1][2], 4, "■");
        strcpy_s(block[2][2], 4, "■");
        strcpy_s(block[3][2], 4, "■");
        break;
    case 5:
        strcpy_s(block[0][2], 4, "■");
        strcpy_s(block[1][2], 4, "■");
        strcpy_s(block[2][2], 4, "■");
        strcpy_s(block[3][2], 4, "■");
        strcpy_s(block[4][2], 4, "■");
        break;
    case 6:
        strcpy_s(block[2][1], 4, "■");
        strcpy_s(block[2][2], 4, "■");
        break;
    case 7:
        strcpy_s(block[2][1], 4, "■");
        strcpy_s(block[2][2], 4, "■");
        strcpy_s(block[2][3], 4, "■");
        break;
    case 8:
        strcpy_s(block[2][0], 4, "■");
        strcpy_s(block[2][1], 4, "■");
        strcpy_s(block[2][2], 4, "■");
        strcpy_s(block[2][3], 4, "■");
        break;
    case 9:
        strcpy_s(block[2][0], 4, "■");
        strcpy_s(block[2][1], 4, "■");
        strcpy_s(block[2][2], 4, "■");
        strcpy_s(block[2][3], 4, "■");
        strcpy_s(block[2][4], 4, "■");
        break;
    case 10:
        strcpy_s(block[1][1], 4, "■");
        strcpy_s(block[1][2], 4, "■");
        strcpy_s(block[2][2], 4, "■");
        break;
    case 11:
        strcpy_s(block[2][1], 4, "■");
        strcpy_s(block[2][2], 4, "■");
        strcpy_s(block[3][1], 4, "■");
        break;
    case 12:
        strcpy_s(block[2][2], 4, "■");
        strcpy_s(block[3][2], 4, "■");
        strcpy_s(block[3][3], 4, "■");
        break;
    case 13:
        strcpy_s(block[1][3], 4, "■");
        strcpy_s(block[2][2], 4, "■");
        strcpy_s(block[2][3], 4, "■");
        break;
    case 14:
        strcpy_s(block[1][1], 4, "■");
        strcpy_s(block[1][2], 4, "■");
        strcpy_s(block[2][1], 4, "■");
        strcpy_s(block[2][2], 4, "■");
        break;
    case 15:
        strcpy_s(block[1][1], 4, "■");
        strcpy_s(block[1][2], 4, "■");
        strcpy_s(block[1][3], 4, "■");
        strcpy_s(block[2][3], 4, "■");
        strcpy_s(block[3][3], 4, "■");
        break;
    case 16:
        strcpy_s(block[1][1], 4, "■");
        strcpy_s(block[1][2], 4, "■");
        strcpy_s(block[1][3], 4, "■");
        strcpy_s(block[2][1], 4, "■");
        strcpy_s(block[3][1], 4, "■");
        break;
    case 17:
        strcpy_s(block[1][1], 4, "■");
        strcpy_s(block[2][1], 4, "■");
        strcpy_s(block[3][1], 4, "■");
        strcpy_s(block[3][2], 4, "■");
        strcpy_s(block[3][3], 4, "■");
        break;
    case 18:
        strcpy_s(block[1][3], 4, "■");
        strcpy_s(block[2][3], 4, "■");
        strcpy_s(block[3][1], 4, "■");
        strcpy_s(block[3][2], 4, "■");
        strcpy_s(block[3][3], 4, "■");
        break;
    case 19:
        strcpy_s(block[1][1], 4, "■");
        strcpy_s(block[1][2], 4, "■");
        strcpy_s(block[1][3], 4, "■");
        strcpy_s(block[2][1], 4, "■");
        strcpy_s(block[2][2], 4, "■");
        strcpy_s(block[2][3], 4, "■");
        strcpy_s(block[3][1], 4, "■");
        strcpy_s(block[3][2], 4, "■");
        strcpy_s(block[3][3], 4, "■");
        break;
    }
}

int show_point(int point, int& high_score) {
    int x = 70, y = 0;
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

void put_block(char*** board, char*** block, int x, int y) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (strcmp(block[i][j], "■") == 0) {
                int bx = x + j - 2;
                int by = y + i - 2;
                if (bx >= 0 && bx < board_row && by >= 0 && by < board_col)
                    strcpy_s(board[by][bx], 4, "□");
            }
        }
    }
}

void set_block(char*** board) {
    for (int i = 0; i < board_row; i++) {
        for (int j = 0; j < board_col; j++) {
            if (strcmp(board[i][j], "□") == 0) {
                strcpy_s(board[i][j], 4, "■");
            }
        }
    }
}

void clean_board(char*** board) {
    for (int i = 0; i < board_row; i++) {
        for (int j = 0; j < board_col; j++) {
            if (strcmp(board[i][j], "□") == 0) {
                strcpy_s(board[i][j], 4, " ");
            }
        }
    }
}

void put_block_with_overlap_check(char*** c_board, char*** m_board, char*** block, int x, int y) {
    for (int i = 0; i < board_row; i++)
        for (int j = 0; j < board_col; j++)
            strcpy_s(c_board[i][j], 4, m_board[i][j]);
    for (int i = 0; i < block_row; i++) {
        for (int j = 0; j < block_col; j++) {
            if (strcmp(block[i][j], "■") == 0) {
                int bx = x + j - 2;
                int by = y + i - 2;
                if (bx >= 0 && bx < board_row && by >= 0 && by < board_col) {
                    if (strcmp(m_board[by][bx], "■") == 0)
                        strcpy_s(c_board[by][bx], 4, "▣");
                    else
                        strcpy_s(c_board[by][bx], 4, "□");
                }
            }
        }
    }
}

bool can_move(char*** m_board, char*** block, int x, int y) {
    for (int i = 0; i < block_row; i++) {
        for (int j = 0; j < block_col; j++) {
            if (strcmp(block[i][j], "■") == 0) {
                int bx = x + j - 2;
                int by = y + i - 2;
                //범위 체크
                if (bx < 0 || bx >= board_row || by < 0 || by >= board_col)
                    return false;
            }
        }
    }
    return true;
}

bool can_place_block(char*** m_board, char*** block, int x, int y) {
    for (int i = 0; i < block_row; i++) {
        for (int j = 0; j < block_col; j++) {
            if (strcmp(block[i][j], "■") == 0) {
                int bx = x + j - 2;
                int by = y + i - 2;
                if (bx < 0 || bx >= board_row || by < 0 || by >= board_col)
                    return false;
                if (strcmp(m_board[by][bx], "■") == 0)
                    return false;
            }
        }
    }
    return true;
}

bool move_and_place_block(char*** m_board, char*** c_board, char*** block, char*** f_block, char*** s_block, char*** t_block, bool* block_used, int point, int& high_score) {
    int x = 5, y = 5;
    int key = 0;
    while (1) {
        system("cls");
        put_block_with_overlap_check(c_board, m_board, block, x, y);
        draw_board(c_board);
        point = show_point(point, high_score);
        show_block(f_block, s_block, t_block, block_used);
        key = key_control();
        int new_x = x, new_y = y;
        switch (key) {
        case k_up:    new_y--; break;
        case k_down:  new_y++; break;
        case k_left:  new_x--; break;
        case k_right: new_x++; break;
        case k_enter:
            if (can_place_block(m_board, block, x, y)) {
                put_block(m_board, block, x, y);
                set_block(m_board);
                return true;
            }
            continue;
        case k_back:
            return false;
        }
        if (can_move(m_board, block, new_x, new_y)) {
            x = new_x; y = new_y;
        }
    }
}

int remove_lines(char*** board) {
    int remove_line_x[10];
    int remove_line_y[10];
    int count_x = 0;
    int count_y = 0;
    int point = 0;

    // 가로줄 검사
    for (int i = 0; i < 10; ++i) {
        bool full_row = true;
        for (int j = 0; j < 10; ++j) {
            if (strcmp(board[i][j], " ") == 0) {
                full_row = false;
                break;
            }
        }
        if (full_row) {
            remove_line_x[count_x++] = i;
        }
    }

    // 세로줄 검사
    for (int i = 0; i < 10; ++i) {
        bool full_col = true;
        for (int j = 0; j < 10; ++j) {
            if (strcmp(board[j][i], " ") == 0) {
                full_col = false;
                break;
            }
        }
        if (full_col) {
            remove_line_y[count_y++] = i;
        }
    }

    // 가로줄 제거
    for (int k = 0; k < count_x; ++k) {
        int x = remove_line_x[k];
        for (int j = 0; j < 10; ++j) {
            strcpy_s(board[x][j], 4, " ");
        }
        point += 10;
    }

    // 세로줄 제거
    for (int k = 0; k < count_y; ++k) {
        int y = remove_line_y[k];
        for (int i = 0; i < 10; ++i) {
            strcpy_s(board[i][y], 4, " ");
        }
        point += 10;
    }

    return point;
}

bool all_blocks_unplaceable(char*** board, char*** f_block, char*** s_block, char*** t_block, bool* block_used) {
    for (int y = 0; y < board_row; y++) {
        for (int x = 0; x < board_col; x++) {
            if (!block_used[0] && can_place_block(board, f_block, x, y)) return false;
            if (!block_used[1] && can_place_block(board, s_block, x, y)) return false;
            if (!block_used[2] && can_place_block(board, t_block, x, y)) return false;
        }
    }
    return true;
}


int draw_info() {
    system("cls");
    int x = 50, y = 8;
    gotoxy(x, y);
    cout << "→ ← ↑ ↓ 1 2 3";
    int key = key_control();
    return key;
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
    // 내림차순 정렬
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
        if (key == k_back)
            return 9;
    }
}

void input_ranking(string name, int score) {
    ofstream fout("ranking.txt", ios::app);
    if (fout.is_open()) {
        fout << name << " " << score << endl;
        fout.close();
    }
}

int main() {
    srand((unsigned)time(NULL));
    int key = -1;
    int high_score = load_high_score();
    int total_point = 0;

    char*** m_board;
    char*** c_board;
    char*** f_block;
    char*** s_block;
    char*** t_block;

    allocate_board(&m_board); // 메인 보드
    allocate_board(&c_board); // 복사용 보드
    allocate_block(&f_block); // 1번 블럭
    allocate_block(&s_block); // 2번 블럭
    allocate_block(&t_block); // 3번 블럭

    main_block(f_block);
    main_block(s_block);
    main_block(t_block);

    cursor_view(false);

    while (1) {
        system("cls");
        draw_title();
        int menu_num = main_menu();
        if (menu_num == 0) {
            draw_title();
            int game_num = game_menu();
            if (game_num == 0) {
                total_point = 0; // 스코어 초기화
                main_board(m_board);
                bool block_used[3] = { true, true, true };

                while (1) {
                    total_point += remove_lines(m_board);
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

                    if (all_blocks_unplaceable(m_board, f_block, s_block, t_block, block_used)) {
                        gotoxy(0, 35);
                        cout << "\n\n※ 모든 블록을 배치할 수 없습니다. 게임 오버!";
                        cout << "\n이름을 입력하세요(랭킹 저장): ";
                        string name; cin >> name;
                        input_ranking(name, total_point);
                        save_high_score(high_score);
                        break;
                    }

                    show_block(f_block, s_block, t_block, block_used);
                    key = key_control();

                    if (key == k_1) {
                        if (!block_used[0]) {
                            block_used[0] = true;
                            block_used[0] = move_and_place_block(m_board, c_board, f_block, f_block, s_block, t_block, block_used, total_point, high_score);
                            if (block_used[0]) main_block(f_block);
                        }
                        continue;
                    }
                    else if (key == k_2) {
                        if (!block_used[1]) {
                            block_used[1] = true;
                            block_used[1] = move_and_place_block(m_board, c_board, s_block, f_block, s_block, t_block, block_used, total_point, high_score);
                            if (block_used[1]) main_block(s_block);
                        }
                        continue;
                    }
                    else if (key == k_3) {
                        if (!block_used[2]) {
                            block_used[2] = true;
                            block_used[2] = move_and_place_block(m_board, c_board, t_block, f_block, s_block, t_block, block_used, total_point, high_score);
                            if (block_used[2]) main_block(t_block);
                        }
                        continue;
                    }
                    else if (key == k_back) {
                        cout << "\n이름을 입력하세요(랭킹 저장): ";
                        string name; cin >> name;
                        input_ranking(name, total_point);
                        save_high_score(high_score);
                        break;
                    }
                }
            }
        }
        else if (menu_num == 1) {
            while (1) {
                int info_num = draw_info();
                if (info_num == k_back)
                    break;
            }
        }
        else if (menu_num == 2) {
            showRanking();
        }
        else if (menu_num == 3) {
            save_high_score(high_score);
            break;
        }
    }

    deallocate_board(m_board);
    deallocate_board(c_board);
    deallocate_block(f_block);
    deallocate_block(s_block);
    deallocate_block(t_block);

    return 0;
}
