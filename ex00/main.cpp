#include "BitcoinExchange.hpp"

int main(int argc, char** argv)
{
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return 1;
    }
    try {
        BitcoinExchange exchange;
        if (!exchange.loadDatabase("data.csv"))
            throw BitcoinExchange::DatabaseLoadException();
        exchange.processInputFile(argv[1]);
    } catch (const BitcoinExchange::FileOpenException& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    } catch (const BitcoinExchange::DatabaseLoadException& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}