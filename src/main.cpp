#include <iostream>
#include <sstream>
#include "game.hpp"
#include "engine/exceptions/stackexception.hpp"


int main (int argc, char **argv)
{
	GLOBAL_EXCEPT_TRY
		Game new_game;
		new_game.loop();
	GLOBAL_EXCEPT_CATCH
	return 0;
}