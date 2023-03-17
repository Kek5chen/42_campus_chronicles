#include <algorithm>
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
    SDL_Renderer* renderer = this->_game->get_renderer();
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

	std::vector<Triangle3> projectedTriangles;
    for (const Triangle3& tri : _triangles) {
		Triangle3 projectedTriangle = tri;
		for (auto& i: projectedTriangle.v) {
			Vector4 transformedVertex = modelMatrix * Vector4(i, 1.0f);
			transformedVertex = modelTranslationMatrix * transformedVertex;
			i = math::point_to_screen((Vector3 &) transformedVertex, projectionMatrix, screenSize);
		}
		projectedTriangle.normals[0] = tri.normals[0];
		projectedTriangle.normals[1] = tri.normals[1];
		projectedTriangle.normals[2] = tri.normals[2];
		projectedTriangles.push_back(projectedTriangle);
	}
	std::sort(projectedTriangles.begin(), projectedTriangles.end(), [](const Triangle3& a, const Triangle3& b) {
		return a.v->z > b.v->z;
	});

	for (const Triangle3& tri : projectedTriangles) {
		Vector2 min_coords = tri.v[0];
		Vector2 max_coords = tri.v[0];

		for (int i = 1; i < 3; ++i) {
			min_coords.x = std::min(min_coords.x, tri.v[i].x);
			min_coords.y = std::min(min_coords.y, tri.v[i].y);
			max_coords.x = std::max(max_coords.x, tri.v[i].x);
			max_coords.y = std::max(max_coords.y, tri.v[i].y);
		}

		Vector2 triangleScreenSize;
		triangleScreenSize.x = max_coords.x - min_coords.x;
		triangleScreenSize.y = max_coords.y - min_coords.y;
		if (triangleScreenSize.x < 1 || triangleScreenSize.y < 1)
			continue;

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		Vector3 centroid{};
		for (auto normal : tri.normals)
			centroid += normal;
		centroid /= 3.0f;
		centroid = centroid.normalize();
		SDL_Vertex vertices[3];
		int gradient = (int)((centroid.y < 0 ? 0 : centroid.y) * 150 + 105);
		for (int i = 0; i < 3; ++i) {
			vertices[i].position.x = tri.v[i].x;
			vertices[i].position.y = tri.v[i].y;
			vertices[i].color.r = gradient;
			vertices[i].color.g = gradient;
			vertices[i].color.b = gradient;
			vertices[i].color.a = 255;
		}
		int indices[3] = {2, 1, 0};
		SDL_RenderGeometry(renderer, 0, vertices, 3, indices, 3);
    }
}
