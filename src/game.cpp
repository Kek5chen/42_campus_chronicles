#include <stdexcept>
#include "game.hpp"

ResourceLoader	*resource_loader;

void Game::check_resource_loader() {
	SDL_Surface	*testSurface;
	if (resource_loader == nullptr) {
		resource_loader = new ResourceLoader();
		try {
			resource_loader->load_resource_definitions("resources.42CC");
		} catch (std::runtime_error &e) {
			delete resource_loader;
			resource_loader = nullptr;
			throw e;
		}
		testSurface = resource_loader->get_texture("assets/duck.png");
		if (!testSurface)
			delete resource_loader;
	}
}

Game::Game(): Window(TITLE, WINDOW_WIDTH, WINDOW_HEIGHT) {
	try {
		check_resource_loader();
	} catch (std::runtime_error &e) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", e.what(), nullptr);
		return;
	}
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
	this->_objects.push_back(object);
}

void Game::loop() {
	while (!this->is_closed()) {
		this->prepare_scene();
		this->poll_events();
		this->draw_scene();
		this->present_scene();
	}
}

Game::~Game() {
	for (auto it = this->_objects.begin(); it != this->_objects.end(); it++)
		delete *it;
}
