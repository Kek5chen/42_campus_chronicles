#pragma once

#define TITLE "42 Campus Chronicles"
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#ifdef _WIN32
#include <SDL/SDL.h> /* Windows-specific SDL2 library */
#else
#include <SDL.h> /* macOS- and GNU/Linux-specific */
#endif