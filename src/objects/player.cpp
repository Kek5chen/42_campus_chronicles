#include "objects/player.hpp"
#include "game.hpp"

Player::Player(Game *game) : Sprite2D(game) {
	this->pos.x = 100;
	this->pos.y = 100;
	this->pos.z = 0;
	this->_size.x = 300;
	this->_size.y = 200;
	this->_rotation = 0;
	this->set_texture("assets/player.png", g_resource_loader);
}
Player::~Player() = default;

void Player::update() {
	if (this->_game->is_key_pressed(SDL_SCANCODE_A)) {
		this->pos.x -= 2;
		this->_flip = SDL_FLIP_NONE;
	}
	if (this->_game->is_key_pressed(SDL_SCANCODE_D)) {
		this->pos.x += 2;
		this->_flip = SDL_FLIP_HORIZONTAL;
	}
	if (this->_game->is_key_pressed(SDL_SCANCODE_W))
		this->pos.y -= 2;
	if (this->_game->is_key_pressed(SDL_SCANCODE_S))
		this->pos.y += 2;
	this->_game->camera.pos.x = this->pos.x;
	this->_game->camera.pos.y = this->pos.y;
}