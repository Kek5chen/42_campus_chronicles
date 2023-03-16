#pragma once

#include "objects.hpp"

class Player : public Sprite2D {
public:
	explicit Player(Game *game);
	~Player() override;

	void update() override;
};
