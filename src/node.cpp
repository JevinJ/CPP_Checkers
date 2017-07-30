/*
 * node.cpp
 *
 *  Created on: Jul 12, 2017
 *      Author: Jevin
 */

#include <iostream>
#include <vector>
#include "board.h"
#include "node.h"


//helper function to create new move nodes in tree with y, x
// coordinates for that possible move
Node *newNode(int y, int x) {
    Node *node = new (struct Node);
    node->move = std::make_pair(y, x);
    return(node);
}

//recursively builds nodes for each pawn after each turn to create possible
// and valid paths for ai and player move validation
void build_nodes(Board::Square orig, Node *root, int y, int x, bool isJump) {
    //if king or player(black) type
    if(orig.isKing or orig.type == 2) {
        //basic up left movement
        if((y+1 >= 0 and y+1 < 8) and (x-1 >= 0 and x-1 < 8)) {
            //basic up left
            if(game.board[y+1][x-1].type == 0 and not isJump) {
                root->up_left = newNode(y+1, x-1);
            }
            //enemy jump check
            if((y+2 >= 0 and y+2 < 8) and (x-2 >= 0 and x-2 < 8) and game.board[y+2][x-2].type == 0 and (game.board[y+1][x-1].type != orig.type and game.board[y+1][x-1].type != 0)) {
                root->up_left = newNode(y+2, x-2);
                build_nodes(orig, root->up_left, y+2, x-2, true);
            }
        }
        //basic up right movement
        if((y+1 >= 0 and y+1 < 8) and (x+1 >= 0 and x+1 < 8) ) {
            //basic up right
            if(game.board[y+1][x+1].type == 0 and not isJump) {
                root->up_right = newNode(y+1, x+1);
            }
            //enemy jump check
            if((y+2 >= 0 and y+2 < 8) and (x+2 >= 0 and x+2 < 8) and game.board[y+2][x+2].type == 0 and (game.board[y+1][x+1].type != orig.type and game.board[y+1][x+1].type != 0)) {
                root->up_right = newNode(y+2, x+2);
                build_nodes(orig, root->up_right, y+2, x+2, true);
            }
        }
    }
    //if king or AI(white) type
    if(orig.isKing or orig.type == 1) {
        //down left movement
        if((y-1 >= 0 and y-1 < 8) and (x-1 >= 0 and x-1 < 8)) {
            //king basic down left
            if(game.board[y-1][x-1].type == 0 and not isJump) {
                root->down_left = newNode(y-1, x-1);
            }
            //jump check
            if((y-2 >= 0 and y-2 < 8) and (x-2 >= 0 and x-2 < 8) and game.board[y-2][x-2].type == 0 and (game.board[y-1][x-1].type != orig.type and game.board[y-1][x-1].type != 0)) {
                root->down_left = newNode(y-2, x-2);
                build_nodes(orig, root->down_left, y-2, x-2, true);
            }
        }
        //down right movement
        if((y-1 >= 0 and y-1 < 8) and (x+1 >= 0 and x+1 < 8)) {
            //king basic down right
            if(game.board[y-1][x+1].type == 0 and not isJump) {
                root->down_right = newNode(y-1, x+1);
            }
            //jump check
            if((y-2 >= 0 and y-2 < 8) and (x+2 >= 0 and x+2 < 8) and game.board[y-2][x+2].type == 0 and (game.board[y-1][x+1].type != orig.type and game.board[y-1][x+1].type != 0)) {
                root->down_right = newNode(y-2, x+2);
                build_nodes(orig, root->down_right, y-2, x+2, true);
            }
        }
    }
}

//updating all possible move nodes on each turn
void update_nodes() {
    game.white_moves.clear();
    game.black_moves.clear();
    for(int y = 7; y >= 0; y--) {
        for(int x = 0; x < 8; x++) {
            delete game.board[y][x].moves;
            game.board[y][x].moves = newNode(y, x);
            build_nodes(game.board[y][x], game.board[y][x].moves, y, x, false);
            if(game.board[y][x].type == 1) {
                game.white_moves.push_back(game.board[y][x].moves);
            }
            if(game.board[y][x].type == 2) {
                game.black_moves.push_back(game.board[y][x].moves);
            }
        }
    }
}

//recursive debugging function to output which path a move node tree is taking
// starting with first node and direction(eg, "root: ")
void print_tree(Node *root, std::string direction) {
    if(root == NULL) {
        return;
    }
    std::cout << direction << root->move.second << "," << root->move.first << '\n';
    print_tree(root->up_left, "up left: ");
    print_tree(root->up_right, "up right: ");
    print_tree(root->down_left, "down left: ");
    print_tree(root->down_right, "down right: ");
}



