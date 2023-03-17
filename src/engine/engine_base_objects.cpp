#include "engine/base_objects.hpp"


/*
 * Vector 2 Implementations
 */


Vector2::Vector2(float x, float y) : x(x), y(y) {}

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

float& Vector2::operator[](int index) {
    return (&x)[index];
}

const float& Vector2::operator[](int index) const {
    return (&x)[index];
}


/*
 * Vector 3 Implementations
 */


Vector3::Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

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

float& Vector3::operator[](int index) {
    return (&x)[index];
}

const float& Vector3::operator[](int index) const {
    return (&x)[index];
}


/*
 * Vector 4 Implementations
 */


Vector4::Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

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

float& Vector4::operator[](int index) {
    return (&x)[index];
}

const float &Vector4::operator[](int index) const {
    return (&x)[index];
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
