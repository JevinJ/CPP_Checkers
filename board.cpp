/*
 * board.cpp
 *
 *  Created on: Jul 12, 2017
 *      Author: Jevin
 */

#include "board.h"


void Board::Square::make_king() {
    isKing = true;
    ui_val = toupper(ui_val);
}

//Initial board set-up
void Board::build() {
    //White pieces
    for(int y = 5; y < 8; y++) {
        for(int x = 0; x < 8; x++) {
            if(y % 2 == 0 and x % 2 == 0) {
                game.board[y][x] = Board::Square::white();
            }
            if(y % 2 != 0 and x % 2 != 0) {
                game.board[y][x] = Board::Square::white();
            }
        }
    }
    //Black pieces
    for(int y = 0; y <= 2; y++) {
        for(int x = 0; x < 8; x++) {
            if(y % 2 == 0 and x % 2 == 0) {
                game.board[y][x] = Board::Square::black();
            }
            if(y % 2 != 0 and x % 2 != 0) {
                game.board[y][x] = Board::Square::black();
            }
        }
    }
}
//Inverts board for correct x, y selection input and appearance.
void Board::print() {
    for(int y = 7; y >= 0; y--) {
        for(int x = 0; x < 8; x++) {
            std::cout << "  " << game.board[y][x].ui_val;
        }
        std::cout << '\n';
    }
}





