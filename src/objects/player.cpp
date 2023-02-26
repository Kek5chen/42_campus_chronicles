#include "objects/player.hpp"
#include "game.hpp"

Player::Player(Game *game) : Object(game) {
	this->_x = 100;
	this->_y = 100;
	this->_z = 0;
	this->_width = 300;
	this->_height = 200;
	this->_rotation = 0;
	this->set_texture("assets/player.png", g_resource_loader);
}
Player::~Player() = default;

void Player::draw() {
	if (this->_game->is_key_pressed(SDL_SCANCODE_A)) {
		this->_x -= 2;
		this->_flip = SDL_FLIP_NONE;
	}
	if (this->_game->is_key_pressed(SDL_SCANCODE_D)) {
		this->_x += 2;
		this->_flip = SDL_FLIP_HORIZONTAL;
	}
	if (this->_game->is_key_pressed(SDL_SCANCODE_W))
		this->_y -= 2;
	if (this->_game->is_key_pressed(SDL_SCANCODE_S))
		this->_y += 2;
	this->_game->camera.x = this->_x;
	this->_game->camera.y = this->_y;
	Object::draw();
}