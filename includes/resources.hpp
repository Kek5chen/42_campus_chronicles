#pragma once

#include <string>
#include <vector>
#include <map>
#include <memory>
#include "includes.hpp"

struct ResourceDefinition {
	std::string	path;
	long long	data_size;
	long long 	data_offset;
};

class ResourceLoader {
public:
	ResourceLoader() = default;
	~ResourceLoader();

	void										load_resource_definitions(const std::string &package_filename);
	void 										unload_resource_definitions(const std::string &package_filename);
	[[nodiscard]] std::vector<char>				load_data(const std::string &filename) const;
	[[nodiscard]] std::shared_ptr<SDL_Surface>	load_texture(const std::string &filename) const;

private:
	std::map<std::string, std::vector<std::unique_ptr<ResourceDefinition>>>	_resource_definitions;
};
