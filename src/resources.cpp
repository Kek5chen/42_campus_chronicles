#include <fstream>
#include "resources.hpp"
#include "engine/exceptions/stackexception.hpp"

/*
 * .42CC Resource Format will be defined like the following:
 * [DataSize:8] 0x00 [PathName:-] 0x00 [Data:-] 0x00 ....
 */
void ResourceLoader::load_resource_definitions(const std::string &package_filename)
{
	std::ifstream						infile(package_filename, std::ios::binary);
	std::unique_ptr<ResourceDefinition>	def;

	if(!infile.is_open())
		throw StackException("Could not open resource package: " + package_filename);
	if (_resource_definitions.find(package_filename) != _resource_definitions.end())
		unload_resource_definitions(package_filename);
	while (infile.good()) {
		def = std::make_unique<ResourceDefinition>();
		infile.read((char*)&def->data_size, 8);
		if (def->data_size <= 0)
			break;
		infile.seekg(1, std::ios::cur);
		std::getline(infile, def->path, '\0');
		def->data_offset = ((long long) infile.tellg());
		infile.seekg(def->data_size, std::ios::cur);
		infile.seekg(1, std::ios::cur);
		this->_resource_definitions[package_filename].push_back(std::move(def));
	}
	infile.close();
}

void ResourceLoader::unload_resource_definitions(const std::string &package_filename)
{
	_resource_definitions.erase(package_filename);
}

std::vector<char> ResourceLoader::load_data(const std::string &filename) const {
	std::ifstream		infile;
	std::vector<char>	data;
	ResourceDefinition	*def;

	for (const auto& _resource_definition : _resource_definitions) {
		for (auto it2 = _resource_definition.second.begin(); it2 != _resource_definition.second.end(); ++it2) {
			if ((*it2)->path != filename)
				continue;
			def = it2->get();
			infile.open(_resource_definition.first, std::ios::binary);
			if (!infile.is_open())
				throw StackException("Could not open resource package: " + _resource_definition.first);
			infile.seekg(def->data_offset, std::ios::beg);
			if (def->data_size <= 0)
				break;
			data.resize((size_t)def->data_size);
			infile.read(data.data(), def->data_size);
			infile.close();
		}
	}
	return data;
}

SurfacePtr ResourceLoader::load_texture(const std::string& filename) const
{
	std::vector<char> data = load_data(filename);
	if (data.empty())
		return nullptr;

	SDL_RWops* rw = SDL_RWFromMem(data.data(), static_cast<int>(data.size()));
	SDL_Surface* surface = IMG_Load_RW(rw, 1);
	if (!surface)
		return nullptr;

	return {surface, [](SDL_Surface* p) { SDL_DestroySurface(p); }};
}
