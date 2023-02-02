#include "game.hpp"

static ResourceLoader *resource_loader;

Game::Game(): Window(TITLE, WINDOW_WIDTH, WINDOW_HEIGHT) {
	if (resource_loader == nullptr) {
		resource_loader = new ResourceLoader();
		resource_loader->load_resource_definitions("resources.42CC");
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
}
