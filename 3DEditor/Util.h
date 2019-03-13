#pragma once

class Util final {
public:
	Util() = delete;
	~Util() = default;

public:
	static const glm::mat4 IDENTITY_MATRIX;

public:
	static float repeat(float val, float _min, float _max);

};
