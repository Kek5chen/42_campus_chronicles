#include <algorithm>
#include <execution>
#include "objects/objects.hpp"
#include "game.hpp"
#include "engine/math.hpp"

Object3D::Object3D(Game *game) : _game(game) {}

void Object3D::set_size(Vector3 size) {
    this->_size = size;
}

void Object3D::set_size(float x, float y, float z) {
    this->_size = {x, y, z};
}

void Object3D::set_rotation(Vector3 rotation) {
    this->_rotation = rotation;
}

void Object3D::set_rotation(float pitch, float yaw, float roll) {
    this->_rotation = {pitch, yaw, roll};
}

void Object3D::add_triangle(Triangle3 triangle) {
    this->_triangles.push_back(triangle);
}

void Object3D::update() {}

void Object3D::draw() {
    if (!this->_game)
        return;
    auto renderer = this->_game->get_renderer();
	Vector2 screenSize = {(float)this->_game->get_width(), (float)this->_game->get_height()};

    float fov = math::radians(90);
    float aspect = (float)this->_game->get_width() / (float)this->_game->get_height();
    float near = 0.1f;
    float far = 1000.0f;
	Matrix4 modelMatrix(1.0f);
	Matrix4 modelTranslationMatrix(1.0f);
	modelMatrix = math::scale(modelMatrix, this->_size);
	modelMatrix = math::rotate(modelMatrix, this->_rotation.x, {1, 0, 0});
	modelMatrix = math::rotate(modelMatrix, this->_rotation.y, {0, 1, 0});
	modelMatrix = math::rotate(modelMatrix, this->_rotation.z, {0, 0, 1});
	modelTranslationMatrix = math::translate(modelTranslationMatrix, this->pos);
	modelTranslationMatrix = math::translate(modelTranslationMatrix, this->_game->camera.pos);
    Matrix4 projectionMatrix = math::perspective(fov, aspect, near, far);

	std::vector<Triangle3> projectedTriangles(_triangles.size());
	std::transform(std::execution::par, _triangles.begin(), _triangles.end(), projectedTriangles.begin(), [&](Triangle3& tri) {
		Triangle3 projectedTriangle = tri;
		for (auto& i: projectedTriangle.v) {
			Vector4 transformedVertex = modelMatrix * Vector4(i, 1.0f);
			transformedVertex = modelTranslationMatrix * transformedVertex;
			i = transformedVertex;
		}
		projectedTriangle.normals[0] = tri.normals[0];
		projectedTriangle.normals[1] = tri.normals[1];
		projectedTriangle.normals[2] = tri.normals[2];
		return projectedTriangle;
	});
	std::sort(std::execution::seq, projectedTriangles.begin(), projectedTriangles.end(), [](const Triangle3& a, const Triangle3& b) {
		return a.v->z < b.v->z;
	});

	for (Triangle3& tri : projectedTriangles) {
		for (auto& i: tri.v) {
			i = math::point_to_screen((Vector3 &) i, projectionMatrix, screenSize);
		}
		SDL_SetRenderDrawColor(renderer.lock().get(), 255, 255, 255, 255);
		Vector3 centroid{};
		for (auto normal : tri.normals)
			centroid += normal;
		centroid /= 3.0f;
		centroid = centroid.normalize();
		SDL_Vertex vertices[3];
		int gradient = (int)( std::abs(centroid.x) * 0.5 + (1.f - std::abs(centroid.y)) / 2 * 255);
		for (int i = 0; i < 3; ++i) {
			vertices[i].position.x = tri.v[i].x;
			vertices[i].position.y = tri.v[i].y;
			vertices[i].color.r = gradient;
			vertices[i].color.g = gradient;
			vertices[i].color.b = gradient;
			vertices[i].color.a = 255;
		}
		int indices[3] = {2, 1, 0};
		SDL_RenderGeometry(renderer.lock().get(), nullptr, vertices, 3, indices, 3);
    }
}
