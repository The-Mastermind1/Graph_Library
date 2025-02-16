#include "Header.h"


int main() {
    std::string input = "1x^2+3x^1"; // Polynomial input string

   draw_the_graph(parse_polynomial(input));
  
}
