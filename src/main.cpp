#include <stdio.h> /* printf and fprintf */
#include "window.hpp"


/* Sets constants */
#define WIDTH 800
#define HEIGHT 600
#define DELAY (1000 / 60)

int main (int argc, char **argv)
{
	Window win("42 Campus Chronicles", 800, 600);

	while (!win.isClosed()) {
		win.prepareScene();
		win.pollEvents();
		win.presentScene();
		SDL_Delay(DELAY);
	}
	return 0;
}