#include "Util.h"


/* Constants */

const glm::mat4 Util::IDENTITY_MATRIX = glm::mat4 { 1.0f };


/* Functions */

float Util::repeat(float val, float _min, float _max) {
	float res = val;

	if (val < _min) {
		res = _max + std::fmodf(val, _max);
	} else if (val > _max) {
		res = _min - std::fmodf(val, _max);
	}

	return res;
}

glm::vec3 Util::repeat(glm::vec3 val, float _min, float _max) {
	val.x = Util::repeat(val.x, _min, _max);
	val.y = Util::repeat(val.y, _min, _max);
	val.z = Util::repeat(val.z, _min, _max);

	return val;
}

glm::vec2 Util::repeat(glm::vec2 val, float _min, float _max) {
	val.x = Util::repeat(val.x, _min, _max);
	val.y = Util::repeat(val.y, _min, _max);

	return val;
}


glm::vec4 Util::generateRGBAColorById(uint32_t colorId) {
	char *rgba = reinterpret_cast<char*>(&colorId);
	return glm::vec4 { rgba[0], rgba[1], rgba[2], rgba[3] };
}


std::string Util::getTextFromFile(const std::filesystem::path& filePath) {
	if (!std::filesystem::exists(filePath)) {
		throw std::exception { (filePath.string() + " isn't exists").c_str() };
	}

	if (std::filesystem::is_directory(filePath)) {
		throw std::exception { (filePath.string() + " isn't file").c_str() };
	}

	std::ifstream fh;

	fh.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	std::stringstream res {};

	try {
		fh.open(filePath);
		res << fh.rdbuf();
		fh.close();
	} catch (...) {
		throw;
	}

	return res.str();
}
