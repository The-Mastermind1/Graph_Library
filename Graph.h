
#pragma once
#include <iostream>
#include"Macros.h"
#include <regex>
#include <vector>
#include<cmath>
#include<SFML/Graphics.hpp>
#include<variant>
#include<utility>
#include<iterator>



_P_S_BEGIN

_NODISCARD inline  float evaluate_polyonomial(float cofficient, float  expotent, float x)noexcept {
    std::cout << cofficient << " " << expotent << '\n';
    return static_cast<float>(cofficient * std::pow(x, expotent));
}
_NODISCARD inline float evaluate_exponential(float n, float a, float x)noexcept {
    std::cout << n << " " << a << '\n';

    return n * std::exp(a * x);
}

_NODISCARD inline float evaluate_log(float n, float a, float x)noexcept {
    std::cout << n << " " << a << '\n';
    return n * std::log(a * x);
}

_NODISCARD inline float evaluate_sin(float n, float a, float x)noexcept {
    std::cout << n << " " << a << '\n';
    return n * std::sin(a * x);
}

_NODISCARD inline float evaluate_cos(float n, float a, float x)noexcept {
    std::cout << n << " " << a << '\n';

    return n * std::cos(a * x);
}
_NODISCARD inline float evaluate_a(float a, float x)noexcept {
    std::cout << a << '\n';
    if (a > 0) {
        return std::pow(a, x);
    }
    else if (a < 0) {
        return -std::pow(-a, x);
    }


    //return std::pow(a, x);
}



