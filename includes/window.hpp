#pragma once

#include "includes.hpp"
#include "resources.hpp"
#include <string>

// #ifdef _WIN32
// #include <SDL/SDL.h> /* Windows-specific SDL2 library */
// #else
// #include <SDL.h> /* macOS- and GNU/Linux-specific */
// #endif

class Window {
	public:
		Window(std::string title, int width, int height);
		~Window();

		bool is_closed() const;

		void			poll_events();
		void			prepare_scene();
		virtual void	draw_scene();
		void			present_scene();

	private:
		bool init();

		const std::string _title;
		const int _width;
		const int _height;
		
		bool _closed = false;
		SDL_Window *_window = nullptr;
		SDL_Renderer *_renderer = nullptr;
};