#pragma once

#include <string>
#include <vector>
#include "includes.hpp"
#include "resources.hpp"
#include "engine/base_objects.hpp"

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
	Vector2				_size;
	double				_rotation = 0;
	SDL_RendererFlip	_flip = SDL_FLIP_NONE;
	Game*				_game = nullptr;

private:
	SDL_Surface*		_surface = nullptr;
	SDL_Texture*		_texture = nullptr;

};

class Object3D : public Object {
public:
	explicit Object3D(Game *game);
	~Object3D() override = default;

	virtual void	set_size(Vector3 size);
	virtual void	set_size(float x, float y, float z);
	virtual void	set_rotation(Vector3 rotation);
	virtual void	set_rotation(float pitch, float yaw, float roll);

	void 	add_triangle(Triangle3 triangle);
	void 	update() override;
	void	draw() override;

protected:
	Vector3	_size;
	Vector3	_rotation;
	Game*	_game = nullptr;

	std::vector<Triangle3>	_triangles;

};
