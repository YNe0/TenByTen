#pragma once
#include <string>

void draw_title();
int move_menu(int x, int y, int le);
int main_menu();
int game_menu();

int show_point(int point, int& high_score);
void save_high_score(int high_score);
int load_high_score();

int remove_lines(char*** board);
int draw_info();
struct Ranking {
    std::string name;
    int score;
};
int showRanking();
void input_ranking(std::string name, int score);

// 블록, 보드 관련 함수(위 Board.h에 있음)
void put_block(char*** board, char*** block, int x, int y);
void set_block(char*** board);
void clean_board(char*** board);
void put_block_with_overlap_check(char*** c_board, char*** m_board, char*** block, int x, int y);
bool can_move(char*** m_board, char*** block, int x, int y);
bool can_place_block(char*** m_board, char*** block, int x, int y);
void move_and_place_block(char*** m_board, char*** c_board, char*** block);
