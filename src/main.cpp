#include <iostream>
#include <time.h>

#include "Game.hpp"


int main( int argc, char **argv ){
	// init rand
	srand(time(NULL));
	vdk::Game game;

	game.run();

	return 0;
}
