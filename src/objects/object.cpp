#include "objects.hpp"
#include "window.hpp"
#include "includes.hpp"
#include "game.hpp"

Object::Object() = default;

Object::~Object() {
	if (this->_texture != nullptr)
		SDL_DestroySurface(this->_texture);
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

void Object::set_texture(SDL_Surface* texture)
{
	this->_texture = texture;
}

void Object::set_texture(const std::string &filename, ResourceLoader* resourceLoader)
{
	this->_texture = resourceLoader->get_texture(filename);
}

void Object::draw(Game *game)
{
	SDL_Texture	*tex;
	SDL_FRect	rect;
	rect.x = this->_x;
	rect.y = this->_y;
	rect.w = this->_width;
	rect.h = this->_height;
	tex = SDL_CreateTextureFromSurface(game->get_renderer(), this->_texture);
	if (this->_rotation != 0)
		SDL_RenderTextureRotated(game->get_renderer(), tex, nullptr, &rect, this->_rotation, nullptr, SDL_FLIP_NONE);
	else
		SDL_RenderTexture(game->get_renderer(), tex, nullptr, &rect);
	SDL_DestroyTexture(tex);
}
