#pragma once

struct Vector2 {
	float x = 0;
	float y = 0;
};

struct Vector3 {
	float 				x = 0;
	float 				y = 0;
	float				z = 0;
};

struct Object {
	virtual ~Object() = default;

	virtual void 	update() = 0;
	virtual void	draw() = 0;

	Vector3			pos;
};

class Camera {
public:
	Vector3 pos;
};

struct Triangle3 {
	Vector3 a;
	Vector3 b;
	Vector3 c;
};
