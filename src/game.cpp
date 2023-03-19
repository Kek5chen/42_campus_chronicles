#include <stdexcept>
#include <algorithm>
#include "game.hpp"
#include "objects/player.hpp"
#include "objects/wavefront.hpp"

ResourceLoader	*g_resource_loader;

Game::Game(): Window(TITLE, WINDOW_WIDTH, WINDOW_HEIGHT) {
	try {
		check_resource_loader();
	} catch (std::runtime_error &e) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", e.what(), nullptr);
		this->close();
		return;
	}
	auto deer = new WaveFrontObject(this);
	deer->load_obj(g_resource_loader, "assets/deer_gpl.obj");
	deer->pos = {-6.5f, 0, -2000};
	deer->set_rotation(30, 0, 0);
	this->add_object(deer);
}

Game::~Game() {
	for (auto & _object : this->_objects)
		delete _object;
}

void Game::check_resource_loader() {
	SDL_Surface	*testSurface;

	if (g_resource_loader == nullptr) {
		g_resource_loader = new ResourceLoader();
		try {
			g_resource_loader->load_resource_definitions("resources.42CC");
		} catch (std::exception &e) {
			delete g_resource_loader;
			g_resource_loader = nullptr;
		}
		testSurface = g_resource_loader->load_texture("assets/duck.png");
		if (!testSurface)
			delete g_resource_loader;
		SDL_DestroySurface(testSurface);
	}
}

void Game::update_scene() {
	this->update_camera();
	for (auto it = this->_objects.begin(); it < this->_objects.end(); it++)
		(*it)->update();
}

void Game::draw_scene() {
	for(auto it = this->_objects.begin(); it < this->_objects.end(); it++)
		(*it)->draw();
}

void Game::add_object(Object* object)
{
	for (auto it = this->_objects.begin(); it != this->_objects.end(); it++) {
		if ((*it)->pos.z > object->pos.z) {
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
		this->update_scene();
		this->draw_scene();
		this->present_scene();
	}
}

void Game::update_camera() {
	if (this->is_key_pressed(SDL_SCANCODE_A))
		this->camera.pos.x -= .1f;
	if (this->is_key_pressed(SDL_SCANCODE_D))
		this->camera.pos.x += .1f;
	if (this->is_key_pressed(SDL_SCANCODE_W))
		this->camera.pos.y += .1f;
	if (this->is_key_pressed(SDL_SCANCODE_S))
		this->camera.pos.y -= .1f;
	if (this->is_key_pressed(SDL_SCANCODE_Q))
		this->camera.pos.z += 100.f;
	if (this->is_key_pressed(SDL_SCANCODE_E))
		this->camera.pos.z -= 100.f;
}
