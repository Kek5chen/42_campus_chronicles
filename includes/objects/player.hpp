#pragma once

#include "objects.hpp"

class Player : public Object {
public:
	explicit Player(Game *game);
	~Player();

	void draw() override;
};
