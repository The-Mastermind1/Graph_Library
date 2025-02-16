#pragma once
#include <iostream>
#include <regex>
#include <string>
#include <vector>
#include<cmath>
#include<SFML/Graphics.hpp>
struct Term {
    float coefficient;
   float exponent;
};

float evaluate_polyonomial(float cofficient, float  expotent,float x) {
    return static_cast<float>(cofficient * std::pow(x, expotent));
}



std::vector<Term> parse_polynomial( std::string input) {
   
    std::regex pattern(R"([+-]?[1-9]x\^[1-9])");
    std::smatch match;
    std::sregex_iterator begin(input.begin(), input.end(), pattern);
    std::sregex_iterator end;
    std::vector<std::string>terms;
   
    for (std::sregex_iterator it = begin; it != end; ++it) {
        std::smatch match = *it;  // Παίρνουμε το τρέχον match
        terms.push_back(match.str());
       

    }
    std::vector<Term> term;
    for (size_t i = 0; i < terms.size(); i++) {
      
       std::string::iterator it = std::find(terms[i].begin(), terms[i].end(), '^');
       std::string kati{ it+1,terms[i].end() };
      
       
       term.push_back({ std::stof(terms[i]),std::stof(kati)});
       
    }
    return term;
  

}

void draw_the_graph(std::vector<Term> terms) {
    /* for (size_t i = 0; i < terms.size(); i++) {
        std::cout << terms[i].coefficient << '\n';
        std::cout << terms[i].exponent << '\n';
     }*/

    float xmin = -10.0f, xmax = 10.0f;
    float step = 0.1f;
    sf::RenderWindow window(sf::VideoMode(800, 600), "polynomial graph");
    sf::VertexArray graph(sf::LinesStrip);
    for (float x = xmin; x <= xmax; x += step) {
        float y = 0;
        for (size_t i = 0; i < terms.size(); i++) {
             y += evaluate_polyonomial(terms[i].coefficient, terms[i].exponent, x);
           
        }
        
       
        float screenX = (x - xmin) / (xmax - xmin) * 800; // Scale to window width
        float screenY = 300 - y * 10; // Scale y and center on screen (adjust scaling as needed)

        //std::cout << screenX << " " << screenY << '\n';
        graph.append(sf::Vertex(sf::Vector2f(screenX, screenY), sf::Color::Red));
    }
    float offsetx = 400;
    float offsety = 300;
    sf::VertexArray axes(sf::Lines, 4);
    axes[0].position = sf::Vector2f(0, offsety); // Άξονας X
    axes[1].position = sf::Vector2f(800, offsety);//και τα δυο
    axes[2].position = sf::Vector2f(offsetx, 0); // Άξονας Y
    axes[3].position = sf::Vector2f(offsetx, 600);//και τα δυο 

    for (int i = 0; i < 4; ++i) {
        axes[i].color = sf::Color::Blue;
    }

    sf::VertexArray grid(sf::Lines);
    for (int i = 0; i < 800; i += 50) {
        grid.append(sf::Vertex(sf::Vector2f((float)i, 0), sf::Color(200, 200, 200)));
        grid.append(sf::Vertex(sf::Vector2f((float)i, 600), sf::Color(200, 200, 200)));
    }
    for (int i = 0; i < 600; i += 50) {
        grid.append(sf::Vertex(sf::Vector2f(0, (float)i), sf::Color(200, 200, 200)));
        grid.append(sf::Vertex(sf::Vector2f(800, (float)i), sf::Color(200, 200, 200)));
    }

    // Main loop to render the graph
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black); // Clear screen
        window.draw(graph); // Draw the graph

        window.draw(axes);
        window.display(); // Display the window
    }

    return ;
}
