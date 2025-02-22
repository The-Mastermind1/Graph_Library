#include "Header.h"


int main() {
	using namespace _panagiotis_stelios;

	std::string input = "+5^x+2log(5x)"; // Polynomial input string
	try {
		sf::RenderTexture rendertexture;
		  if (!rendertexture.create(800, 600)) {
		    throw _FAILED_ACTION{ "Failed to create render texture" };
		  }
		
		  sf::Texture texture;

		parse_graph(input,rendertexture,texture);
	}
	catch (const _INVALID_INPUT& e) {
		std::cout << e.what() << '\n';
	}


}
