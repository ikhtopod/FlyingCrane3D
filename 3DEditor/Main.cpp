#include "Application.h"

int main() {
	std::string applicationName = "Application 3D Editor";

	try {
		Application(applicationName).run();
	} catch (std::exception e) {
		std::cerr << e.what() << std::endl;

		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
