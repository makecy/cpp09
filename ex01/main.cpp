#include "RPN.hpp"

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " \"<RPN expression>\"" << std::endl;
        return 1;
    }
    
    try {
        RPN calculator;
        double result = calculator.calculate(argv[1]);
        std::cout << result << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}

// some tests for RPN calc


// # Provided examples
// ./RPN "8 9 * 9 - 9 - 9 - 4 - 1 +"    # Output: 42
// ./RPN "7 7 * 7 -"                     # Output: 42
// ./RPN "1 2 * 2 / 2 * 2 4 - +"         # Output: 0
// ./RPN "(1 + 1)"                       # Output: Error

// # Additional tests
// ./RPN "1 2 +"                         # Output: 3
// ./RPN "5 3 -"                         # Output: 2
// ./RPN "4 2 /"                         # Output: 2
// ./RPN "3 4 * 2 +"                     # Output: 14
// ./RPN "1 0 /"                         # Output: Error (division by zero)
// ./RPN "1 2"                           # Output: Error (too many operands)
// ./RPN "1 +"                           # Output: Error (insufficient operands)