#pragma once

#include <initializer_list>
#include <type_traits>

template <int V>
struct Vector {
	Vector();
	Vector(std::initializer_list<float> list);
	template<int V2>
	Vector(const Vector<V2>& other);
	Vector(const Vector<V-1>& other, float value);

	template <int V2>
	Vector<V> 		operator+(const Vector<V2>& other) const;
	template <int V2>
	Vector<V> 		operator-(const Vector<V2>& other) const;
	template <int V2>
	Vector<V> 		operator*(const Vector<V2>& other) const;
	template <int V2>
	Vector<V> 		operator/(const Vector<V2>& other) const;
	Vector<V>		operator+(float value) const;
	Vector<V>		operator-(float value) const;
    Vector<V>		operator*(float scalar) const;
    Vector<V>		operator/(float scalar) const;
	float&			operator[](int index);
	const float&	operator[](int index) const;
	template <int V2>
    void            operator+=(const Vector<V2>& other);
	template <int V2>
    void            operator-=(const Vector<V2>& other);
	template <int V2>
    void            operator*=(const Vector<V2>& other);
	template <int V2>
    void            operator/=(const Vector<V2>& other);
    void            operator*=(float scalar);
    void            operator/=(float scalar);

	[[nodiscard]] float		sum() const;
	[[nodiscard]] float		magnitude() const;
	[[nodiscard]] Vector	normalize() const;
	[[nodiscard]] float		distance(const Vector &other) const;

	union {
		float data[V] {0};
		struct {
			float x;
			std::enable_if_t<V >= 2, float> y;
			std::enable_if_t<V >= 2, float> z;
			std::enable_if_t<V >= 2, float> w;
		};
	};
};

using Vector2 = Vector<2>;
using Vector3 = Vector<3>;
using Vector4 = Vector<4>;

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

#include "base_objects_impl.inl"
