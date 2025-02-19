#include "Header.h"


int main() {
	using namespace _panagiotis_stelios;

std::string input = "5^x+2log(5x)"; // Polynomial input string
try {
	parse_graph(input);
}
catch (const _INVALID_INPUT& e) {
	std::cout << e.what() << '\n';
}

   
}
