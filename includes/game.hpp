#pragma once

#include "includes.hpp"
#include "window.hpp"
#include "resources.hpp"

class Game : public Window {

	public:
		Game();
		~Game() = default;;

		void draw_scene() override;
		void loop();

	private:
		static ResourceLoader *_resource_loader;

};