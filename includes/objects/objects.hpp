#pragma once

#include <string>
#include <vector>
#include "includes.hpp"
#include "resources.hpp"
#include "engine.hpp"

class Game;

class Sprite2D : public Object {
	friend class Game;
public:
	explicit Sprite2D(Game *game);
	~Sprite2D() override;

	virtual void	set_size(float width, float height);
	virtual void	set_rotation(double rotation);
	virtual void	set_texture(SDL_Surface* surface);
	virtual void	set_texture(const std::string &filename, ResourceLoader* resourceLoader);

	void			draw() override;

protected:
	float				_width = 0;
	float				_height = 0;
	double				_rotation = 0;
	SDL_RendererFlip	_flip = SDL_FLIP_NONE;
	Game*				_game = nullptr;

private:
	SDL_Surface*		_surface = nullptr;
	SDL_Texture*		_texture = nullptr;

};

class Object3D : public Object{
public:
	Object3D();
	~Object3D();

	virtual void 	add_triangle();
	virtual void	set_size(float x, float y, float z);
	virtual void	set_rotation(float pitch, float yaw, float roll);

	virtual void	draw();

protected:
	float 	_sizeX = 1;
	float 	_sizeY = 1;
	float 	_sizeZ = 1;
	float	_pitch = 0;
	float	_yaw = 0;
	float	_roll = 0;

};
