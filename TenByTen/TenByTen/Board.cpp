#include "Board.h"
#include "KeyDef.h"
#include <cstring>
#include <iostream>
#include "GameUtil.h"

using namespace std;

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

void draw_board(char*** board) {
    system("cls");
    std::cout << " ";
    for (int i = 0; i < board_row; ++i) {
        std::cout << "_____ ";
    }
    std::cout << std::endl;

    for (int i = 0; i < board_col; ++i) {
        std::cout << "|";
        for (int j = 0; j < board_row; ++j) {
            std::cout << "     |";
        }
        std::cout << std::endl;

        std::cout << "|";
        for (int j = 0; j < board_row; ++j) {
            std::cout << "  " << board[i][j] << "  |";
        }
        std::cout << std::endl;

        std::cout << "|";
        for (int k = 0; k < board_row; ++k) {
            std::cout << "_____|";
        }
        std::cout << std::endl;
    }
}

void draw_block(int x, int y, char*** block) {
    for (int i = 0; i < block_row; i++) {
        for (int j = 0; j < block_col; j++) {
            gotoxy(x + j, y + i);
            std::cout << block[i][j];
        }
    }
}

void show_block(char*** f_block, char*** s_block, char*** t_block, bool* block_used) {
    int x = 70;
    int y = 6;
    if (!block_used[0]) {
        gotoxy(x, y);
        std::cout << "1";
        draw_block(x, y, f_block);
    }
    if (!block_used[1]) {
        gotoxy(x, y + 9);
        std::cout << "2";
        draw_block(x, y + 9, s_block);
    }
    if (!block_used[2]) {
        gotoxy(x, y + 18);
        std::cout << "3";
        draw_block(x, y + 18, t_block);
    }
}

void create_block(char*** block) {
    main_block(block);
    int block_num = rand() % 19 + 1;
    switch (block_num) {
    case 1:
        strcpy_s(block[2][2], 4, "бс");
        break;
    case 2:
        strcpy_s(block[1][2], 4, "бс");
        strcpy_s(block[2][2], 4, "бс");
        break;
    case 3:
        strcpy_s(block[1][2], 4, "бс");
        strcpy_s(block[2][2], 4, "бс");
        strcpy_s(block[3][2], 4, "бс");
        break;
    case 4:
        strcpy_s(block[0][2], 4, "бс");
        strcpy_s(block[1][2], 4, "бс");
        strcpy_s(block[2][2], 4, "бс");
        strcpy_s(block[3][2], 4, "бс");
        break;
    case 5:
        strcpy_s(block[0][2], 4, "бс");
        strcpy_s(block[1][2], 4, "бс");
        strcpy_s(block[2][2], 4, "бс");
        strcpy_s(block[3][2], 4, "бс");
        strcpy_s(block[4][2], 4, "бс");
        break;
    case 6:
        strcpy_s(block[2][1], 4, "бс");
        strcpy_s(block[2][2], 4, "бс");
        break;
    case 7:
        strcpy_s(block[2][1], 4, "бс");
        strcpy_s(block[2][2], 4, "бс");
        strcpy_s(block[2][3], 4, "бс");
        break;
    case 8:
        strcpy_s(block[2][0], 4, "бс");
        strcpy_s(block[2][1], 4, "бс");
        strcpy_s(block[2][2], 4, "бс");
        strcpy_s(block[2][3], 4, "бс");
        break;
    case 9:
        strcpy_s(block[2][0], 4, "бс");
        strcpy_s(block[2][1], 4, "бс");
        strcpy_s(block[2][2], 4, "бс");
        strcpy_s(block[2][3], 4, "бс");
        strcpy_s(block[2][4], 4, "бс");
        break;
    case 10:
        strcpy_s(block[1][1], 4, "бс");
        strcpy_s(block[1][2], 4, "бс");
        strcpy_s(block[2][2], 4, "бс");
        break;
    case 11:
        strcpy_s(block[2][1], 4, "бс");
        strcpy_s(block[2][2], 4, "бс");
        strcpy_s(block[3][1], 4, "бс");
        break;
    case 12:
        strcpy_s(block[2][2], 4, "бс");
        strcpy_s(block[3][2], 4, "бс");
        strcpy_s(block[3][3], 4, "бс");
        break;
    case 13:
        strcpy_s(block[1][3], 4, "бс");
        strcpy_s(block[2][2], 4, "бс");
        strcpy_s(block[2][3], 4, "бс");
        break;
    case 14:
        strcpy_s(block[1][1], 4, "бс");
        strcpy_s(block[1][2], 4, "бс");
        strcpy_s(block[2][1], 4, "бс");
        strcpy_s(block[2][2], 4, "бс");
        break;
    case 15:
        strcpy_s(block[1][1], 4, "бс");
        strcpy_s(block[1][2], 4, "бс");
        strcpy_s(block[1][3], 4, "бс");
        strcpy_s(block[2][3], 4, "бс");
        strcpy_s(block[3][3], 4, "бс");
        break;
    case 16:
        strcpy_s(block[1][1], 4, "бс");
        strcpy_s(block[1][2], 4, "бс");
        strcpy_s(block[1][3], 4, "бс");
        strcpy_s(block[2][1], 4, "бс");
        strcpy_s(block[3][1], 4, "бс");
        break;
    case 17:
        strcpy_s(block[1][1], 4, "бс");
        strcpy_s(block[2][1], 4, "бс");
        strcpy_s(block[3][1], 4, "бс");
        strcpy_s(block[3][2], 4, "бс");
        strcpy_s(block[3][3], 4, "бс");
        break;
    case 18:
        strcpy_s(block[1][3], 4, "бс");
        strcpy_s(block[2][3], 4, "бс");
        strcpy_s(block[3][1], 4, "бс");
        strcpy_s(block[3][2], 4, "бс");
        strcpy_s(block[3][3], 4, "бс");
        break;
    case 19:
        strcpy_s(block[1][1], 4, "бс");
        strcpy_s(block[1][2], 4, "бс");
        strcpy_s(block[1][3], 4, "бс");
        strcpy_s(block[2][1], 4, "бс");
        strcpy_s(block[2][2], 4, "бс");
        strcpy_s(block[2][3], 4, "бс");
        strcpy_s(block[3][1], 4, "бс");
        strcpy_s(block[3][2], 4, "бс");
        strcpy_s(block[3][3], 4, "бс");
        break;
    }
}
