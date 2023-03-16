#pragma once

struct Positional {
	float 				x = 0;
	float 				y = 0;
	float				z = 0;
};

struct Object : Positional {
	virtual ~Object() = default;

	virtual void 	update() = 0;
	virtual void	draw() = 0;
};

class Camera : public Positional { };
