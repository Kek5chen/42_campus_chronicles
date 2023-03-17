#pragma once

struct Matrix2 {
};

struct Vector2 {
	Vector2() = default;
	Vector2(float x, float y);

	Vector2 		operator+(const Vector2& other) const;
	Vector2 		operator-(const Vector2& other) const;
	Vector2 		operator*(const Vector2& other) const;
	Vector2 		operator/(const Vector2& other) const;
    Vector2         operator*(float scalar) const;
	float&			operator[](int index);
	const float&	operator[](int index) const;

	float x, y;
};

struct Vector3 {
	Vector3() = default;
	Vector3(float x, float y, float z);

	Vector3 		operator+(const Vector3& other) const;
	Vector3 		operator-(const Vector3& other) const;
	Vector3 		operator*(const Vector3& other) const;
	Vector3 		operator/(const Vector3& other) const;
    Vector3         operator*(float scalar) const;
	float&			operator[](int index);
	const float&	operator[](int index) const;

	float x, y, z;
};

struct Vector4 {
	Vector4() = default;
	Vector4(float x, float y, float z, float w);

	Vector4 		operator+(const Vector4& other) const;
	Vector4 		operator-(const Vector4& other) const;
	Vector4 		operator*(const Vector4& other) const;
	Vector4 		operator/(const Vector4& other) const;
    Vector4         operator*(float scalar) const;
	float&			operator[](int index);
	const float&	operator[](int index) const;

	float x, y, z, w;
};

struct Matrix4 {
	Matrix4();
	Matrix4(Vector4 v0, Vector4 v1, Vector4 v2, Vector4 v3);

	Vector4&		operator[](int index);
	const Vector4&	operator[](int index) const;
	Matrix4			operator*(const Matrix4& other) const;

	Vector4	v[4];
};

struct Object {
	virtual ~Object() = default;

	virtual void 	update() = 0;
	virtual void	draw() = 0;

	Vector3			pos;
};

class Camera {
public:
	Vector3	pos;
};

struct Triangle3 {
	Vector3	v[3];
};
