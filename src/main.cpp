#include "game.hpp"
#include "engine/error_handler.hpp"


int main (int argc, char **argv)
{
	register_signal_handler();
	Game new_game;
	new_game.loop();
	return 0;
}