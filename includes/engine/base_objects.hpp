#pragma once

struct Vector2;
struct Vector3;
struct Vector4;
struct Matrix4;

struct Vector2 {
	Vector2() = default;
	Vector2(float x, float y);
	Vector2(Vector3 vec3);
	Vector2(Vector4 vec4);

	Vector2 		operator+(const Vector2& other) const;
	Vector2 		operator-(const Vector2& other) const;
	Vector2 		operator*(const Vector2& other) const;
	Vector2 		operator/(const Vector2& other) const;
    Vector2         operator*(float scalar) const;
    Vector2         operator/(float scalar) const;
	float&			operator[](int index);
	const float&	operator[](int index) const;
    void            operator+=(const Vector2& other);
    void            operator-=(const Vector2& other);
    void            operator*=(const Vector2& other);
    void            operator/=(const Vector2& other);
    void            operator*=(float scalar);
    void            operator/=(float scalar);

	float	magnitude() const;
	Vector2	normalize() const;
	float	distance(const Vector2 &other) const;

	float x = 0, y = 0;
};

struct Vector3 {
	Vector3() = default;
	Vector3(float x, float y, float z);
    Vector3(Vector2 vec2, float z);
	Vector3(Vector2 vec2);
	Vector3(Vector4 vec4);

	Vector3 		operator+(const Vector3& other) const;
	Vector3 		operator-(const Vector3& other) const;
	Vector3 		operator*(const Vector3& other) const;
	Vector3 		operator/(const Vector3& other) const;
    Vector3         operator*(float scalar) const;
    Vector3         operator/(float scalar) const;
	float&			operator[](int index);
	const float&	operator[](int index) const;
    void            operator+=(const Vector3& other);
    void            operator-=(const Vector3& other);
    void            operator*=(const Vector3& other);
    void            operator/=(const Vector3& other);
    void            operator*=(float scalar);
    void            operator/=(float scalar);
	Vector3			operator-() const;

    float           magnitude() const;
    Vector3         normalize() const;
	float 			distance(const Vector3& other) const;

	float x = 0, y = 0, z = 0;
};

struct Vector4 {
	Vector4() = default;
    Vector4(float x, float y, float z, float w);
    Vector4(Vector3 vec3, float w);
	Vector4(Vector2 vec2);
	Vector4(Vector3 vec3);

	Vector4 		operator+(const Vector4& other) const;
	Vector4 		operator-(const Vector4& other) const;
	Vector4 		operator*(const Vector4& other) const;
	Vector4 		operator/(const Vector4& other) const;
    Vector4         operator*(float scalar) const;
    Vector4         operator/(float scalar) const;
	float&			operator[](int index);
	const float&	operator[](int index) const;
    void            operator+=(const Vector4& other);
    void            operator-=(const Vector4& other);
    void            operator*=(const Vector4& other);
    void            operator/=(const Vector4& other);
    void            operator*=(float scalar);
    void            operator/=(float scalar);
	Vector4			operator-() const;
	Vector4 		operator*(const Matrix4& other) const;

	float x = 0, y = 0, z = 0, w = 0;
};

struct Matrix4 {
    Matrix4();
    explicit Matrix4(float diagonal);
	Matrix4(Vector4 v0, Vector4 v1, Vector4 v2, Vector4 v3);

	Vector4&		operator[](int index);
	const Vector4&	operator[](int index) const;
	Matrix4			operator*(const Matrix4& other) const;
    Vector4         operator*(const Vector4& other) const;

	float determinant();

	Vector4	v[4];

};

struct Object {
	virtual ~Object() = default;

	virtual void 	update() = 0;
	virtual void	draw() = 0;

	Vector3	pos {};
};

struct Triangle3 {
	Vector3	v[3];
	Vector3 normals[3] {};
};
