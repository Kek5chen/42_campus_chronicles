#pragma once

#include <string>
#include <vector>
#include <map>
#include "SDL_render.h"

struct ResourceDefinition {
	std::string	path;
	long long	data_size;
	long long 	data_offset;
};

class ResourceLoader {
public:
	ResourceLoader() {};
	~ResourceLoader();

	void		load_resource_definitions(const std::string &package_filename);
	void 		unload_resource_definitions(const std::string &package_filename);
	SDL_Surface *get_texture(const std::string &filename);
private:
	std::map<std::string, std::vector<ResourceDefinition*>>	_resource_definitions;
};