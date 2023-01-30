#include "window.hpp"
#include <iostream>

Window::Window(const string &title, int width, int height) : _title(title), _width(width), _height(height) {
	if (!init())
		this->_closed = true;
}

Window::~Window() {
	SDL_DestroyWindow(this->_window);
	SDL_Quit();
}

bool Window::init() {
	if (SDL_Init(SDL_INIT_VIDEO)) {
		cerr << "Failed to initialize SDL\n";
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
		cerr << "Failed to create window\n";
		return false;
	}

	return true;
}

void Window::pollEvents() {
	SDL_Event event;

	if (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_EVENT_QUIT:
			_closed = true;
			break;
		default:
			break;
		}
	}
}