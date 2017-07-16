/*
 * ai.cpp
 *
 *  Created on: Jul 13, 2017
 *      Author: Jevin
 */

#include <algorithm>
#include <deque>
#include <math.h>
#include <vector>
#include "ai.h"
#include "misc.h"

using namespace std;


/*basic AI based on the highest possible move/jump count for a given pawn
 */
int most_jumps = 0;

//lambda functions for randomizing and sorting pawn paths
//randomize function for ai pawn selection, randomizes pawns with same jump count before being sorted.
const auto randomize = [&](int x) -> int {return rand() % x;};

//inner-most sort and remove functions for a single pawns entire move set
auto sort_p_jumps = [&](const pair<deque<pair<int, int>>, int> &a, const pair<deque<pair<int, int>>, int> &b) -> bool {return a.second > b.second;};
auto remove_low_p_jumps = [&](const pair<deque<pair<int, int>>, int> &x) -> bool {return x.second < most_jumps;};

//outer sort/remove for every ai pawn's move set
auto sort_set_jumps = [&](const vector<pair<deque<pair<int, int>>, int>> &a, const vector<pair<deque<pair<int, int>>, int>> &b) -> bool {return a[0].second > b[0].second;};
auto remove_low_set_jumps = [&](const vector<pair<deque<pair<int, int>>, int>> &x) -> bool {return x[0].second < most_jumps;};


//measures and returns distances for a given ai path, used to give ai kill move preference
int total_jumps(deque<pair<int, int>> path) {
    int jumps = 0;
    if(path.size() <= 1) {
        return 0;
    }
    for(int i = 0; i < path.size()-1; i++) {
        int x = path[i].first;
        int x_ = path[i+1].first;
        int y = path[i].second;
        int y_ = path[i+1].second;
        double x_sq = (x-x_)*(x-x_);
        double y_sq = (y-y_)*(y-y_);
        if(sqrt(x_sq + y_sq) < 1) {
            continue;
        }
        if(sqrt(x_sq + y_sq) >= 2) {
            jumps += 2;
        }
        if(sqrt(x_sq + y_sq) > 1 and sqrt(x_sq + y_sq) < 2) {
            jumps += 1;
        }
    }
    return jumps;
}

//pathfinding function to return a queue of all direct paths in a move tree
void find_path(std::vector<std::pair<std::deque<std::pair<int, int>>, int>> &p_paths, std::deque<std::pair<int, int>> path, Node *root) {
    if(root == NULL) {
        return;
    }
    path.push_back(make_pair(root->move.first, root->move.second));
    if(path.size() > 1) {
        p_paths.push_back(make_pair(path, total_jumps(path)));
    }
    if(root->up_left == NULL and root->up_right == NULL and root->down_left == NULL and root->down_right == NULL) {
        path.pop_back();
        return;
    }
    find_path(p_paths, path, root->up_left);
    find_path(p_paths, path, root->up_right);
    find_path(p_paths, path, root->down_left);
    find_path(p_paths, path, root->down_right);
}


void ai_move() {
    most_jumps = 0;
    //vector containing a pair of queued valid paths and their jump count
    // for each possible pawn, contained in a vector to be randomized and sorted
    // to get a pawn with the highest jump count.
    // vec[vec[pair(que[pair(y, x)], jumps)
    std::vector<std::vector<std::pair<std::deque<std::pair<int, int>>, int>>> test;
    for(int i = 0; i < game.white_moves.size(); i++) {
        vector<pair<deque<pair<int, int>>, int>> p_paths;
        deque<pair<int, int>> path;
        Node *ai_pawn = game.white_moves[i];
        path.push_back(make_pair(ai_pawn->move.first, ai_pawn->move.second));
        find_path(p_paths, path, ai_pawn->up_left);
        find_path(p_paths, path, ai_pawn->up_right);
        find_path(p_paths, path, ai_pawn->down_left);
        find_path(p_paths, path, ai_pawn->down_right);

        for(int i = 0; i < p_paths.size(); i++) {
            if(p_paths[i].second > most_jumps) {
                most_jumps = p_paths[i].second;
            }
        }
        p_paths.erase(remove_if(p_paths.begin(), p_paths.end(), remove_low_p_jumps), p_paths.end());
        random_shuffle(p_paths.begin(), p_paths.end(), randomize);
        sort(p_paths.begin(), p_paths.end(), sort_p_jumps);
        if(p_paths.size() > 0) {
            test.push_back(p_paths);
        }

    }
    random_shuffle(test.begin(), test.end(), randomize);
    sort(test.begin(), test.end(), sort_set_jumps);
    test.erase(remove_if(test.begin(), test.end(), remove_low_set_jumps), test.end());
    deque<pair<int, int>> ai_path = test[0][0].first;
    for(int i = 0; i < ai_path.size()-1; i++) {
        make_move(ai_path[i].first, ai_path[i].second, ai_path[i+1].first, ai_path[i+1].second);
    }
}




