#include "game.hpp"

static ResourceLoader *resource_loader;

Game::Game(): Window(TITLE, WINDOW_WIDTH, WINDOW_HEIGHT) {
	SDL_Surface	*testSurface;
	if (resource_loader == nullptr) {
		resource_loader = new ResourceLoader();
		resource_loader->load_resource_definitions("resources.42CC");
		testSurface = resource_loader->get_texture("assets/duck.png");
		if (!testSurface)
			delete resource_loader;
	}
}

void Game::loop() {
	while (!this->is_closed()) {
		this->prepare_scene();
		this->poll_events();
		this->draw_scene();
		this->present_scene();
	}
}

void Game::draw_scene()
{
	SDL_Surface	*surface;

	surface = resource_loader->get_texture("assets/banana.png");
	if (surface) {
		SDL_Texture *testTexture = SDL_CreateTextureFromSurface(this->get_renderer(), surface);
		SDL_DestroySurface(surface);
		SDL_RenderTexture(this->get_renderer(), testTexture, nullptr, nullptr);
		SDL_DestroyTexture(testTexture);
	}
}
