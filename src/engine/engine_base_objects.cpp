#include "engine/base_objects.hpp"

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
