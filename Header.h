#pragma once
#include <iostream>
#include <regex>
#include <string>
#include <vector>
#include<cmath>
#include<SFML/Graphics.hpp>
#include<variant>
#include<utility>



struct Term {
   float coefficient;
   float exponent;
  
};
struct Term2 {
    float expontential;
};

struct Term3 {
    float log;
};

float evaluate_polyonomial(float cofficient, float  expotent, float x) {
    return static_cast<float>(cofficient * std::pow(x, expotent));
}
float evaluate_exponential(float a, float x) {
    return std::exp(a * x);
}

float evaluate_log(float a, float x) {
    return std::log(a * x);
}

void draw_the_graph( std::vector<std::variant<Term,Term2,Term3>> terms) {
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
          
           if (terms[i].index() == 0) {
                    y += evaluate_polyonomial(std::get<0>(terms[i]).coefficient, std::get<0>(terms[i]).exponent, x);

           }
           else if(terms[i].index()==1) {
              
              
                    y += evaluate_exponential(std::get<1>(terms[i]).expontential, x);
           }
           else if (terms[i].index() == 2) {
               y += evaluate_log(std::get<2>(terms[i]).log, x);
           }
              
            
           

        }
        std::cout << y << '\n';
        system("pause");

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

    return;
}




void  parse_polynomial( std::string input) {
    std::vector<std::variant<Term, Term2,Term3>> term;
    std::regex pattern1(R"([+-]?[1-9]x\^[1-9])");
    std::regex pattern2(R"([+-]?e\^[1-9]x)");
    std::regex pattern3(R"(log\([1-9]x\))");
    
    std::smatch match;
    std::sregex_iterator begin1(input.begin(), input.end(), pattern1);
    std::sregex_iterator begin2(input.begin(), input.end(), pattern2);
    std::sregex_iterator begin3(input.begin(), input.end(), pattern3);
    std::sregex_iterator end;
   
   
    for (std::sregex_iterator it = begin1; it != end; ++it) {
        Term a;
        std::smatch match = *it;  // Παίρνουμε το τρέχον match gia polywnyma
        std::string kati{ match.str() };//ax^n
        
        a.coefficient = std::stof(kati);
        
       
       
        std::string::iterator it2 = std::find(kati.begin(), kati.end(),'^');
        std::string kati2{ it2 + 1,kati.end()};
        
       
        
        a.exponent = std::stof(kati2);
        
        std::cout << a.coefficient << " " << a.exponent << '\n';

        term.push_back(std::move(a));
       

    }
    //std::cout << "hello\n";

    for (std::sregex_iterator it = begin2; it != end; ++it) {
        
        std::smatch match = *it;  // Παίρνουμε το τρέχον match gia e^ax
        std::string kati{ match.str() };//e^ax
        std::string::iterator it2 = std::find(kati.begin(), kati.end(), '^');
        std::string kati2{ it2 + 1,kati.end() };
        Term2 a;
        a.expontential = stof(kati2);
        term.push_back(std::move(a));
      
        


    }
    for (std::sregex_iterator it = begin3; it != end; ++it) {
       
        std::smatch match = *it;
        std::string kati{ match.str() };
        std::string::iterator it2 = std::find(kati.begin(), kati.end(), '(');
        std::string kati2{ it2 + 1,kati.end() };
        Term3 a;
        a.log = stof(kati2);
        term.push_back(std::move(a));

       
    }
    
   
   draw_the_graph(std::move(term));
  

}

