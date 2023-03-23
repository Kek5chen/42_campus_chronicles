#include <functional>
#include <utility>
#include "objects/objects.hpp"
#include "window.hpp"
#include "includes.hpp"
#include "game.hpp"

Sprite2D::Sprite2D(Game* game) : _game(game) {}

Sprite2D::~Sprite2D() = default;

void Sprite2D::set_size(float width, float height)
{
	this->_size = {width, height};
}

void Sprite2D::set_rotation(double rotation)
{
	this->_rotation = rotation;
}

void Sprite2D::set_texture(const std::shared_ptr<SDL_Surface>& surface)
{
	if (!surface)
		return;
	this->_surface = surface;
	this->_size.x = static_cast<float>(this->_surface->w) / 4;
	this->_size.y = static_cast<float>(this->_surface->h) / 4;
	std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> texture(
			SDL_CreateTextureFromSurface(this->_game->get_renderer().lock().get(), this->_surface.get()), SDL_DestroyTexture);
	this->_texture = std::move(texture);

}

void Sprite2D::set_texture(const std::string& filename, const std::weak_ptr<ResourceLoader>& resourceLoader)
{
	if (!resourceLoader.lock())
		return;
	this->set_texture(resourceLoader.lock()->load_texture(filename));
}

void Sprite2D::draw()
{
	SDL_FRect	rect;

	if (!this->_game)
		return;
	rect.x = this->pos.x - this->_game->camera.pos.x - this->_size.x / 2 + (float)this->_game->get_width() / 2;
	rect.y = this->pos.y - this->_game->camera.pos.y - this->_size.y / 2 + (float)this->_game->get_height() / 2;
	rect.w = this->_size.x;
	rect.h = this->_size.y;
	if (this->_rotation != 0 || this->_flip)
		SDL_RenderTextureRotated(this->_game->get_renderer().lock().get(), _texture.get(), nullptr,
								 &rect, this->_rotation, nullptr, this->_flip);
	else
		SDL_RenderTexture(this->_game->get_renderer().lock().get(), _texture.get(), nullptr, &rect);
}
