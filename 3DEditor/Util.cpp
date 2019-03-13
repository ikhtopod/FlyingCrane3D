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

	std::cout << res << std::endl;

	return res;
}
