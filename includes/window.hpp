#pragma once

#include "includes.hpp"
#include <string>

// #ifdef _WIN32
// #include <SDL/SDL.h> /* Windows-specific SDL2 library */
// #else
// #include <SDL.h> /* macOS- and GNU/Linux-specific */
// #endif

using namespace std;

class Window {
	public:
		Window(string title, int width, int height);
		~Window();

		inline bool isClosed() const { return _closed; };

		void pollEvents();
		void prepareScene();
		void drawScene();
		void presentScene();

	private:
		bool init();

		const string _title;
		const int _width;
		const int _height;
		
		bool _closed = false;
		SDL_Window *_window = nullptr;
		SDL_Renderer *_renderer = nullptr;
};