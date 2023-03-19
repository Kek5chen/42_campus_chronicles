#include <fstream>
#include "resources.hpp"
#include "engine/exceptions/stackexception.hpp"

ResourceLoader::~ResourceLoader()
{
	for (auto& _resource_definition : _resource_definitions)
		unload_resource_definitions(_resource_definition.first);
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
		throw StackException("Could not open resource package: " + package_filename);
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
		for (auto& it : _resource_definitions[package_filename])
			delete it;
		_resource_definitions.erase(package_filename);
	}
}

std::vector<char> ResourceLoader::load_data(const std::string &filename) const {
	std::ifstream		infile;
	std::vector<char>	data;
	ResourceDefinition	*def;

	for (const auto& _resource_definition : _resource_definitions) {
		for (auto it2 = _resource_definition.second.begin(); it2 != _resource_definition.second.end(); ++it2) {
			if ((*it2)->path != filename)
				continue;
			def = *it2;
			infile.open(_resource_definition.first, std::ios::binary);
			if (!infile.is_open())
				throw StackException("Could not open resource package: " + _resource_definition.first);
			infile.seekg(def->data_offset, std::ios::beg);
			data.resize(def->data_size);
			infile.read(data.data(), def->data_size);
			infile.close();
		}
	}
	return data;
}

SDL_Surface *ResourceLoader::load_texture(const std::string &filename) const
{
	SDL_Surface	*surface;

	std::vector<char>	data = load_data(filename);
	if (data.empty())
		return nullptr;
	surface = IMG_Load_RW(SDL_RWFromMem(data.data(), (int) data.size()), 1);
	return surface;
}
