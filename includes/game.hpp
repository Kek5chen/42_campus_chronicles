#pragma once

#include "includes.hpp"
#include "window.hpp"
#include "resources.hpp"
#include "objects/objects.hpp"
#include "engine/base_objects.hpp"

extern	ResourceLoader	*g_resource_loader;

class Game : public Window {
public:
	Game();
	~Game();

	void	update_scene();
	void	draw_scene() override;
	void 	add_object(Object *object);
	void 	remove_object(Object *object);
	void	loop();

	Camera	camera;

private:
	static void	check_resource_loader();

	std::vector<Object*>		_objects;
};