#pragma once
#include <iostream>
#include"Macros.h"
#include <regex>
#include <string>
#include <vector>
#include<cmath>
#include<SFML/Graphics.hpp>
#include<variant>
#include<utility>
#include<string_view>

_P_S_BEGIN




_NODISCARD inline  float evaluate_polyonomial(float cofficient, float  expotent, float x) {
    std::cout << cofficient << " " << expotent << '\n';
    return static_cast<float>(cofficient * std::pow(x, expotent));
}
_NODISCARD inline float evaluate_exponential(float n,float a, float x) {
    std::cout << n << " " << a << '\n';
    
    return n*std::exp(a * x);
}

_NODISCARD inline float evaluate_log(float n, float a, float x) {
    std::cout << n << " " << a << '\n';
    return n*std::log(a * x);
}

_NODISCARD inline float evaluate_sin(float n, float a, float x) {
    std::cout << n << " " << a << '\n';
    return n*std::sin(a * x);
}

_NODISCARD inline float evaluate_cos(float n, float a, float x) {
    std::cout << n << " " << a << '\n';
   
    return n*std::cos(a * x);
}
inline void draw_the_graph(std::vector<std::variant<Term,Term2,Term3,Term4,Term5>>& terms) {
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
              
              
                    y += evaluate_exponential(std::get<1>(terms[i]).a,std::get<1>(terms[i]).expontential, x);
           }
           else if (terms[i].index() == 2) {
               y += evaluate_log(std::get<2>(terms[i]).a,std::get<2>(terms[i]).log, x);
           }
           else if (terms[i].index() == 3) {
               y += evaluate_sin(std::get<3>(terms[i]).a,std::get<3>(terms[i]).sin, x);

           }
           else if (terms[i].index() == 4) {
               y += evaluate_cos(std::get<4>(terms[i]).a,std::get<4>(terms[i]).cos, x);

           }
           
           
           
              
            
           

        }
        //std::cout << y << '\n';
       

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
        window.draw(axes);
        window.draw(graph); // Draw the graph

        
        window.display(); // Display the window
    }

    return;
}




inline void  parse_polynomial(const std::string input) {
    std::vector<std::variant<Term, Term2,Term3,Term4,Term5>> term;
    std::regex pattern1(R"([+-]?[1-9]+x\^[1-9]+)");
    std::regex pattern2(R"([+-]?[1-9]*e\^[1-9]+x)");
    std::regex pattern3(R"([+-]?[1-9]*log\([1-9]+x\))");
    std::regex pattern4(R"([+-]?[1-9]*sin\([1-9]+x\))");
    std::regex pattern5(R"([+-]?[1-9]*cos\([1-9]+x\))");
   
   
    std::sregex_iterator begin1(input.cbegin(), input.cend(), pattern1);
    std::sregex_iterator begin2(input.cbegin(), input.cend(), pattern2);
    std::sregex_iterator begin3(input.cbegin(), input.cend(), pattern3);
    std::sregex_iterator begin4(input.cbegin(), input.cend(), pattern4);
    std::sregex_iterator begin5(input.cbegin(), input.cend(), pattern5);
  
    std::sregex_iterator end;
   
   
    for (std::sregex_iterator it = begin1; it != end; ++it) {
        Term a;
        std::smatch match = *it;
        std::string kati{ match.str() };//ax^n
        try {
            a.coefficient = std::stof(kati);
        }
        catch (const std::exception& e) {
            std::cout << e.what() << '\n';
            return;
        }
        
       
       
        std::string::iterator it2 = std::find(kati.begin(), kati.end(),'^');
        std::string kati2{ it2 + 1,kati.end()};
        
       
       
       a.exponent = std::stof(kati2);
        
       
        
       

        term.push_back(std::move(a));
       

    }
   

    for (std::sregex_iterator it = begin2; it != end; ++it) {
        
        std::smatch match = *it;  
        std::string kati{ match.str() };//e^ax
        Term2 a;
        if (kati[0] != 'e') {
            try {
                a.a = stof(kati);
            }
            catch (const std::invalid_argument&e) {
                std::cout << e.what() << '\n';
                return;
            }
        }
        else {
            a.a = 1;
        }
        std::string::iterator it2 = std::find(kati.begin(), kati.end(), '^');
        std::string kati2{ it2 + 1,kati.end() };
      
      
          
        a.expontential = stof(kati2);
        
        
        term.push_back(std::move(a));
      
        


    }
    for (std::sregex_iterator it = begin3; it != end; ++it) {
       
        std::smatch match = *it;
        std::string kati{ match.str() };//nlog(ax)
        Term3 a;
        if (kati[0] != 'l') {
            try {
                a.a = stof(kati);
            }
            catch (const std::invalid_argument& e) {
                std::cout << e.what() << '\n';
                return;
            }
        }
        else {
            a.a = 1;
        }
        std::string::iterator it2 = std::find(kati.begin(), kati.end(), '(');
        std::string kati2{ it2 + 1,kati.end() };
      
        a.log = stof(kati2);
        
      
        term.push_back(std::move(a));

       
    }
    for (std::sregex_iterator it = begin4; it != end; it++) {
        
        std::smatch match = *it;
        std::string kati{ match.str() };//nsin(ax)
        Term4 a;
        if (kati[0] != 's') {
            try {
                a.a = stof(kati);
            }
            catch (const std::invalid_argument& e) {
                std::cout << e.what() << '\n';
                return;
            }
        }
        else {
            a.a = 1;
        }
        std::string::iterator it2 = std::find(kati.begin(), kati.end(), '(');
        std::string kati2{ it2 + 1,kati.end() };
       
        a.sin = stof(kati2);
        
       
        term.push_back(std::move(a));

    }
    for (std::sregex_iterator it = begin5; it != end; it++) {
        std::smatch match = *it;
        std::string kati{ match.str() };//ncos(ax)
        Term5 a;
        if (kati[0] != 'c') {
            try {
                a.a = stof(kati);
            }
            catch (const std::invalid_argument& e) {
                std::cout << e.what() << '\n';
                return;
            }
        }
        else {
            a.a = 1;
        }
        std::string::iterator it2 = std::find(kati.begin(), kati.end(), '(');
        std::string kati2{ it2 + 1,kati.end() };
       
        a.cos = stof(kati2);
        
        
        term.push_back(std::move(a));

       
    }
   
    if (term.size() == 0) {
        throw _INVALID_INPUT("Invalid input");
    }
   draw_the_graph(term);
   return;

}

_P_S_END


