#pragma once

#include <string>
#include <vector>
#include "includes.hpp"
#include "resources.hpp"
#include "window.hpp"

class Object {
	friend class Game;
public:
	Object();
	~Object();

	virtual void	set_position(float x, float y, float z);
	virtual void	set_size(float width, float height);
	virtual void	set_rotation(double rotation);
	virtual void	set_texture(SDL_Surface *texture);
	virtual void	set_texture(const std::string &filename, ResourceLoader *resource_loader);

	virtual void	draw(Window *window);
protected:
	float 		_x = 0;
	float 		_y = 0;
	float		_z = 0;
	float		_width = 0;
	float		_height = 0;
	double		_rotation = 0;
	SDL_Surface	*_texture = nullptr;
};
