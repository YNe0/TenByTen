#include "BlockGame.h"
#include "GameUtil.h"
#include "Board.h"
#include "KeyDef.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>

using namespace std;

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

void move_and_place_block(char*** m_board, char*** c_board, char*** block) {
    int x = 5, y = 5;
    int key = 0;
    while (1) {
        system("cls");
        put_block_with_overlap_check(c_board, m_board, block, x, y);
        draw_board(c_board);
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
                return;
            }
            continue;
        case k_back:
            return;
        }
        if (can_move(m_board, block, new_x, new_y)) {
            x = new_x; y = new_y;
        }
    }
}

int remove_lines(char*** board) {
    int removed = 0;
    int sum = 0;
    // 가득 찬 행 삭제
    for (int row = 0; row < board_row; ++row) {
        bool full = true;
        for (int col = 0; col < board_col; ++col) {
            if (strcmp(board[row][col], " ") == 0) {
                full = false;
                break;
            }
        }
        if (full) {
            ++removed;
            for (int col = 0; col < board_col; ++col)
                strcpy_s(board[row][col], 4, " ");
        }
    }
    // 가득 찬 열 삭제
    for (int col = 0; col < board_col; ++col) {
        bool full = true;
        for (int row = 0; row < board_row; ++row) {
            if (strcmp(board[row][col], " ") == 0) {
                full = false;
                break;
            }
        }
        if (full) {
            ++removed;
            for (int row = 0; row < board_row; ++row)
                strcpy_s(board[row][col], 4, " ");
        }
    }
    if (removed > 0) {
        sum += removed * 10;
        sum += (removed - 1) * 5;
    }
    return sum;
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
