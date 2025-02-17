#include "Header.h"


int main() {
	using namespace _panagiotis_stelios;
	
	std::string input = "1x^4"; // Polynomial input string
	try {

		parse_graph(input);
	}
	catch (const _INVALID_INPUT& e) {
		 std::cout << e.what() << '\n';
	}

   
}
