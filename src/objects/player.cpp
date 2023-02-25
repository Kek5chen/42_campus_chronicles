#include "objects/player.hpp"
#include "game.hpp"

Player::Player() {
	this->_x = 100;
	this->_y = 100;
	this->_z = 0;
	this->_width = 300;
	this->_height = 200;
	this->_rotation = 0;
	this->_texture = g_resource_loader->get_texture("assets/player.png");
}
Player::~Player() = default;

void Player::draw(Game *game) {
	if (game->is_key_pressed(SDL_SCANCODE_A)) {
		this->_x -= 10;
		this->_flip = SDL_FLIP_NONE;
	}
	if (game->is_key_pressed(SDL_SCANCODE_D)) {
		this->_x += 10;
		this->_flip = SDL_FLIP_HORIZONTAL;
	}
	if (game->is_key_pressed(SDL_SCANCODE_W))
		this->_y -= 10;
	if (game->is_key_pressed(SDL_SCANCODE_S))
		this->_y += 10;
	game->camera.x = this->_x;
	game->camera.y = this->_y;
	Object::draw(game);
}