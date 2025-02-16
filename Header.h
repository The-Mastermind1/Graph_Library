#pragma once
#include <iostream>
#include <regex>
#include <string>
#include <vector>
#include<cmath>

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
