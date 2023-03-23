#include <cmath>
#include "engine/base_objects.hpp"


/*
 * Vector 2 Implementations
 */


Vector2::Vector2(float x, float y) : x(x), y(y) {}

Vector2::Vector2(Vector3 vec3) {
	this->x = vec3.x;
	this->y = vec3.y;
}

Vector2::Vector2(Vector4 vec4) {
	this->x = vec4.x;
	this->y = vec4.y;
}

Vector2 Vector2::operator+(const Vector2& other) const {
	return {this->x + other.x, this->y + other.y};
}

Vector2 Vector2::operator-(const Vector2& other) const {
	return {this->x- other.x, this->y - other.y};
}

Vector2 Vector2::operator*(const Vector2& other) const {
	return {this->x * other.x, this->x * other.x};
}

Vector2 Vector2::operator/(const Vector2& other) const {
	return {this->x / other.x, this->y / other.y};
}

Vector2 Vector2::operator*(float scalar) const {
    return {this->x * scalar, this->y * scalar};
}

Vector2 Vector2::operator/(float scalar) const {
    return {this->x / scalar, this->y / scalar};
}

float& Vector2::operator[](int index) {
    return (&x)[index];
}

const float& Vector2::operator[](int index) const {
    return (&x)[index];
}

void Vector2::operator+=(const Vector2 &other) {
    this->x += other.x;
    this->y += other.y;
}

void Vector2::operator-=(const Vector2 &other) {
    this->x -= other.x;
    this->y -= other.y;
}

void Vector2::operator*=(const Vector2 &other) {
    this->x *= other.x;
    this->y *= other.y;
}

void Vector2::operator/=(const Vector2 &other) {
    this->x /= other.x;
    this->y /= other.y;
}

void Vector2::operator*=(float scalar) {
    this->x *= scalar;
    this->y *= scalar;
}

void Vector2::operator/=(float scalar) {
    this->x /= scalar;
    this->y /= scalar;
}

float Vector2::magnitude() const {
	return std::sqrt(x * x + y * y);
}

Vector2 Vector2::normalize() const {
	float mag = magnitude();
	return {x / mag, y / mag};
}

float Vector2::distance(const Vector2 &other) const {
	float dx = this->x - other.x;
	float dy = this->y - other.y;
	return std::sqrt(dx * dx + dy * dy);
}


/*
 * Vector 3 Implementations
 */


Vector3::Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

Vector3::Vector3(Vector2 vec2, float z) {
    this->x = vec2.x;
    this->y = vec2.y;
    this->z = z;
}

Vector3::Vector3(Vector2 vec2) {
	this->x = vec2.x;
	this->y = vec2.y;
	this->z = 0.0f;
}

Vector3::Vector3(Vector4 vec4) {
	this->x = vec4.x;
	this->y = vec4.y;
	this->z = vec4.z;
}

Vector3 Vector3::operator+(const Vector3 &other) const {
	return {this->x + other.x, this->y + other.y, this->z + other.z};
}

Vector3 Vector3::operator-(const Vector3 &other) const {
	return {this->x - other.x, this->y - other.y, this->z - other.z};
}

Vector3 Vector3::operator*(const Vector3 &other) const {
	return {this->x * other.x, this->y * other.y, this->z * other.z};
}

Vector3 Vector3::operator/(const Vector3 &other) const {
	return {this->x / other.x, this->y / other.y, this->z / other.z};
}

Vector3 Vector3::operator*(float scalar) const {
    return {this->x * scalar, this->y * scalar, this->z * scalar};
}

Vector3 Vector3::operator/(float scalar) const {
    return {this->x / scalar, this->y / scalar, this->z / scalar};
}

float& Vector3::operator[](int index) {
    return (&x)[index];
}

const float& Vector3::operator[](int index) const {
    return (&x)[index];
}

void Vector3::operator+=(const Vector3 &other) {
    this->x += other.x;
    this->y += other.y;
    this->z += other.z;
}

void Vector3::operator-=(const Vector3 &other) {
    this->x -= other.x;
    this->y -= other.y;
    this->z -= other.z;
}

void Vector3::operator*=(const Vector3 &other) {
    this->x *= other.x;
    this->y *= other.y;
    this->z *= other.z;
}

void Vector3::operator/=(const Vector3 &other) {
    this->x /= other.x;
    this->y /= other.y;
    this->z /= other.z;
}

void Vector3::operator*=(float scalar) {
    this->x *= scalar;
    this->y *= scalar;
    this->z *= scalar;
}

void Vector3::operator/=(float scalar) {
    this->x /= scalar;
    this->y /= scalar;
    this->z /= scalar;
}

float Vector3::magnitude() const {
    return std::sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
}

Vector3 Vector3::normalize() const {
    float length = this->magnitude();
    return {this->x / length, this->y / length, this->z / length};
}

float Vector3::distance(const Vector3 &other) const {
	float dx = this->x - other.x;
	float dy = this->y - other.y;
	float dz = this->z - other.z;
	return std::sqrt(dx * dx + dy * dy + dz * dz);
}

