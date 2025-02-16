#include "Header.h"
#include"SFML/Graphics.hpp"

int main() {
    std::string input = "+1x^2"; // Polynomial input string

    std::vector<Term> terms=parse_polynomial(input);
    for (size_t i = 0; i < terms.size(); i++) {
        std::cout << terms[i].coefficient << '\n';
        std::cout << terms[i].exponent << '\n';
    }
    float xmin = -10.0f, xmax = 10.0f;
    float step = 0.1f;
    sf::RenderWindow window(sf::VideoMode(800, 600), "polynomial graph");
    sf::VertexArray graph(sf::LinesStrip);
    for (float x = xmin; x <= xmax; x += step) {
        for (size_t i = 0; i < terms.size(); i++) {
           float y = evaluate_polyonomial(terms[i].coefficient, terms[i].exponent, x);
            float screenX = (x - xmin) / (xmax - xmin) * 800; // Scale to window width
            float screenY = 300 - y * 10; // Scale y and center on screen (adjust scaling as needed)

            
            graph.append(sf::Vertex(sf::Vector2f(screenX, screenY), sf::Color::Red));
        }
    }
    // Main loop to render the graph
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White); // Clear screen
        window.draw(graph); // Draw the graph
        window.display(); // Display the window
    }

    return 0;
   
}
