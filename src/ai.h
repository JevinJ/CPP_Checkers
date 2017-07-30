/*
 * ai.h
 *
 *  Created on: Jul 13, 2017
 *      Author: Jevin
 */

#include <deque>
#include <vector>

#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED
#include "node.h"
#endif //NODE_H_INCLUDED


#ifndef AI_H_
#define AI_H_

/*basic AI based on the highest possible move/jump count for a given pawn
 */
//measures and returns distances for a given ai path, used to give ai kill move preference
int total_jumps(std::deque<std::pair<int, int>> path);

//pathfinding function to return a queue of all direct paths in a move tree
void find_path(std::vector<std::pair<std::deque<std::pair<int, int>>, int>> &all_paths, std::deque<std::pair<int, int>> path, Node *root);

//Basic AI based on the highest possible move count for a given pawn
void ai_move();

#endif /* AI_H_ */
