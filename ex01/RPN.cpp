#include "RPN.hpp"

double RPN::calculate(const std::string& expression) {
    while (!_stack.empty()) {
        _stack.pop();
    }
    
    std::istringstream iss(expression);
    std::string token;
    
    while (iss >> token) {
        if (isNumber(token)) {
            double num;
            std::stringstream ss(token);
            ss >> num;
            _stack.push(num);
        }
        else if (isOperator(token)) {
            if (_stack.size() < 2) {
                throw InvalidExpressionException();
            }
            double b = _stack.top(); _stack.pop();
            double a = _stack.top(); _stack.pop();
            double result = performOperation(a, b, token);
            _stack.push(result);
        }
        else {
            throw InvalidTokenException();
        }
    }
    if (_stack.size() != 1) {
        throw InvalidExpressionException();
    }
    
    return _stack.top();
}

bool RPN::isOperator(const std::string& token) const {
    return (token == "+" || token == "-" || token == "*" || token == "/");
}

bool RPN::isNumber(const std::string& token) const {
    if (token.empty()) return false;
    
    size_t start = 0;
    if (token[0] == '-' || token[0] == '+') {
        if (token.length() == 1) return false;
        start = 1;
    }
    for (size_t i = start; i < token.length(); i++) {
        if (!isdigit(token[i])) {
            return false;
        }
    }
    return true;
}

double RPN::performOperation(double a, double b, const std::string& op) const {
    if (op == "+") {
        return a + b;
    }
    else if (op == "-") {
        return a - b;
    }
    else if (op == "*") {
        return a * b;
    }
    else if (op == "/") {
        if (b == 0) {
            throw DivisionByZeroException();
        }
        return a / b;
    }
    throw InvalidTokenException();
}