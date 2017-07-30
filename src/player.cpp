/*
 * player.cpp
 *
 *  Created on: Jul 13, 2017
 *      Author: Jevin
 */

#include <iostream>
#include "board.h"
#include "misc.h"
#include "player.h"


bool is_valid_move(Node *root, std::pair<int, int> move) {
    if(root == NULL) {
        return false;
    }
    if(root->move == move) {
        return true;
    }
    if(is_valid_move(root->up_left, move)) return true;
    if(is_valid_move(root->up_right, move)) return true;
    if(is_valid_move(root->down_left, move)) return true;
    if(is_valid_move(root->down_right, move)) return true;
    return false;
}

//helps update new location for player pawn by keeping track of which node direction we're going
// NOTE: Updates node, not ui location in /misc.h
void update_player_location(Node *&player_pawn, Node *root, std::pair<int, int> move) {
    if(root == NULL) {
        return;
    }
    if(root->move == move) {
        player_pawn = root;
        return;
    }
    update_player_location(player_pawn, root->up_left, move);
    update_player_location(player_pawn, root->up_right, move);
    update_player_location(player_pawn, root->down_left, move);
    update_player_location(player_pawn, root->down_right, move);
}

void select_pawn() {
    Node *player_pawn;
    int x = 0, y = 0;
    while(true) {
        std::cout << "Enter X location to select a pawn." << '\n';
        std::cin >> x;
        std::cout << "Enter Y location to select a pawn." << '\n';
        std::cin >> y;
        if((x >= 8 or x < 0) or (y >= 8 or y < 0) or game.board[y][x].type != 2) {
            std::cout << "Invalid selection. Try again." << '\n';
            continue;
        }
        player_pawn = game.board[y][x].moves;
        if(player_pawn->up_left == NULL and player_pawn->up_right == NULL and player_pawn->down_left == NULL and player_pawn->down_right == NULL) {
            std::cout << "No moves available with this pawn, select another." << '\n';
            continue;
        }
        break;
    }
    while(player_pawn->up_left != NULL or player_pawn->up_right != NULL or player_pawn->down_left != NULL or player_pawn->down_right != NULL) {
        int new_x = 0, new_y = 0;
        std::cout << "You have a move remaining." << '\n';
        std::cout << "Enter the X location to move to." << '\n';
        std::cin >> new_x;
        std::cout << "Enter the Y location to move to." << '\n';
        std::cin >> new_y;
        if(is_valid_move(player_pawn, std::make_pair(new_y, new_x))) {
            update_player_location(player_pawn, player_pawn, std::make_pair(new_y, new_x));
            game.board[y][x].moves = player_pawn;
            make_move(y, x, new_y, new_x);
            y = new_y, x = new_x;
        }
        else {
            std::cout << "Invalid selection, try again." << '\n';
        }
    }
}




