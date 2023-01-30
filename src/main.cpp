#include <stdio.h> /* printf and fprintf */
#include "window.hpp"


/* Sets constants */
#define WIDTH 800
#define HEIGHT 600
#define DELAY 10000

int main (int argc, char **argv)
{
	Window win("testWin", 800, 600);

	while (!win.isClosed()) {
		win.pollEvents();
	}
	return 0;
}