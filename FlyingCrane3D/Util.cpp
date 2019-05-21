#include "Util.h"


/* Constants */

const glm::mat4 Util::IDENTITY_MATRIX = glm::mat4 { 1.0f };


/* OpenGL Functions */

void Util::clearColor() {
	Util::clearColor(glm::vec4 {});
}

void Util::clearColor(const glm::vec4& color) {
	Util::clearColor(glm::value_ptr(color));
}

void Util::clearColor(const GLfloat color[4]) {
	glClearColor(color[0], color[1], color[2], color[3]);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

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
	UINT8 *rgba = reinterpret_cast<UINT8*>(&colorId);
	return glm::vec4 { rgba[0], rgba[1], rgba[2], rgba[3] };
}

void Util::makeListUniqueVec3(std::vector<glm::vec3>* vectors) {
	if (vectors == nullptr || vectors->size() < 2) return;

	auto sortPred = [](const glm::vec3& lhs, const glm::vec3& rhs) -> bool {
		return lhs.x < rhs.x && lhs.y < rhs.y && lhs.z < rhs.z;
	};

	std::sort(vectors->begin(), vectors->end(), sortPred);
	vectors->erase(std::unique(vectors->begin(), vectors->end()), vectors->end());
}


std::string Util::getTextFromFile(const FSPath& filePath) {
	if (!std::filesystem::exists(filePath)) {
		throw std::exception { (filePath.string() + " isn't exists").c_str() };
	}

	if (std::filesystem::is_directory(filePath)) {
		throw std::exception { (filePath.string() + " isn't file").c_str() };
	}

	std::ifstream fh;
	int oldExceptions = fh.exceptions();
	fh.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	std::stringstream res {};

	try {
		fh.open(filePath);
		res << fh.rdbuf();
		fh.exceptions(oldExceptions);
		fh.close();
	} catch (...) {
		fh.exceptions(oldExceptions);
		throw;
	}

	return res.str();
}

bool Util::createDirectories(const FSPath& dirPath) {
	if (Util::existsDirectory(dirPath)) {
		return false;
	}

	return std::filesystem::create_directories(dirPath);
}

bool Util::existsFile(const FSPath& filePath) {
	if (std::filesystem::exists(filePath) &&
		!std::filesystem::is_directory(filePath)) {
		return true;
	}

	return false;
}

bool Util::existsDirectory(const FSPath& dirPath) {
	if (std::filesystem::exists(dirPath) &&
		std::filesystem::is_directory(dirPath)) {
		return true;
	}

	return false;
}

void Util::saveSettings(const FSPath& path, const std::string& content) {
	std::ofstream fh;

	int oldExceptions = fh.exceptions();
	fh.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	std::size_t size = content.size();

	try {
		fh.open(path, std::ios::out);
		fh << content;
		fh.exceptions(oldExceptions);
		fh.flush();
		fh.close();
	} catch (...) {
		fh.exceptions(oldExceptions);
		throw;
	}
}

std::string Util::loadSettings(const FSPath& path) {
	return getTextFromFile(path);
}
