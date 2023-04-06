
#include <algorithm>
#include <charconv>
#include "objects/wavefront.hpp"
#include "engine/exceptions/stackexception.hpp"

WaveFrontObject::WaveFrontObject(Game *game) : Object3D(game) { }

static std::vector<std::string_view>	parse_lines(const std::vector<char> &data) {
	std::vector<std::string_view> lines;
	std::string_view data_view(data.data(), data.size());

	size_t pos = 0;
	while (pos < data_view.size()) {
		size_t end = data_view.find_first_of('\n', pos);
		if (end == std::string_view::npos)
			end = data_view.size();

		lines.emplace_back(data_view.substr(pos, end - pos));
		pos = end + 1;
	}

	return lines;
}

static Vector3 parse_vertex(const std::string_view &line) {
	Vector3 vertex;
	auto start = line.data() + 2;  // Skip the "v " at the beginning

	for (auto* coord : {&vertex.x, &vertex.y, &vertex.z}) {
		start = std::find_if_not(start, line.data() + line.size(), [](unsigned char c) { return std::isspace(c); });
		auto [ptr, err] = std::from_chars(start, line.data() + line.size(), *coord);
		if (err != std::errc{}) {
			throw StackException("Failed to parse vertex");
		}
		start = ptr;
	}
	return vertex;
}

static Vector3 parse_normal(const std::string_view &line) {
	Vector3 normal;
	auto start = line.data() + 3;  // Skip the "vn " at the beginning

	for (auto* coord : {&normal.x, &normal.y, &normal.z}) {
		start = std::find_if_not(start, line.data() + line.size(), [](unsigned char c) { return std::isspace(c); });
		auto [ptr, err] = std::from_chars(start, line.data() + line.size(), *coord);
		if (err != std::errc{}) {
			throw StackException("Failed to parse vertex");
		}
		start = ptr;
	}
	return normal;
}

static std::vector<std::string_view> parse_tokens(const std::string_view &line) {
	std::vector<std::string_view> tokens;
	size_t pos = 0;
	while (pos < line.size()) {
		size_t end = line.find_first_of(' ', pos);
		if (end == std::string_view::npos)
			end = line.size();

		tokens.emplace_back(line.substr(pos, end - pos));
		pos = end + 1;
	}

	return tokens;
}

static Triangle3 parse_triangle(const std::string_view& line, const std::vector<Vector3> &vertices, const std::vector<Vector3> &normals) {
	Triangle3 triangle;
	std::vector<std::string_view> tokens = parse_tokens(line);
	for (size_t i = 0; i < 3; ++i) {
		std::vector<std::string_view> indices;
		size_t pos = 0;
		while (pos < tokens[i + 1].size()) {
			size_t end = tokens[i + 1].find_first_of('/', pos);
			if (end == std::string_view::npos)
				end = tokens[i + 1].size();

			indices.emplace_back(tokens[i + 1].substr(pos, end - pos));
			pos = end + 1;
		}

		while (indices.size() < 3)
			indices.emplace_back("0");

		triangle.v[i] = vertices[std::stoi(std::string(indices[0])) - 1];
		triangle.normals[i] = normals[std::stoi(std::string(indices[2])) - 1];
	}

	return triangle;
}

void WaveFrontObject::load_obj(const std::vector<char>& data) {
	if (data.empty())
		return;

	std::vector<std::string_view> lines = parse_lines(data);
	for (const auto &line : lines) {
		if (line.empty())
			continue;

		if (line.starts_with("v ")) {
			_vertices.emplace_back(parse_vertex(line));
		} else if (line.starts_with("vn ")) {
			_normals.emplace_back(parse_normal(line));
		} else if (line.starts_with("f ")) {
			add_triangle(parse_triangle(line, _vertices, _normals));
		}
	}
}

void WaveFrontObject::load_obj(const std::weak_ptr<ResourceLoader>& resourceLoader, const std::string &filename) {
	std::vector<char> data = resourceLoader.lock()->load_data(filename);

	load_obj(data);
}

void WaveFrontObject::update() {
	if (_game->is_key_pressed(SDL_SCANCODE_UP))
		this->_rotation.x += 1.f;
	if (_game->is_key_pressed(SDL_SCANCODE_DOWN))
		this->_rotation.x -= 1.f;
	if (_game->is_key_pressed(SDL_SCANCODE_LEFT))
		this->_rotation.y += 1.f;
	if (_game->is_key_pressed(SDL_SCANCODE_RIGHT))
		this->_rotation.y -= 1.f;
	if (_game->is_key_pressed(SDL_SCANCODE_T))
		this->_rotation.z += 1.f;
	if (_game->is_key_pressed(SDL_SCANCODE_R))
		this->_rotation.z -= 1.f;
}
