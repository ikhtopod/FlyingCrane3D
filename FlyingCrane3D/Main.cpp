#include "Application.h"

int main() {
	std::string applicationName = "Flying Crane 3D";

	try {
		Application(applicationName, 1280, 720).run();
	} catch (std::exception e) {
		std::cerr << e.what() << std::endl;

		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
