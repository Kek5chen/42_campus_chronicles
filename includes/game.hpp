#pragma once

#include "includes.hpp"
#include "window.hpp"
#include "resources.hpp"

extern ResourceLoader *resource_loader;

class Game : public Window {

	public:
		Game();
		~Game() {};

		void loop();

	private:
		

};