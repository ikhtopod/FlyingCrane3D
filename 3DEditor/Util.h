#pragma once

class Util final {
public:
	Util() = delete;
	~Util() = default;

public:
	static const glm::mat4 IDENTITY_MATRIX;

public:
	static void clearColor();
	static void clearColor(const GLfloat color[4]);
	static void clearColor(const glm::vec4& color);

public:
	static float repeat(float val, float _min, float _max);
	static glm::vec3 repeat(glm::vec3 val, float _min, float _max);
	static glm::vec2 repeat(glm::vec2 val, float _min, float _max);

	/**
		\brief ������� ������� ���� �� id

		����������� ��������� ����� ���������� ������������� ������� ���� uint32_t,
		�.�. - 4'294'967'296

		\param colorId uint32_t id �����
		\return glm::vec4 ������
	*/
	static glm::vec4 generateRGBAColorById(uint32_t colorId);

	static void makeListUniqueVec3(std::vector<glm::vec3>* vectors);

	static std::string getTextFromFile(const std::filesystem::path& filePath);
};
