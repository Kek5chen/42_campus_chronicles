#pragma once

#define TITLE "42 Campus Chronicles"
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#ifdef _WIN32
# include <SDL3/SDL.h>
# include <SDL3/SDL_image.h>
#else
# include <SDL.h>
# include <SDL_image.h>
#endif