Vector3 Vector3::operator-() const {
	return {-x, -y, -z};
}


/*
 * Vector 4 Implementations
 */


Vector4::Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

Vector4::Vector4(Vector3 vec3, float w) {
    this->x = vec3.x;
    this->y = vec3.y;
    this->z = vec3.z;
    this->w = w;
}

Vector4::Vector4(Vector2 vec2) {
	this->x = vec2.x;
	this->y = vec2.y;
	this->z = 0.0f;
	this->w = 0.0f;
}

Vector4::Vector4(Vector3 vec3) {
	this->x = vec3.x;
	this->y = vec3.y;
	this->z = vec3.z;
	this->w = 0.0f;
}

Vector4 Vector4::operator+(const Vector4 &other) const {
	return {this->x + other.x, this->y + other.y, this->z + other.z, this->w + other.w};
}

Vector4 Vector4::operator-(const Vector4 &other) const {
	return {this->x - other.x, this->y - other.y, this->z - other.z, this->w - other.w};
}

Vector4 Vector4::operator*(const Vector4 &other) const {
	return {this->x * other.x, this->y * other.y, this->z * other.z, this->w * other.w};
}

Vector4 Vector4::operator/(const Vector4 &other) const {
	return {this->x / other.x, this->y / other.y, this->z / other.z, this->w / other.w};
}

Vector4 Vector4::operator*(float scalar) const {
    return {this->x * scalar, this->y * scalar, this->z * scalar, this->w * scalar};
}

Vector4 Vector4::operator/(float scalar) const {
    return {this->x / scalar, this->y / scalar, this->z / scalar, this->w / scalar};
}

float& Vector4::operator[](int index) {
    return (&x)[index];
}

const float &Vector4::operator[](int index) const {
    return (&x)[index];
}

void Vector4::operator+=(const Vector4 &other) {
    this->x += other.x;
    this->y += other.y;
    this->z += other.z;
    this->w += other.w;
}

void Vector4::operator-=(const Vector4 &other) {
    this->x -= other.x;
    this->y -= other.y;
    this->z -= other.z;
    this->w -= other.w;
}

void Vector4::operator*=(const Vector4 &other) {
    this->x *= other.x;
    this->y *= other.y;
    this->z *= other.z;
    this->w *= other.w;
}

void Vector4::operator/=(const Vector4 &other) {
    this->x /= other.x;
    this->y /= other.y;
    this->z /= other.z;
    this->w /= other.w;
}

void Vector4::operator*=(float scalar) {
    this->x *= scalar;
    this->y *= scalar;
    this->z *= scalar;
    this->w *= scalar;
}

void Vector4::operator/=(float scalar) {
    this->x /= scalar;
    this->y /= scalar;
    this->z /= scalar;
    this->w /= scalar;
}

Vector4 Vector4::operator-() const {
	return {-x, -y, -z, -w};
}

Vector4 Vector4::operator*(const Matrix4 &other) const {
	Vector4 result;
	for (int i = 0; i < 4; i++) {
		result[i] = this->x * other[i][0] + this->y * other[i][1] + this->z * other[i][2] + this->w * other[i][3];
	}
	return result;
}

/*
 * Matrix 4 Implementations
 */


Matrix4::Matrix4() {
    for (auto& i : v) {
        for (int j = 0; j < 4; j++) {
            i[j] = 0;
        }
    }
}

Matrix4::Matrix4(float diagonal) {
    for (auto& i : v) {
        for (int j = 0; j < 4; j++) {
            i[j] = 0;
        }
    }
    v[0][0] = diagonal;
    v[1][1] = diagonal;
    v[2][2] = diagonal;
    v[3][3] = diagonal;
}

Matrix4::Matrix4(Vector4 v0, Vector4 v1, Vector4 v2, Vector4 v3) : v{v0, v1, v2, v3} {}


Vector4& Matrix4::operator[](int index) {
    return v[index];
}

const Vector4 &Matrix4::operator[](int index) const {
    return v[index];
}


Matrix4 Matrix4::operator*(const Matrix4 &other) const {
    Matrix4 result;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            result[i][j] = 0;
            for (int k = 0; k < 4; k++) {
                result[i][j] += v[i][k] * other[k][j];
            }
        }
    }
    return result;
}

Vector4 Matrix4::operator*(const Vector4 &other) const {
    Vector4 result;
    for (int i = 0; i < 4; i++) {
        result[i] = 0;
        for (int j = 0; j < 4; j++) {
            result[i] += v[i][j] * other[j];
        }
    }
    return result;
}

float Matrix4::determinant() {
	float result = 0;
	for (int i = 0; i < 4; i++) {
		result += v[0][i] * (v[1][(i + 1) % 4] * v[2][(i + 2) % 4] * v[3][(i + 3) % 4] - v[1][(i + 3) % 4] * v[2][(i + 2) % 4] * v[3][(i + 1) % 4]);
	}
	return result;
}
