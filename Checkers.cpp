#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "ai.h"
#include "board.h"
#include "misc.h"
#include "node.h"
#include "player.h"

using namespace std;


Board game;
int main() {
	srand(time(NULL));
	game.build();
	while(true) {
	    game.print();
	    if(win_condition()) {
	        break;
	    }
	    update_nodes();
		cout << "Your turn." << '\n';
		select_pawn();
	    game.print();
	    if(win_condition()) {
	        break;
	    }
		update_nodes();
		cout << "-------------------------" << '\n';
		cout << "AI turn." << '\n';
		ai_move();
	}
	return 0;
}
