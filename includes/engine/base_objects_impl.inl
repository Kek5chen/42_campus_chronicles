#include <numeric>
#include <algorithm>
#include <functional>
#include <complex>
#include <cassert>

template <int V>
Vector<V>::Vector() {
	static_assert(V > 0);
}

template <int V>
Vector<V>::Vector(std::initializer_list<float> list) {
	static_assert(V > 0, "Vector dimension must be greater than zero.");
	if (list.size() > V)
		throw std::out_of_range("Initializer list has wrong size");
	std::copy(list.begin(), list.end(), data);
}

template <int V>
template <int V2>
Vector<V>::Vector(const Vector<V2>& other) {
	static_assert(V > 0, "Vector dimension must be greater than zero.");
	if constexpr (V >= V2) {
		std::copy(other.data, other.data + V2, data);
		std::fill(data + V2, data + V, 0.0f);
	} else
		std::copy(other.data, other.data + V, data);
}

template<int V>
Vector<V>::Vector(const Vector<V - 1>& other, float value) {
	static_assert(V >= 2, "Vector dimension must be at least 2.");
	std::copy(other.data, other.data + (V - 1), data);
	data[V - 1] = value;
}

template <int V>
template <int V2>
Vector<V> Vector<V>::operator+(const Vector<V2>& other) const {
	Vector<V> result;
	std::transform(data, data + std::min(V, V2), other.data, result.data, std::plus());
	return result;
}

template <int V>
template <int V2>
Vector<V> Vector<V>::operator-(const Vector<V2>& other) const {
	Vector<V> result;
	std::transform(data, data + std::min(V, V2), other.data, result.data, std::minus());
	return result;
}

template <int V>
template <int V2>
Vector<V> Vector<V>::operator*(const Vector<V2>& other) const {
	Vector<V> result;
	std::transform(data, data + std::min(V, V2), other.data, result.data, std::multiplies());
	return result;
}

template <int V>
template <int V2>
Vector<V> Vector<V>::operator/(const Vector<V2>& other) const {
	Vector<V> result;
	std::transform(data, data + std::min(V, V2), other.data, result.data, std::divides());
	return result;
}

template <int V>
Vector<V> Vector<V>::operator+(float value) const {
	Vector<V> result;
	std::transform(data, data + V, result.data,
		[value](float elem){ return elem + value; });
	return result;
}
template <int V>
Vector<V> Vector<V>::operator-(float value) const {
	Vector<V> result;
	std::transform(data, data + V, result.data,
				   [value](float elem){ return elem - value; });
	return result;
}

template <int V>
Vector<V> Vector<V>::operator*(float scalar) const {
	Vector<V> result;
	std::transform(data, data + V, result.data,
				   [scalar](float elem){ return elem * scalar; });
	return result;
}

template <int V>
Vector<V> Vector<V>::operator/(float scalar) const {
	Vector<V> result;
	std::transform(data, data + V, result.data,
				   [scalar](float elem){ return elem / scalar; });
	return result;
}

template <int V>
float& Vector<V>::operator[](int index) {
	return this->data[index];
}

template <int V>
const float& Vector<V>::operator[](int index) const {
	return this->data[index];
}

template <int V>
template <int V2>
void Vector<V>::operator+=(const Vector<V2>& other) {
	std::transform(data, data + std::min(V, V2), other.data, data, std::plus());
}

template <int V>
template <int V2>
void Vector<V>::operator-=(const Vector<V2>& other) {
	std::transform(data, data + std::min(V, V2), other.data, data, std::minus());
}

template <int V>
template <int V2>
void Vector<V>::operator*=(const Vector<V2>& other) {
	std::transform(data, data + std::min(V, V2), other.data, data, std::multiplies());
}

template <int V>
template <int V2>
void Vector<V>::operator/=(const Vector<V2>& other) {
	std::transform(data, data + std::min(V, V2), other.data, data, std::divides());
}

template <int V>
void Vector<V>::operator*=(float scalar) {
	std::transform(data, data + V, data,
		[scalar](float x) { return x * scalar; });
}

template <int V>
void Vector<V>::operator/=(float scalar) {
	std::transform(data, data + V, data,
				   [scalar](float x) { return x / scalar; });
}

template <int V>
float Vector<V>::sum() const {
	return std::accumulate(this->data, this->data + V, 0.0f);
}

template <int V>
float Vector<V>::magnitude() const {
	float squaredSum = std::inner_product(data, data + V, data, 0.0f);
	return std::sqrt(squaredSum);
}

template <int V>
Vector<V> Vector<V>::normalize() const {
	Vector<V> result{};
	float mag = this->magnitude();
	std::transform(data, data + V, result.data, [mag](float value)
		{ return value / mag; });
	return result;
}

template <int V>
float Vector<V>::distance(const Vector<V>& other) const {
	Vector<V> deltaVec;
	std::transform(other.data, other.data + V, this->data, deltaVec.data, std::minus());
	return std::sqrt(std::inner_product(deltaVec.data, deltaVec.data + V, 0.0f, std::plus(),
		[](float x, float y) { return y * y; }));
}
