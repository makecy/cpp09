#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {
}

BitcoinExchange::~BitcoinExchange() {
}

bool BitcoinExchange::loadDatabase(const std::string& filename) {
    std::ifstream file(filename.c_str());
    if (!file.is_open()) {
        return false;
    }
    std::string line;
    bool firstLine = true;
    
    while (std::getline(file, line)) {
        if (firstLine) {
            firstLine = false;
            continue;
        }
        if (line.empty())
            continue;
        size_t commaPos = line.find(',');
        if (commaPos == std::string::npos)
            continue;
        std::string date = line.substr(0, commaPos);
        std::string rateStr = line.substr(commaPos + 1);
        if (isValidDate(date)) {
            double rate;
            std::stringstream ss(rateStr);
            if (ss >> rate) {
                _database[date] = rate;
            }
        }
    }
    file.close();
    return !_database.empty();
}

void BitcoinExchange::processInputFile(const std::string& filename) {
    std::ifstream file(filename.c_str());
    if (!file.is_open()) {
        throw FileOpenException();
    }
    
    std::string line;
    bool firstLine = true;
    
    while (std::getline(file, line)) {
        if (firstLine) {
            firstLine = false;
            continue;
        }
        if (line.empty())
            continue;
        size_t pipePos = line.find(" | ");
        if (pipePos == std::string::npos) {
            std::cout << "Error: bad input => " << line << std::endl;
            continue;
        }
        std::string date = trim(line.substr(0, pipePos));
        std::string valueStr = trim(line.substr(pipePos + 3));
        if (!isValidDate(date)) {
            std::cout << "Error: bad input => " << date << std::endl;
            continue;
        }
        double value;
        if (!isValidValue(valueStr, value)) {
            if (valueStr.find('-') != std::string::npos) {
                std::cout << "Error: not a positive number." << std::endl;
            } else {
                std::cout << "Error: bad input => " << valueStr << std::endl;
            }
            continue;
        }
        if (value < 0) {
            std::cout << "Error: not a positive number." << std::endl;
            continue;
        }
        if (value > 1000) {
            std::cout << "Error: too large a number." << std::endl;
            continue;
        }
        double rate = getExchangeRate(date);
        double result = value * rate;
        std::cout << date << " => " << value << " = " << result << std::endl;
    }
    file.close();
}

double BitcoinExchange::getExchangeRate(const std::string& date) const {
    std::map<std::string, double>::const_iterator it = _database.upper_bound(date);
    if (it == _database.begin())
        return 0.0;
    --it;
    return it->second;
}

bool BitcoinExchange::isValidDate(const std::string& date) const {
    if (date.length() != 10)
        return false;
    if (date[4] != '-' || date[7] != '-')
        return false;
    std::string yearStr = date.substr(0, 4);
    std::string monthStr = date.substr(5, 2);
    std::string dayStr = date.substr(8, 2);
    for (int i = 0; i < 4; i++) {
        if (!isdigit(yearStr[i]))
            return false;
    }
    for (int i = 0; i < 2; i++) {
        if (!isdigit(monthStr[i]))
            return false;
        if (!isdigit(dayStr[i]))
            return false;
    }
    int year, month, day;
    std::stringstream ss1(yearStr), ss2(monthStr), ss3(dayStr);
    ss1 >> year;
    ss2 >> month;
    ss3 >> day;
    if (year < 1000 || year > 3000) return false;
    if (month < 1 || month > 12) return false;
    if (day < 1 || day > getDaysInMonth(month, year)) return false;
    return true;
}

bool BitcoinExchange::isValidValue(const std::string& valueStr, double& value) const {
    if (valueStr.empty())
        return false;
    std::stringstream ss(valueStr);
    ss >> value;
    return !ss.fail() && ss.eof();
}

std::string BitcoinExchange::trim(const std::string& str) const {
    size_t start = str.find_first_not_of(" \t\r\n");
    if (start == std::string::npos)
        return "";
    size_t end = str.find_last_not_of(" \t\r\n");
    return str.substr(start, end - start + 1);
}

bool BitcoinExchange::isLeapYear(int year) const {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int BitcoinExchange::getDaysInMonth(int month, int year) const {
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (month == 2 && isLeapYear(year))
        return 29;
    return daysInMonth[month - 1];
}