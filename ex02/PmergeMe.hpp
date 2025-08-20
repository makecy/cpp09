#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <deque>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <ctime>
#include <sys/time.h>
#include <exception>
#include <iomanip>

class PmergeMe {
private:
    std::vector<int> _vectorContainer;
    std::deque<int> _dequeContainer;
    bool isValidNumber(const std::string& str) const;
    double getCurrentTime() const;
    void fordJohnsonSort(std::vector<int>& container);
    void mergeInsertSort(std::vector<int>& container, int start, int end);
    void insertionSort(std::vector<int>& container, int start, int end);
    void fordJohnsonSort(std::deque<int>& container);
    void mergeInsertSort(std::deque<int>& container, int start, int end);
    void insertionSort(std::deque<int>& container, int start, int end);
    
public:
    void parseInput(int argc, char** argv);
    void sortAndDisplay();
    class InvalidInputException : public std::exception {
    public:
        virtual const char* what() const throw() {
            return "Error";
        }
    };
};

#endif