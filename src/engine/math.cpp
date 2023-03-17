#include <cmath>
#include "engine/math.hpp"

namespace math {
	float radians(float degrees) {
		return (float) (degrees * (M_PI / 180.0f));
	}

	float degrees(float radians) {
		return (float) (radians * (180.0f / M_PI));
	}

	float    aspect_ratio(float width, float height) {
		return width / height;
	}

	Matrix4  perspective(float fov, float aspect, float near, float far) {
		float f = 1.0f / std::tan(radians(fov) / 2.0f);
		float nf = 1.0f / (near - far);

		Matrix4 matrix = {
			{ f / aspect, 0, 0, 0 },
			{ 0, f, 0, 0 },
			{0, 0, (far + near) * nf, -1},
			{0, 0, (2 * far * near) * nf, 0}
		};

		return matrix;
	}

	Matrix4  orthographic(float left, float right, float bottom, float top, float near, float far) {
		float lr = 1.0f / (right - left);
		float bt = 1.0f / (top - bottom);
		float nf = 1.0f / (far - near);

		Matrix4 matrix = {
			{ -2.0f * lr, 0, 0, 0 },
			{ 0, -2.0f * bt, 0, 0 },
			{ 0, 0, 2.0f * nf, 0 },
			{ (left + right) * lr, (top + bottom) * bt, (far + near) * nf, 1 }
		};

		return matrix;
	}

	Matrix4  orthographic(float fov, float aspect, float near, float far) {
		float top = near * std::tan(radians(fov) / 2.0f);
		float right = top * aspect;

		return orthographic(-right, right, -top, top, near, far);
	}

	Matrix4  orthographic(float aspect, float near, float far) {
		float top = near * std::tan(radians(45.0f) / 2.0f);
		float right = top * aspect;

		return orthographic(-right, right, -top, top, near, far);
	}

	Vector3  point_to_screen(Vector3& point, Matrix4& view, Vector2 &screenSize) {
		Vector4 projectedPoint = view * Vector4(point, 1.0f);
		projectedPoint /= projectedPoint.w;

		Vector3 screenPoint;
		screenPoint.x = (projectedPoint.x * 0.5f + 0.5f) * screenSize.x;
		screenPoint.y = (1.0f - (projectedPoint.y * 0.5f + 0.5f)) * screenSize.y;
		screenPoint.z = projectedPoint.z;

		return screenPoint;
	}

	Matrix4  translate(Matrix4& matrix, Vector3& translation) {
		Matrix4 translationMatrix = {
			{ 1, 0, 0, translation.x },
			{ 0, 1, 0, translation.y },
			{ 0, 0, 1, translation.z },
			{ 0, 0, 0, 1 }
		};

		return matrix * translationMatrix;
	}

	Matrix4  rotate(Matrix4& matrix, float angle, Vector3 axis) {
		float r = radians(angle);
		float c = std::cos(r);
		float s = std::sin(r);
		float oc = 1.0f - c;

		Vector3 normalizedAxis = axis.normalize();

		Matrix4 rotationMatrix = {
			{ oc * normalizedAxis.x * normalizedAxis.x + c, oc * normalizedAxis.x * normalizedAxis.y - normalizedAxis.z * s, oc * normalizedAxis.x * normalizedAxis.z + normalizedAxis.y * s, 0 },
			{ oc * normalizedAxis.x * normalizedAxis.y + normalizedAxis.z * s, oc * normalizedAxis.y * normalizedAxis.y + c, oc * normalizedAxis.y * normalizedAxis.z - normalizedAxis.x * s, 0 },
			{ oc * normalizedAxis.x * normalizedAxis.z - normalizedAxis.y * s, oc * normalizedAxis.y * normalizedAxis.z + normalizedAxis.x * s, oc * normalizedAxis.z * normalizedAxis.z + c, 0 },
			{ 0, 0, 0, 1 }
		};

		return matrix * rotationMatrix;
	}

	Matrix4  scale(Matrix4& matrix, Vector3& scale) {
		Matrix4 scaleMatrix = {
			{ scale.x, 0, 0, 0 },
			{ 0, scale.y, 0, 0 },
			{ 0, 0, scale.z, 0 },
			{ 0, 0, 0, 1 }
		};

		return matrix * scaleMatrix;
	}
}