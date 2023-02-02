#include <fstream>
#include "resources.hpp"
#include "SDL_image.h"

ResourceLoader::~ResourceLoader()
{
	for (auto it = _resource_definitions.begin(); it != _resource_definitions.end(); ++it)
		unload_resource_definitions(it->first);
}

/*
 * .42CC Resource Format will be defined like the following:
 * [DataSize:8] 0x00 [PathName:-] 0x00 [Data:-] 0x00 ....
 */
void ResourceLoader::load_resource_definitions(const std::string &package_filename)
{
	std::ifstream	infile(package_filename, std::ios::binary);
	ResourceDefinition	*def;

	if(!infile.is_open())
		return;
	if (_resource_definitions.find(package_filename) != _resource_definitions.end())
		unload_resource_definitions(package_filename);
	while (infile.good()) {
		def = new ResourceDefinition();
		infile.read((char*)&def->data_size, 8);
		infile.seekg(1, std::ios::cur);
		std::getline(infile, def->path, '\0');
		def->data_offset = ((long long) infile.tellg());
		this->_resource_definitions[package_filename].push_back(def);
		infile.seekg(def->data_size, std::ios::cur);
		infile.seekg(1, std::ios::cur);
	}
	infile.close();
}

void ResourceLoader::unload_resource_definitions(const std::string &package_filename)
{
	if (_resource_definitions.find(package_filename) != _resource_definitions.end()) {
		for (auto it = _resource_definitions[package_filename].begin(); it != _resource_definitions[package_filename].end(); ++it)
			delete *it;
		_resource_definitions.erase(package_filename);
	}
}

SDL_Surface *ResourceLoader::get_texture(const std::string &filename)
{
	SDL_Surface	*surface;
	std::ifstream	infile;
	std::vector<char>	data;
	ResourceDefinition	*def;

	for (auto it = _resource_definitions.begin(); it != _resource_definitions.end(); ++it) {
		for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2) {
			if ((*it2)->path != filename)
				continue;
			def = *it2;
			infile.open(it->first, std::ios::binary);
			if (!infile.is_open())
				return nullptr;
			infile.seekg(def->data_offset, std::ios::beg);
			data.resize(def->data_size);
			infile.read(data.data(), def->data_size);
			infile.close();
			surface = IMG_Load_RW(SDL_RWFromMem(data.data(), (int) def->data_size), 1);
			return surface;
		}
	}
	return nullptr;
}
