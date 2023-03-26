#pragma once
#ifdef _WIN32
# include <SDL3/SDL.h>
# include <SDL3/SDL_image.h>
#else
# include <SDL.h>
# include <SDL_image.h>
#include <memory>

#define TITLE "42 Campus Chronicles"
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600


using SurfacePtr = std::shared_ptr<SDL_Surface>;
using TexturePtr = std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)>;