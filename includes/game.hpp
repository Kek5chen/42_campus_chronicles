#pragma once

#include "includes.hpp"
#include "window.hpp"
#include "resources.hpp"
#include "objects/objects.hpp"
#include "engine/base_objects.hpp"

#define GLOBAL_EXCEPT_TRY try {
#define GLOBAL_EXCEPT_CATCH } catch (const std::exception& e) { \
		std::stringstream ss; \
		ss << "--- An exception caused the program to crash --- \n\nWhat happened?\n" << e.what() << "\n\n"; \
		if (dynamic_cast<const StackException*>(&e) != nullptr) { \
			ss << "------------------------------------------------\n\n"; \
			ss << "Stack trace:" << '\n'; \
			ss << dynamic_cast<const StackException*>(&e)->get_stack_trace() << std::endl; \
		} \
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", ss.str().c_str(), nullptr); \
		return 1; \
	}

extern	ResourceLoader	*g_resource_loader;

class Camera {
public:
	Vector3	pos {};
};

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

	void	update_camera();

	std::vector<Object*>		_objects;
};
