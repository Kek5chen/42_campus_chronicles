#include "game.hpp"

Game::Game(): Window("42 Campus Chronicles", 800, 600){}

void Game::loop() {
	while (!this->isClosed()) {
		this->prepareScene();
		this->pollEvents();
		this->drawScene();
		this->presentScene();
		// SDL_Delay(DELAY);
	}
}