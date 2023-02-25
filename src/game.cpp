#include <stdexcept>
#include <algorithm>
#include "game.hpp"

ResourceLoader	*g_resource_loader;

void Game::check_resource_loader() {
	SDL_Surface	*testSurface;
	if (g_resource_loader == nullptr) {
		g_resource_loader = new ResourceLoader();
		try {
			g_resource_loader->load_resource_definitions("resources.42CC");
		} catch (std::runtime_error &e) {
			delete g_resource_loader;
			g_resource_loader = nullptr;
			throw e;
		}
		testSurface = g_resource_loader->get_texture("assets/duck.png");
		if (!testSurface)
			delete g_resource_loader;
	}
}

Game::Game(): Window(TITLE, WINDOW_WIDTH, WINDOW_HEIGHT) {
	try {
		check_resource_loader();
	} catch (std::runtime_error &e) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", e.what(), nullptr);
		this->close();
		return;
	}
}

void Game::draw_scene() {
	for(auto it = this->_objects.begin(); it < this->_objects.end(); it++)
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

void Game::remove_object(Object *object) {
	auto it = std::find(this->_objects.begin(), this->_objects.end(), object);
	if (it != this->_objects.end())
		this->_objects.erase(it);
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
	for (auto & _object : this->_objects)
		delete _object;
}
