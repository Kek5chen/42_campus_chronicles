#include "window.hpp"
#include <iostream>
#include <utility>

static ResourceLoader *resource_loader;

Window::Window(std::string title, int width, int height) : _title(std::move(title)), _width(width), _height(height) {
	if (!init())
		this->_closed = true;

	resource_loader = new ResourceLoader();
	resource_loader->load_resource_definitions("resources.42CC");
}

Window::~Window() {
	SDL_DestroyWindow(this->_window);
	SDL_Quit();
}

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

void Window::prepareScene() {
	SDL_SetRenderDrawColor(this->_renderer, 0, 0, 0, 255);
	SDL_RenderClear(this->_renderer);
}

void Window::drawScene() {
	SDL_Surface* surface = resource_loader->get_texture("assets/img.png");
	if (surface == nullptr) {
		std::cerr << "Failed to load texture\n";
		return;
	}
	SDL_Texture* texture = SDL_CreateTextureFromSurface(this->_renderer, surface);
	SDL_DestroySurface(surface);
	SDL_RenderTexture(this->_renderer, texture, nullptr, nullptr);
	SDL_DestroyTexture(texture);
}

void Window::presentScene() {
	SDL_RenderPresent(this->_renderer);
}
