#include <numeric>
#include <algorithm>
#include <functional>
#include <complex>
#include <cassert>

template <typename T, int V>
requires std::is_arithmetic_v<T>
Vector<T, V>::Vector() {
	static_assert(V > 0);
}

template <typename T, int V>
requires std::is_arithmetic_v<T>
Vector<T, V>::Vector(std::initializer_list<T> list) {
	static_assert(V > 0, "Vector dimension must be greater than zero.");
	if (list.size() > V)
		throw std::out_of_range("Initializer list has wrong size");
	std::copy(list.begin(), list.end(), data);
}

template <typename T, int V>
requires std::is_arithmetic_v<T>
template <int V2>
Vector<T, V>::Vector(const Vector<T, V2>& other) {
	static_assert(V > 0, "Vector dimension must be greater than zero.");
	if constexpr (V >= V2) {
		std::copy(other.data, other.data + V2, data);
		std::fill(data + V2, data + V, 0.0f);
	} else
		std::copy(other.data, other.data + V, data);
}

template <typename T, int V>
requires std::is_arithmetic_v<T>
Vector<T, V>::Vector(const Vector<T, V - 1>& other, T value) {
	static_assert(V >= 2, "Vector dimension must be at least 2.");
	std::copy(other.data, other.data + (V - 1), data);
	data[V - 1] = value;
}

template <typename T, int V>
requires std::is_arithmetic_v<T>
template <int V2>
Vector<T, V> Vector<T, V>::operator+(const Vector<T, V2>& other) const {
	Vector<T, V> result;
	std::transform(data, data + std::min(V, V2), other.data, result.data, std::plus());
	return result;
}

template <typename T, int V>
requires std::is_arithmetic_v<T>
template <int V2>
Vector<T, V> Vector<T, V>::operator-(const Vector<T, V2>& other) const {
	Vector<T, V> result;
	std::transform(data, data + std::min(V, V2), other.data, result.data, std::minus());
	return result;
}

template <typename T, int V>
requires std::is_arithmetic_v<T>
template <int V2>
Vector<T, V> Vector<T, V>::operator*(const Vector<T, V2>& other) const {
	Vector<T, V> result;
	std::transform(data, data + std::min(V, V2), other.data, result.data, std::multiplies());
	return result;
}

template <typename T, int V>
requires std::is_arithmetic_v<T>
template <int V2>
Vector<T, V> Vector<T, V>::operator/(const Vector<T, V2>& other) const {
	Vector<T, V> result;
	std::transform(data, data + std::min(V, V2), other.data, result.data, std::divides());
	return result;
}

template <typename T, int V>
requires std::is_arithmetic_v<T>
Vector<T, V> Vector<T, V>::operator+(T value) const {
	Vector<T, V> result;
	std::transform(data, data + V, result.data,
		[value](T elem){ return elem + value; });
	return result;
}
template <typename T, int V>
requires std::is_arithmetic_v<T>
Vector<T, V> Vector<T, V>::operator-(T value) const {
	Vector<T, V> result;
	std::transform(data, data + V, result.data,
				   [value](T elem){ return elem - value; });
	return result;
}

template <typename T, int V>
requires std::is_arithmetic_v<T>
Vector<T, V> Vector<T, V>::operator*(T scalar) const {
	Vector<T, V> result;
	std::transform(data, data + V, result.data,
				   [scalar](T elem){ return elem * scalar; });
	return result;
}

template <typename T, int V>
requires std::is_arithmetic_v<T>
Vector<T, V> Vector<T, V>::operator/(T scalar) const {
	Vector<T, V> result;
	std::transform(data, data + V, result.data,
				   [scalar](T elem){ return elem / scalar; });
	return result;
}

template <typename T, int V>
requires std::is_arithmetic_v<T>
T& Vector<T, V>::operator[](int index) {
	return this->data[index];
}

template <typename T, int V>
requires std::is_arithmetic_v<T>
const T& Vector<T, V>::operator[](int index) const {
	return this->data[index];
}

template <typename T, int V>
requires std::is_arithmetic_v<T>
template <int V2>
void Vector<T, V>::operator+=(const Vector<T, V2>& other) {
	std::transform(data, data + std::min(V, V2), other.data, data, std::plus());
}

template <typename T, int V>
requires std::is_arithmetic_v<T>
template <int V2>
void Vector<T, V>::operator-=(const Vector<T, V2>& other) {
	std::transform(data, data + std::min(V, V2), other.data, data, std::minus());
}

template <typename T, int V>
requires std::is_arithmetic_v<T>
template <int V2>
void Vector<T, V>::operator*=(const Vector<T, V2>& other) {
	std::transform(data, data + std::min(V, V2), other.data, data, std::multiplies());
}

template <typename T, int V>
requires std::is_arithmetic_v<T>
template <int V2>
void Vector<T, V>::operator/=(const Vector<T, V2>& other) {
	std::transform(data, data + std::min(V, V2), other.data, data, std::divides());
}

template <typename T, int V>
requires std::is_arithmetic_v<T>
void Vector<T, V>::operator*=(T scalar) {
	std::transform(data, data + V, data,
		[scalar](T x) { return x * scalar; });
}

template <typename T, int V>
requires std::is_arithmetic_v<T>
void Vector<T, V>::operator/=(T scalar) {
	std::transform(data, data + V, data,
				   [scalar](T x) { return x / scalar; });
}

template <typename T, int V>
requires std::is_arithmetic_v<T>
T Vector<T, V>::sum() const {
	return std::accumulate(this->data, this->data + V, 0.0f);
}

template <typename T, int V>
requires std::is_arithmetic_v<T>
T Vector<T, V>::magnitude() const {
	T squaredSum = std::inner_product(data, data + V, data, 0.0f);
	return std::sqrt(squaredSum);
}

template <typename T, int V>
requires std::is_arithmetic_v<T>
Vector<T, V> Vector<T, V>::normalize() const {
	Vector<T, V> result{};
	T mag = this->magnitude();
	std::transform(data, data + V, result.data, [mag](T value)
		{ return value / mag; });
	return result;
}

template <typename T, int V>
requires std::is_arithmetic_v<T>
T Vector<T, V>::distance(const Vector<T, V>& other) const {
	Vector<T, V> deltaVec;
	std::transform(other.data, other.data + V, this->data, deltaVec.data, std::minus());
	return std::sqrt(std::inner_product(deltaVec.data, deltaVec.data + V, 0.0f, std::plus(),
		[](T x, T y) { return y * y; }));
}
