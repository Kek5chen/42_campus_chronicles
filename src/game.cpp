#include "game.hpp"

ResourceLoader	*resource_loader;

void Game::check_resource_loader() {
	SDL_Surface	*testSurface;
	if (resource_loader == nullptr) {
		resource_loader = new ResourceLoader();
		resource_loader->load_resource_definitions("resources.42CC");
		testSurface = resource_loader->get_texture("assets/duck.png");
		if (!testSurface)
			delete resource_loader;
	}
}

Game::Game(): Window(TITLE, WINDOW_WIDTH, WINDOW_HEIGHT) {
	check_resource_loader();
}

void Game::draw_scene() {
	for(auto it = this->_objects.begin(); it !=  this->_objects.end(); it++)
		(*it)->draw(this);
}

void Game::add_object(Object* object)
{
	for (auto it = this->_objects.begin(); it != this->_objects.end(); it++) {
		if ((*it)->_z > object->_z) {
			this->_objects.insert(it, object);
			return;
		}
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
