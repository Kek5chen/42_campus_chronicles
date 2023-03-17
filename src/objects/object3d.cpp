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
	modelMatrix = math::translate(modelMatrix, this->pos);
	modelMatrix = math::rotate(modelMatrix, this->_rotation.x, {1, 0, 0});
	modelMatrix = math::rotate(modelMatrix, this->_rotation.y, {0, 1, 0});
	modelMatrix = math::rotate(modelMatrix, this->_rotation.z, {0, 0, 1});
	modelMatrix = math::scale(modelMatrix, this->_size);
    Matrix4 projectionMatrix = math::perspective(fov, aspect, near, far);
	Matrix4 worldProjection(1.0f);
	worldProjection = math::translate(worldProjection, this->_game->camera.pos);
	projectionMatrix = worldProjection * projectionMatrix;

    for (const Triangle3& tri : _triangles) {
        Triangle3 projectedTriangle = tri;
		for (auto & i : projectedTriangle.v) {
			Vector4 transformedVertex = modelMatrix * Vector4(i, 1.0f);
			i = math::point_to_screen((Vector3&)transformedVertex, projectionMatrix, screenSize);
		}

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderLine(renderer, projectedTriangle.v[0].x, projectedTriangle.v[0].y, projectedTriangle.v[1].x, projectedTriangle.v[1].y);
        SDL_RenderLine(renderer, projectedTriangle.v[1].x, projectedTriangle.v[1].y, projectedTriangle.v[2].x, projectedTriangle.v[2].y);
        SDL_RenderLine(renderer, projectedTriangle.v[2].x, projectedTriangle.v[2].y, projectedTriangle.v[0].x, projectedTriangle.v[0].y);
    }
}
