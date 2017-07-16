/*
 * node.h
 *
 *  Created on: Jul 12, 2017
 *      Author: Jevin
 */

#include <string>

#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED
#include "board.h"
#endif // BOARD_H_INCLUDED


#ifndef NODE_H_
#define NODE_H_

//Nodes trees are used to store all valid path points for all pawns in a turn
struct Node {
	std::pair<int, int> move;

	Node *up_left = NULL;
	Node *up_right = NULL;
	Node *down_left = NULL;
	Node *down_right = NULL;
};

void build_nodes(Board::Square orig, Node *root, int y, int x, bool isJump);

//helper function to create new move nodes in tree with y, x
// coordinates for that possible move
Node *newNode(int y, int x);

//updating all possible move nodes on each turn
void update_nodes();

//recursive debugging function to output which path a move node tree is taking
// starting with first node and direction(eg, "root: ")
void print_tree(Node *root, std::string direction);

#endif /* NODE_H_ */
