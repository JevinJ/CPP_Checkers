/*
 * board.h
 *
 *  Created on: Jul 12, 2017
 *      Author: Jevin
 */

#include <iostream>
#include <vector>

#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED
#include "node.h"
#endif


#ifndef BOARD_H_
#define BOARD_H_

//board class is used to monitor the general game state and
// uses a vector to contain all pawn locations and possible moves
struct Node;
struct Board {
    //basic white/black pawn class that is contained in a vector. Makes
    // up the board. Also has an empty/no piece constructor.
    class Square {
        Square(int a, char b) : type(a), ui_val(b) {};
    public:
        static Square empty() {return Square(0, '*');}
        static Square white() {return Square(1, 'w');}
        static Square black() {return Square(2, 'b');}
        Node *moves;
        int type = 0;
        char ui_val = '*';
        bool isKing = false;
        void make_king();
    };

    int white = 12;
    int black = 12;
    //Vectors containing all possible moves for all pawns
    std::vector<Node*> white_moves;
    std::vector<Node*> black_moves;
    std::vector<std::vector<Square>> board;
    Board() : board(8, std::vector<Board::Square>(8, Board::Square::empty())) {};
    //Initial board set-up
    void build();
    //Inverts board for correct x, y selection input and appearance.
    void print();
};
extern Board game;

#endif /* BOARD_H_ */
