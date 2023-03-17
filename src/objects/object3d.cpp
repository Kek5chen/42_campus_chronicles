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
    Matrix4 projectionMatrix = math::perspective(fov, aspect, near, far);

    for (const Triangle3& tri : _triangles) {
        Triangle3 projectedTriangle = tri;
        projectedTriangle.v[0] = math::point_to_screen(projectedTriangle.v[0], projectionMatrix, screenSize);
        projectedTriangle.v[1] = math::point_to_screen(projectedTriangle.v[1], projectionMatrix, screenSize);
        projectedTriangle.v[2] = math::point_to_screen(projectedTriangle.v[2], projectionMatrix, screenSize);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderLine(renderer, projectedTriangle.v[0].x, projectedTriangle.v[0].y, projectedTriangle.v[1].x, projectedTriangle.v[1].y);
        SDL_RenderLine(renderer, projectedTriangle.v[1].x, projectedTriangle.v[1].y, projectedTriangle.v[2].x, projectedTriangle.v[2].y);
        SDL_RenderLine(renderer, projectedTriangle.v[2].x, projectedTriangle.v[2].y, projectedTriangle.v[0].x, projectedTriangle.v[0].y);
    }
}