using Terms = std::variant < Term, Term2, Term3, Term4, Term5, Term6>;
inline void draw_the_graph(std::vector<Terms>& terms, sf::RenderTexture& rendertexture, sf::Texture& texture) {

    /* for (size_t i = 0; i < terms.size(); i++) {
        std::cout << terms[i].coefficient << '\n';
        std::cout << terms[i].exponent << '\n';
     }*/
    float xmin = -10.0f;
    float xmax = 10.0f;
    try {
        float step = 0.1f;

        sf::VertexArray graph(sf::LineStrip);//connects the dots on the graph

        for (float x = xmin; x <= xmax; x += step) {
            float y = 0;

            for (size_t i = 0; i < terms.size(); i++) {

                /*if (terms[i].index() == 0 &&!terms[i].valueless_by_exception()) {
                         y += evaluate_polyonomial(std::get<0>(terms[i]).coefficient, std::get<0>(terms[i]).exponent, x);

                }
                else if(terms[i].index()==1 && !terms[i].valueless_by_exception()) {


                         y += evaluate_exponential(std::get<1>(terms[i]).a,std::get<1>(terms[i]).expontential, x);
                }
                else if (terms[i].index() == 2 && !terms[i].valueless_by_exception()) {
                    y += evaluate_log(std::get<2>(terms[i]).a,std::get<2>(terms[i]).log, x);
                }
                else if (terms[i].index() == 3 && !terms[i].valueless_by_exception()) {
                    y += evaluate_sin(std::get<3>(terms[i]).a,std::get<3>(terms[i]).sin, x);

                }
                else if (terms[i].index() == 4 && !terms[i].valueless_by_exception()) {
                    y += evaluate_cos(std::get<4>(terms[i]).a,std::get<4>(terms[i]).cos, x);

                }*/
                if (!terms[i].valueless_by_exception()) {
                    std::visit(overload{
                     [&y,x](Term& val) {y += evaluate_polyonomial(val.coefficient,val.exponent,x); },
                     [&y,x](Term2& val) {y += evaluate_exponential(val.a,val.expontential,x); },
                     [&y,x](Term3& val) {y += evaluate_log(val.a,val.log,x); },
                     [&y,x](Term4& val) {y += evaluate_sin(val.a,val.sin,x); },
                     [&y,x](Term5& val) {y += evaluate_cos(val.a,val.cos,x); },
                     [&y,x](Term6& val) {y += evaluate_a(val.a,x); }, },
                     terms[i]);
                }







            }
            std::cout << "y:" << y << " x: " << x << '\n';
            //std::cout << y << '\n';


            float screenX = (x - xmin) / (xmax - xmin) * 800; // Scale to window width
            float screenY = 300 - y * 10; // Scale y and center on screen (adjust scaling as needed)

            //std::cout << screenX << " " << screenY << '\n';
            graph.append(sf::Vertex(sf::Vector2f(screenX, screenY), sf::Color::Red));//take vertexes
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
        //while (window.isOpen()) {
        //    sf::Event event;
        //    while (window.pollEvent(event)) {
        //        if (event.type == sf::Event::Closed) {
        //            sf::Texture screentexture;
        //            screentexture.create(window.getSize().x, window.getSize().y);
        //            screentexture.update(window);

        //            sf::Image screenshot = screentexture.copyToImage();
        //            if (!screenshot.saveToFile("output.png")) { // You can also use "output.png"
        //                throw _FAILED_LOADED_IMAGE{ "Failed to load the image\n" };
        //            }


        //            window.close();
        //        }
        //    }

        //    window.clear(sf::Color::Black); // Clear screen
        //    window.draw(grid);
        //    window.draw(axes);

        //    window.draw(graph); // Draw the graph


        //    window.display(); // Display the window
        //}
        //window.~RenderWindow();




        if (rendertexture.create(800, 600)) {

            rendertexture.clear(sf::Color::Black);
            rendertexture.draw(grid);
            rendertexture.draw(axes);
            rendertexture.draw(graph);
            rendertexture.display();
            //sf::sleep(sf::milliseconds(100)); // Small delay to ensure window updates

            texture = rendertexture.getTexture();


            sf::Image screenshot = texture.copyToImage();
            if (!screenshot.saveToFile("static/icons/icon.png")) {
                throw _FAILED_LOADED_IMAGE{ "Failed to load the image\n" };
            }

        }
        else {
            throw _FAILED_ACTION{ "Something went wrong" };
        }

        //sf::sleep(sf::milliseconds(1000));



    }
    catch (...) {
        throw _FAILED_ACTION{ "Something went wrong" };

    }



    return;
}




inline void  parse_graph(const std::string& input, sf::RenderTexture& rendertexture, sf::Texture& texture) {

    std::vector<Terms> term;
    std::regex pattern1(R"([+-]?([1-9][0-9]*)*x\^[1-9][0-9]*)");
    std::regex pattern2(R"([+-]?([1-9][0-9]*)*e\^[1-9][0-9]*x)");
    std::regex pattern3(R"([+-]?([1-9][0-9]*)*log\([1-9][0-9]*x\))");
    std::regex pattern4(R"([+-]?([1-9][0-9]*)*sin\([1-9][0-9]*x\))");
    std::regex pattern5(R"([+-]?([1-9][0-9]*)*cos\([1-9][0-9]*x\))");
    std::regex pattern6(R"([+-]?[1-9][0-9]*\^x)");



    std::sregex_iterator begin1(input.cbegin(), input.cend(), pattern1);
    std::sregex_iterator begin2(input.cbegin(), input.cend(), pattern2);
    std::sregex_iterator begin3(input.cbegin(), input.cend(), pattern3);
    std::sregex_iterator begin4(input.cbegin(), input.cend(), pattern4);
    std::sregex_iterator begin5(input.cbegin(), input.cend(), pattern5);
    std::sregex_iterator begin6(input.cbegin(), input.cend(), pattern6);
    std::sregex_iterator end;
    std::smatch match;
    std::string kati;


    std::string::iterator it2;

    std::size_t iterations = 0;//see the iterations
    iterations += std::distance(begin1, end);
    iterations += std::distance(begin2, end);
    iterations += std::distance(begin3, end);
    iterations += std::distance(begin4, end);
    iterations += std::distance(begin5, end);
    iterations += std::distance(begin6, end);

    term.reserve(iterations);


    for (std::sregex_iterator it = begin1; it != end; ++it) {


        match = *it;


        kati = match.str();//ax^n

        it2 = std::find(kati.begin(), kati.end(), '^');
        std::string kati2{ it2 + 1,kati.end() };



        if (kati[0] != 'x') {
            try {
                term.emplace_back<Term>({ std::stof(kati),std::stof(kati2) });
            }
            catch (...) {

                throw _INVALID_INPUT{ "Invalid Input" };
            }

        }
        else {
            try {
                term.emplace_back<Term>({ 1,std::stof(kati2) });
            }
            catch (...) {
                throw _INVALID_INPUT{ "Invalid Input" };
            }
        }





    }



    for (std::sregex_iterator it = begin2; it != end; ++it) {

        match = *it;
        kati = match.str();//e^ax


        it2 = std::find(kati.begin(), kati.end(), '^');
        std::string kati2{ it2 + 1,kati.end() };




        if (kati[0] != 'e') {
            try {
                term.emplace_back<Term2>({ std::stof(kati),std::stof(kati2) });
            }
            catch (...) {
                throw _INVALID_INPUT{ "Invalid Input" };
            }
        }
        else {
            try {
                term.emplace_back<Term2>({ 1,std::stof(kati2) });
            }
            catch (...) {
                throw _INVALID_INPUT{ "Invalid Input" };
            }
        }






    }
    for (std::sregex_iterator it = begin3; it != end; ++it) {

        match = *it;

        kati = match.str();//nlog(ax)


        it2 = std::find(kati.begin(), kati.end(), '(');
        std::string kati2{ it2 + 1,kati.end() };



        if (kati[0] != 'l') {
            try {
                term.emplace_back<Term3>({ std::stof(kati),std::stof(kati2) });
            }
            catch (...) {
                throw _INVALID_INPUT{ "Invalid Input" };
            }
        }
        else {
            try {
                term.emplace_back<Term3>({ 1,std::stof(kati2) });
            }
            catch (...) {
                throw _INVALID_INPUT{ "Invalid Input" };
            }
        }


    }
    for (std::sregex_iterator it = begin4; it != end; it++) {

        match = *it;
        kati = match.str();//nsin(ax)

        it2 = std::find(kati.begin(), kati.end(), '(');
        std::string kati2{ it2 + 1,kati.end() };



        if (kati[0] != 's') {
            try {
                term.emplace_back<Term4>({ std::stof(kati),std::stof(kati2) });
            }
            catch (...) {

                throw _INVALID_INPUT{ "Invalid Input" };
            }

        }
        else {
            try {
                term.emplace_back<Term4>({ 1,std::stof(kati2) });
            }
            catch (...) {
                throw _INVALID_INPUT{ "Invalid Input" };
            }
        }

    }
    for (std::sregex_iterator it = begin5; it != end; it++) {
        match = *it;
        kati = match.str();//ncos(ax)

        it2 = std::find(kati.begin(), kati.end(), '(');
        std::string kati2{ it2 + 1,kati.end() };



        if (kati[0] != 'c') {
            try {
                term.emplace_back<Term5>({ std::stof(kati),std::stof(kati2) });
            }
            catch (...) {
                throw _INVALID_INPUT{ "Invalid Input" };

            }
        }
        else {
            try {
                term.emplace_back<Term5>({ 1,std::stof(kati2) });
            }
            catch (...) {
                throw _INVALID_INPUT{ "Invalid Input" };
            }
        }


    }

    for (std::sregex_iterator it = begin6; it != end; it++) {
        match = *it;
        kati = match.str();//a^x
        try {

            term.emplace_back<Term6>({ std::stof(kati) });
        }
        catch (...) {
            throw _INVALID_INPUT{ "Invalid Input" };
        }



    }





    if (term.size() == 0) {
        throw _INVALID_INPUT{ "Invalid Input" };
    }
    draw_the_graph(term, rendertexture, texture);
    return;

}

_P_S_END

