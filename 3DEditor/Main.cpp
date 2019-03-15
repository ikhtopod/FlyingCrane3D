#include "Application.h"

int main() {
	std::string applicationName = "Lowpoly Style 3D Editor";

	try {
		Application(applicationName, 1280, 720).run();
	} catch (std::exception e) {
		std::cerr << e.what() << std::endl;

		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
