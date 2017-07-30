/*
 * player.h
 *
 *  Created on: Jul 13, 2017
 *      Author: Jevin
 */

#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED
#include "node.h"
#endif


#ifndef PLAYER_H_
#define PLAYER_H_

bool is_valid_move(Node *root, std::pair<int, int> move);

//helps update new location for player pawn by keeping track of which node direction we're going
// NOTE: Updates node, not ui location
void update_player_location(Node *root, std::pair<int, int> move);

void select_pawn();

#endif /* PLAYER_H_ */
