#include "objects/objects.hpp"
#include "window.hpp"
#include "includes.hpp"
#include "game.hpp"

Object::Object(Game* game) : _game(game) {}

Object::~Object() {
	if (this->_surface != nullptr)
		SDL_DestroySurface(this->_surface);
	if (this->_texture != nullptr)
		SDL_DestroyTexture(this->_texture);
}

void Object::set_position(float x, float y, float z)
{
	this->_x = x;
	this->_y = y;
	this->_z = z;
}

void Object::set_size(float width, float height)
{
	this->_width = width;
	this->_height = height;
}

void Object::set_rotation(double rotation)
{
	this->_rotation = rotation;
}

void Object::set_texture(SDL_Surface* surface)
{
	if (!surface)
		return;
	if (this->_texture)
		SDL_DestroyTexture(this->_texture);
	this->_surface = surface;
	this->_width = this->_surface->w / 4;
	this->_height = this->_surface->h / 4;
	this->_texture = SDL_CreateTextureFromSurface(this->_game->get_renderer(), this->_surface);
}

void Object::set_texture(const std::string &filename, ResourceLoader* resourceLoader)
{
	if (!resourceLoader)
		return;
	set_texture(resourceLoader->get_texture(filename));
}

void Object::draw()
{
	SDL_FRect	rect;

	if (!this->_game)
		return;
	rect.x = this->_x - this->_game->camera.x - this->_width / 2 + this->_game->get_width() / 2;
	rect.y = this->_y - this->_game->camera.y - this->_height / 2 + this->_game->get_height() / 2;
	rect.w = this->_width;
	rect.h = this->_height;
	if (this->_rotation != 0 || this->_flip)
		SDL_RenderTextureRotated(this->_game->get_renderer(), _texture, nullptr, &rect, this->_rotation, nullptr, this->_flip);
	else
		SDL_RenderTexture(this->_game->get_renderer(), _texture, nullptr, &rect);
}
