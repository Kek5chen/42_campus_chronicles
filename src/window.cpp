#include "window.hpp"
#include <iostream>
#include <utility>

Window::Window(std::string title, int width, int height) : _title(std::move(title)), _width(width), _height(height) {
	if (!init())
		this->_closed = true;
}

Window::~Window() {
	SDL_DestroyWindow(this->_window);
	SDL_Quit();
}

bool Window::is_closed() const { return _closed; }

bool Window::init() {
	if (SDL_Init(SDL_INIT_VIDEO)) {
		std::cerr << "Failed to initialize SDL\n";
		return false;
	}

	this->_window = SDL_CreateWindow(this->_title.c_str(),
									 SDL_WINDOWPOS_CENTERED,
									 SDL_WINDOWPOS_CENTERED,
									 this->_width,
									 this->_height,
									 SDL_WINDOW_RESIZABLE
									);
	if (!this->_window) {
		std::cerr << "Failed to create window\n";
		return false;
	}

	this->_renderer = SDL_CreateRenderer(this->_window, nullptr,
										 SDL_RENDERER_ACCELERATED);
	if (!this->_renderer) {
		std::cerr << "Failed to create renderer\n";
		return false;
	}

	SDL_SetRenderVSync(_renderer, 1);
	return true;
}

void Window::poll_events() {
	SDL_Event event;

	if (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_EVENT_QUIT:
			_closed = true;
			break;
		case SDL_EVENT_WINDOW_RESIZED:
			this->_width = event.window.data1;
			this->_height = event.window.data2;
			break;
		case SDL_EVENT_WINDOW_MOVED:
			this->x = event.window.data1;
			this->y = event.window.data2;
			break;
		case SDL_EVENT_KEY_DOWN:
		case SDL_EVENT_KEY_UP:
			if (event.key.repeat == 0) {
				this->_key_states_changed = true;
				this->_key_states[event.key.keysym.scancode].pressed = event.key.state == SDL_PRESSED;
				this->_key_states[event.key.keysym.scancode].changed = true;
			}
			break;
		default:
			break;
		}
	}
}

void Window::prepare_scene() {
	SDL_SetRenderDrawColor(this->_renderer, 0, 0, 0, 255);
	SDL_RenderClear(this->_renderer);
	if (this->_key_states_changed) {
		for (auto &key_state: this->_key_states)
			key_state.changed = false;
		this->_key_states_changed = false;
	}
}

void Window::draw_scene() {}

void Window::present_scene() {
	SDL_RenderPresent(this->_renderer);
}

SDL_Renderer* Window::get_renderer() const
{
	return this->_renderer;
}

void Window::set_title(std::string title)
{
	this->_title = std::move(title);
	SDL_SetWindowTitle(this->_window, this->_title.c_str());
}

bool Window::is_key_down(SDL_Scancode key) {
	return this->_key_states[key].pressed && this->_key_states[key].changed;
}

bool Window::is_key_pressed(SDL_Scancode key) {
	return this->_key_states[key].pressed;
}

bool Window::is_key_released(SDL_Scancode key) {
	return !this->_key_states[key].pressed && this->_key_states[key].changed;
}

void Window::close() {
	this->_closed = true;
}
