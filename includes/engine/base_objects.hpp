#pragma once

#include <initializer_list>
#include <type_traits>

template <typename T, int V>
requires std::is_arithmetic_v<T>
struct Vector {
	Vector();
	Vector(std::initializer_list<T> list);
	template<int V2>
	explicit Vector(const Vector<T, V2>& other);
	Vector(const Vector<T, V-1>& other, T value);

	template <int V2>
	Vector<T, V> 		operator+(const Vector<T, V2>& other) const;
	template <int V2>
	Vector<T, V> 		operator-(const Vector<T, V2>& other) const;
	template <int V2>
	Vector<T, V> 		operator*(const Vector<T, V2>& other) const;
	template <int V2>
	Vector<T, V> 		operator/(const Vector<T, V2>& other) const;
	Vector<T, V>		operator+(T value) const;
	Vector<T, V>		operator-(T value) const;
    Vector<T, V>		operator*(T scalar) const;
    Vector<T, V>		operator/(T scalar) const;
	T&			operator[](int index);
	const T&	operator[](int index) const;
	template <int V2>
    void            operator+=(const Vector<T, V2>& other);
	template <int V2>
    void            operator-=(const Vector<T, V2>& other);
	template <int V2>
    void            operator*=(const Vector<T, V2>& other);
	template <int V2>
    void            operator/=(const Vector<T, V2>& other);
    void            operator*=(T scalar);
    void            operator/=(T scalar);

	[[nodiscard]] T			sum() const;
	[[nodiscard]] T			magnitude() const;
	[[nodiscard]] Vector	normalize() const;
	[[nodiscard]] T			distance(const Vector &other) const;

	union {
		T data[V] {0};
		struct {
			T x;
			std::enable_if_t<V >= 2, T> y;
			std::enable_if_t<V >= 2, T> z; // TODO: Reimplement these x,y,z better so that a Vector2 doesn't have a z and w component. enable_if is really weird.
			std::enable_if_t<V >= 2, T> w;
		};
	};
};

using Vector2 = Vector<float, 2>;
using Vector3 = Vector<float, 3>;
using Vector4 = Vector<float, 4>;

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
