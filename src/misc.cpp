/*
 * misc.cpp
 *
 *  Created on: Jul 13, 2017
 *      Author: Jevin
 */

#include <stdlib.h>
#include "board.h"
#include "misc.h"


void make_move(int y, int x, int new_y, int new_x) {
    std::swap(game.board[y][x], game.board[new_y][new_x]);
    //Removing pieces if jumped
    if(abs(y-new_y) > 1 or abs(x-new_x) > 1) {
        if(game.board[(y+new_y)/2][(x+new_x)/2].type == 1) {
            game.white -= 1;
        }
        if(game.board[(y+new_y)/2][(x+new_x)/2].type == 2) {
            game.black -= 1;
        }
        game.board[(y+new_y)/2][(x+new_x)/2] = Board::Square::empty();
    }
    //'king me' checks
    if(game.board[new_y][new_x].type == 1 and not game.board[new_y][new_x].isKing and new_y == 0) {
        game.board[new_y][new_x].make_king();
    }
    if(game.board[new_y][new_x].type == 2 and not game.board[new_y][new_x].isKing and new_y == 7) {
        game.board[new_y][new_x].make_king();
    }
}

bool win_condition() {
    if(game.white == 0) {
        std::cout << "PLAYER WINS!" << '\n';
        return true;
    }
    if(game.black == 0) {
        std::cout << "AI WINS!" << '\n';
        return true;
    }
    return false;
}

