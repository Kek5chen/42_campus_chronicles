#pragma once

#include "includes.hpp"
#include "resources.hpp"
#include <string>

// #ifdef _WIN32
// #include <SDL/SDL.h> /* Windows-specific SDL2 library */
// #else
// #include <SDL.h> /* macOS- and GNU/Linux-specific */
// #endif

struct KeyState {
	unsigned int	pressed : 1;
	unsigned int	changed : 1;
};

class Window {
public:
	Window(std::string title, int width, int height);
	~Window();

	bool			is_closed() const;
	void			poll_events();
	void			prepare_scene();
	virtual void	draw_scene();
	void			present_scene();
	SDL_Renderer	*get_renderer() const;
	void 			set_title(std::string title);
	bool			is_key_down(SDL_Scancode key);
	bool			is_key_pressed(SDL_Scancode key);
	bool			is_key_released(SDL_Scancode key);
	void			close();

protected:
	bool 			init();

	std::string 	_title;
	int				_width;
	int				_height;
	int				x{};
	int				y{};
	bool 			_closed = false;
	SDL_Window		*_window = nullptr;
	SDL_Renderer	*_renderer = nullptr;
	bool			_key_states_changed{};
	KeyState		_key_states[SDL_NUM_SCANCODES]{};
};
