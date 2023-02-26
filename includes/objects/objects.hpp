#pragma once

#include <string>
#include <vector>
#include "includes.hpp"
#include "resources.hpp"

class Game;

class Object {
	friend class Game;
public:
	explicit Object(Game *game);
	~Object();

	virtual void	set_position(float x, float y, float z);
	virtual void	set_size(float width, float height);
	virtual void	set_rotation(double rotation);
	virtual void	set_texture(SDL_Surface* surface);
	virtual void	set_texture(const std::string &filename, ResourceLoader* resourceLoader);

	virtual void	draw();
protected:
	float 				_x = 0;
	float 				_y = 0;
	float				_z = 0;
	float				_width = 0;
	float				_height = 0;
	double				_rotation = 0;
	SDL_RendererFlip	_flip = SDL_FLIP_NONE;
	Game*				_game = nullptr;
private:
	SDL_Surface*		_surface = nullptr;
	SDL_Texture*		_texture = nullptr;
};
