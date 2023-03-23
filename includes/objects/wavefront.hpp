#pragma once

#include "game.hpp"

class WaveFrontObject : public Object3D {
public:
	explicit WaveFrontObject(Game* game);
	~WaveFrontObject() override = default;

	void	load_obj(const std::vector<char>& data);
	void	load_obj(const std::weak_ptr<ResourceLoader>& resourceLoader, const std::string &filename);

	void	update() override;

private:
	std::vector<Vector3>	_vertices;
	std::vector<Vector3>	_normals;

};
