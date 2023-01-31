#include "game.hpp"

Game::Game(): Window(TITLE, WINDOW_WIDTH,WINDOW_HEIGHT){}

void Game::loop() {
	while (!this->isClosed()) {
		this->prepareScene();
		this->pollEvents();
		this->drawScene();
		this->presentScene();
	}
}