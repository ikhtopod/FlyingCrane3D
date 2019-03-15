#include "Util.h"


/* Constants */

const glm::mat4 Util::IDENTITY_MATRIX = glm::mat4 { 1.0f };
const std::string Util::SHADER_DIRECTORY = std::string { R"(..\resources\shaders)" };


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

