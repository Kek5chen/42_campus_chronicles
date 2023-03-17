#pragma once

#include "base_objects.hpp"

namespace math {
    float    degrees(float radians);
    float    radians(float degrees);
    float    aspect_ratio(float width, float height);
    Matrix4  orthographic(float left, float right, float bottom, float top, float near, float far);
    Matrix4  perspective(float fov, float aspect, float near, float far);
    Matrix4  orthographic(float fov, float aspect, float near, float far);
    Matrix4  orthographic(float aspect, float near, float far);
    Vector3  point_to_screen(Vector3& point, Matrix4& view, Vector2 &screenSize);
    Matrix4  translate(Matrix4& matrix, Vector3& translation);
    Matrix4  rotate(Matrix4& matrix, float angle, Vector3& axis);
    Matrix4  scale(Matrix4& matrix, Vector3& scale);
}
