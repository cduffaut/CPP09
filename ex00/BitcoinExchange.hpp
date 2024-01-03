#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <iostream>
# include <string>

// For reading files.
# include <fstream>
// Will do the conversion from types data to strings.
# include <sstream>
// For isdigit() & ...
# include <cctype>
// For the use of map contenair
# include <map>
// For the use of std::fixed
# include <iomanip>

class BitcoinExchange
{
    public:
        BitcoinExchange();
        ~BitcoinExchange();

        void    initRateFile();
        void    initInput(std::string argv);
        int     parsingData(long int year, long int month, long int day, std::string btc, float fBtc, std::string line);
        void    displayOutput(std::string date, float fBtc);
    private:
        std::map<std::string, float> _data;
    // container type that allow us to create key-values
    // Here key is type string (date) and value attach is a float (value)
};

#endif