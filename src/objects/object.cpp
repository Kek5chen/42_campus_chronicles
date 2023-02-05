#include "objects.hpp"
#include "window.hpp"
#include "includes.hpp"

Object::Object() = default;

Object::~Object() {
	if (this->_texture != nullptr)
		SDL_DestroySurface(this->_texture);
}

void Object::set_position(int x, int y, int z)
{
	this->_x = x;
	this->_y = y;
	this->_z = z;
}

void Object::set_size(int width, int height)
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

void Object::set_texture(std::string &filename, ResourceLoader* resource_loader)
{
	this->_texture = resource_loader->get_texture(filename);
}

void Object::draw(Window *window)
{
	SDL_Texture	*tex;
	SDL_FRect	rect;
	rect.x = (float) this->_x;
	rect.y = (float) this->_y;
	rect.w = (float) this->_width;
	rect.h = (float) this->_height;
	tex = SDL_CreateTextureFromSurface(window->get_renderer(), this->_texture);
	if (this->_rotation != 0)
		SDL_RenderTextureRotated(window->get_renderer(), tex, nullptr, &rect, this->_rotation, nullptr, SDL_FLIP_NONE);
	else
		SDL_RenderTexture(window->get_renderer(), tex, nullptr, &rect);
}
