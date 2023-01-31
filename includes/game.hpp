#pragma once

#include "includes.hpp"
#include "window.hpp"

using namespace std;

#define DELAY (1000 / 60)

class Game : public Window {

	public:
		Game();
		~Game(){};

		void loop();

	private:
		

};