#include "GameUtil.h"
#include "Board.h"
#include "BlockGame.h"
#include <cstdlib>
#include <ctime>
#include "KeyDef.h"

using namespace std;

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
                total_point = 0;
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
                    show_block(f_block, s_block, t_block, block_used);
                    key = key_control();

                    if (key == 6) {
                        if (!block_used[0]) {
                            move_and_place_block(m_board, c_board, f_block);
                            block_used[0] = true;
                            main_block(f_block);
                        }
                        continue;
                    }
                    else if (key == 7) {
                        if (!block_used[1]) {
                            move_and_place_block(m_board, c_board, s_block);
                            block_used[1] = true;
                            main_block(s_block);
                        }
                        continue;
                    }
                    else if (key == 8) {
                        if (!block_used[2]) {
                            move_and_place_block(m_board, c_board, t_block);
                            block_used[2] = true;
                            main_block(t_block);
                        }
                        continue;
                    }
                    else if (key == k_back) {
                        cout << "\n이름을 입력하세요(랭킹 저장): ";
                        string name;
                        cin >> name;
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
                if (info_num == 9)
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
