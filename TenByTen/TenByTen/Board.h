#pragma once

void allocate_board(char**** board);
void allocate_block(char**** block);
void deallocate_board(char*** board);
void deallocate_block(char*** block);
void main_board(char*** board);
void main_block(char*** block);
void create_block(char*** block);
void draw_board(char*** board);
void draw_block(int x, int y, char*** block);
void show_block(char*** f_block, char*** s_block, char*** t_block, bool* block_used);
