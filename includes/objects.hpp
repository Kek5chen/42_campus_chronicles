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

	virtual void	set_position(int x, int y, int z);
	virtual void	set_size(int width, int height);
	virtual void	set_rotation(double rotation);
	virtual void	set_texture(SDL_Surface *texture);
	virtual void	set_texture(std::string filename, ResourceLoader *resource_loader);

	virtual void	draw(Window *window);
private:
	int 		_x = 0;
	int 		_y = 0;
	int			_z = 0;
	int			_width = 0;
	int			_height = 0;
	double		_rotation = 0;
	SDL_Surface	*_texture = nullptr;
};
