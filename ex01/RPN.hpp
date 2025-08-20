#ifndef RPN_HPP
#define RPN_HPP

#include <stack>
#include <string>
#include <sstream>
#include <iostream>
#include <exception>

class RPN {
private:
    std::stack<double> _stack;
    bool isOperator(const std::string& token) const;
    bool isNumber(const std::string& token) const;
    double performOperation(double a, double b, const std::string& op) const;
    
public:
    double calculate(const std::string& expression);
    class InvalidExpressionException : public std::exception {
    public:
        virtual const char* what() const throw() {
            return "Error";
        }
    };
    class DivisionByZeroException : public std::exception {
    public:
        virtual const char* what() const throw() {
            return "Error";
        }
    };
    class InvalidTokenException : public std::exception {
    public:
        virtual const char* what() const throw() {
            return "Error";
        }
    };
};

#endif