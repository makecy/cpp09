#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <map>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <exception>

class BitcoinExchange {
private:
    std::map<std::string, double> _database;
    bool isValidDate(const std::string& date) const;
    bool isValidValue(const std::string& valueStr, double& value) const;
    std::string trim(const std::string& str) const;
    bool isLeapYear(int year) const;
    int getDaysInMonth(int month, int year) const;
    
public:
    BitcoinExchange();
    ~BitcoinExchange();
    bool loadDatabase(const std::string& filename);
    void processInputFile(const std::string& filename);
    double getExchangeRate(const std::string& date) const;
    class DatabaseLoadException : public std::exception {
    public:
        virtual const char* what() const throw() {
            return "Error: could not load database.";
        }
    };
    
    class FileOpenException : public std::exception {
    public:
        virtual const char* what() const throw() {
            return "Error: could not open file.";
        }
    };
};

#endif