#pragma once

#include <string>
#include <vector>
#include "includes.hpp"
#include "resources.hpp"

class Game;

struct Object {
	virtual ~Object() = default;

	virtual void 	update() = 0;
	virtual void	draw() = 0;

	float 				x = 0;
	float 				y = 0;
	float				z = 0;
};

class Sprite2D : public Object {
	friend class Game;
public:
	explicit Sprite2D(Game *game);
	~Sprite2D();

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
