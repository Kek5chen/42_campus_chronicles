#include "window.hpp"
#include <iostream>
#include <utility>

Window::Window(std::string title, int width, int height) : _title(std::move(title)), _width(width), _height(height) {
	if (!init())
		this->_closed = true;
}

Window::~Window() {
	this->_window.reset();
	this->_renderer.reset();
	SDL_Quit();
}

bool Window::is_closed() const { return _closed; }

bool Window::init() {
	if (SDL_Init(SDL_INIT_VIDEO)) {
		std::cerr << "Failed to initialize SDL\n";
		return false;
	}

	this->_window.reset(SDL_CreateWindow(this->_title.c_str(),
									 SDL_WINDOWPOS_CENTERED,
									 SDL_WINDOWPOS_CENTERED,
									 this->_width,
									 this->_height,
									 SDL_WINDOW_RESIZABLE
									), SDL_DestroyWindow);
	if (!this->_window) {
		std::cerr << "Failed to create window\n";
		return false;
	}
	SDL_GetWindowPosition(this->_window.get(), &_x, &_y);

	this->_renderer.reset(SDL_CreateRenderer(this->_window.get(), nullptr,
										 SDL_RENDERER_ACCELERATED), SDL_DestroyRenderer);
	if (!this->_renderer) {
		std::cerr << "Failed to create renderer\n";
		return false;
	}

	SDL_SetRenderVSync(this->_renderer.get(), 1);
	return true;
}

void Window::poll_events() {
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_EVENT_QUIT:
			_closed = true;
			break;
		case SDL_EVENT_WINDOW_RESIZED:
			this->_width = event.window.data1;
			this->_height = event.window.data2;
			break;
		case SDL_EVENT_WINDOW_MOVED:
			this->_x = event.window.data1;
			this->_y = event.window.data2;
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
	SDL_SetRenderDrawColor(this->_renderer.get(), 0, 0, 0, 255);
	SDL_RenderClear(this->_renderer.get());
	if (this->_key_states_changed) {
		for (auto &key_state: this->_key_states)
			key_state.changed = false;
		this->_key_states_changed = false;
	}
}

void Window::draw_scene() {}

void Window::present_scene() {
	SDL_RenderPresent(this->_renderer.get());
}

std::weak_ptr<SDL_Renderer>	Window::get_renderer() const
{
	return this->_renderer;
}

void Window::set_title(std::string title)
{
	this->_title = std::move(title);
	SDL_SetWindowTitle(this->_window.get(), this->_title.c_str());
}

int Window::get_width() const {
	return _width;
}

int Window::get_height() const {
	return _height;
}

int Window::get_x() const {
	return _x;
}

int Window::get_y() const {
	return _y;
}

void Window::set_position(int x, int y) {
	this->_x = x;
	this->_y = y;
	SDL_SetWindowPosition(this->_window.get(), this->_x, this->_y);
}

void Window::set_size(int width, int height) {
	this->_width = width;
	this->_height = height;
	SDL_SetWindowSize(this->_window.get(), this->_width, this->_height);
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
