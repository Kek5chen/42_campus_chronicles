#pragma once

#include "objects.hpp"

class Player : public Object {
public:
	Player();
	~Player();

	void draw(Game *game) override;
};
