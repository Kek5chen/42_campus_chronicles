#pragma once

#ifdef _WIN32
#include <SDL/SDL.h> /* Windows-specific SDL2 library */
#else
#include <SDL.h> /* macOS- and GNU/Linux-specific */
#endif