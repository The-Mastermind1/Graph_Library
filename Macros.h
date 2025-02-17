#pragma once
#include<exception>
#include<string>
#define _P_S_BEGIN namespace _panagiotis_stelios{

#define _P_S_END }

#define _NODISCARD [[nodiscard]]


struct Term {
    float coefficient;
    float exponent;

};
struct Term2 {
    float a;
    float expontential;
};

struct Term3 {
    float a;
    float log;
};

struct Term4 {
    float a;
    float sin;
};
struct Term5 {
    float a;
    float cos;
};

struct Term6 {
    float a;
};


class _INVALID_INPUT : public std::exception {
private:
    std::string errorMessage; // To store the error message
public:
    // Constructor to initialize the error message
    explicit _INVALID_INPUT(const std::string& message)
        : errorMessage(message) {
    }

    // Override the what() method
    const char* what() const noexcept override {
        return errorMessage.c_str();
    }
};

template<typename ...ts>
struct overload :ts...{
    using ts::operator()...;
};
template<typename ...ts>
overload(ts...) -> overload<ts...>;




