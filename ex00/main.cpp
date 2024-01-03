#include "BitcoinExchange.hpp"

int BitcoinExchange::parsingData(long int year, long int month, long int day, std::string btc, float fBtc, std::string line)
{
	size_t		i = 0;

	// If the is no '-' between year-month-day: err.
	if (line.substr(4, 1) != "-"  || line.substr(7, 1) != "-")
	{
		std::cerr << "Error: bad input => " << line << std::endl;
		return (1);
	}
	// Return the index that point on '|'.
	i = line.find("|");
	// If there is no space bef and af '|': err.
	if (line[i - 1] != ' ' || line[i + 1] != ' ')
	{
		std::cerr << "Error: bad input => " << line << std::endl;
		return (1);
	}

	// Check year beginning of btc
    // And month validity.
	int	checkMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	if (year < 2009 || year > 2022 || month > 12 || month < 1 || day > checkMonth[month -1] || day < 1)
	{
		std::cerr << "Error: bad input => " << line << std::endl;
		return (1);		
	}

	// Check the valid format of taux float.
	int dotCounter = 0;
	int	pipeCounter = 0;
	for (int i = 0; i < btc.length(); i++)
	{
		if (btc[0] == '.')
		{
			std::cerr << "Error: bad input => " << line << std::endl;
			return (1);			
		}

		if (btc[i]== '.')
		{
			dotCounter++;
		}

		if (btc[i] == '|')
		{
			pipeCounter++;
		}
		// isdigit() return pos nbr if value is decimal (0-9).
        // No dot has been found.
		// if there is too much dots.
		if ((!(isdigit(btc[i])) && btc[i] != '.' && pipeCounter > 1) || dotCounter > 1)
		{
			std::cerr << "Error: bad input => " << line << std::endl;
			return (1);				
		}
	}

	// Check the "taux" if it's valid. (0-1000)
	if (fBtc < 0)
	{
		std::cerr << "Error: not a positive number." << std::endl;
		return (1);
	}
	else if (fBtc > 1000)
	{
		std::cerr << "Error: too large a number." << std::endl;
		return (1);
	}
	return (0);
}

void BitcoinExchange::initInput(std::string argv)
{
    // Type allow us to read the file.
    std::ifstream		fd;
    std::string     	line;

	fd.open(argv);

	// Check if the opening failed.
	if (fd.fail())
	{
		std::cerr << "Error: could not open file.";
		fd.close();
		exit(1);
	}

	// While we've not reached eof...
    // For EACH line:
	while (std::getline(fd, line))
	{
		// Will help us for a future numeric conv...
		std::stringstream 	y, m, d;

		// Recup the year...
		y << line.substr(0, 4);
		// Recup the month...
		m << line.substr(5, 2);
		// Recup the day...
		d << line.substr(8, 2);

		long int			year, month, day = 0;
		// Then assign & convert them into int
		y >> year;
		m >> month;
		d >> day;

		if (line.length() < 14)
		{
			std::cerr << "Error: bad input => " << line << std::endl;
			// Ignore the rest of the loop and iterate from here.
			continue ;
		}

		float				fBtc = 0.0;
		std::string			btc;
		std::stringstream 	conversion;
		// It extract the rate w/o the ending '\0'
		btc = line.substr(13, line.find('\0'));
		conversion << btc;
		conversion >> fBtc;

		std::string			date;
		// It convert 0X days/month into valid string reading
        // Ex: 2023,9,1 to 2023,09,01
		if (month < 10 && day < 10)
		{
			date = std::to_string(year * 10) + std::to_string(month * 10) + std::to_string(day);
		}
		else if (month < 10)
		{
			date = std::to_string(year * 10) + std::to_string(month) + std::to_string(day);
		}
		else if (day < 10)
		{
			date = std::to_string(year) + std::to_string(month * 10) + std::to_string(day);
		}
		else
		{
			date = std::to_string(year) + std::to_string(month) + std::to_string(day);
		}

		// If parsing_data return != 0 it stop
        // Else: out-puting the "result"
		if (parsingData(year, month, day, btc, fBtc, line) == 0)
			displayOutput(date, fBtc);
	}
}

void    BitcoinExchange::displayOutput(std::string date, float fBtc)
{
	int	checkerDate = 0;
	// Declaration of iterators to go through the map from the Class.

	// Point to the first element.
	std::map<std::string, float>::iterator itbegin = this->_data.begin();
	// Point to the last element + 1.
	std::map<std::string, float>::iterator itend = this->_data.end();

	// While the begin ptr didn't reached the end + 1...
	while (itbegin != itend)
	{
		if (itbegin->first == date)
		{
			checkerDate = 1;
			break;
		}
		itbegin++;
	}
	// If correspondance has been found: reinsert "-" and out it 
	if (checkerDate)
	{
		// std::setprecision(2): bloc to a result of max to numbr aftr "."
		std::cout << date.insert(4, "-").insert(7, "-") << " => " << fBtc << " = " << (itbegin->second * fBtc) << std::endl;
		return ;
	}
	else
	{
		// It index you to "the next smallest value (need to be pimped)" by a lexicographic compar.
		itend = this->_data.lower_bound(date);
		if (itend != this->_data.begin())
			itend--;
		// Print the result in a valid format.
		std::cout << date.insert(4, "-").insert(7, "-") << " => " << fBtc << " = " << (itend->second * fBtc) << std::endl;
	}
}

void	BitcoinExchange::initRateFile()
{
    // type that allow us to open and read the file.
    std::ifstream   fd;
    std::string     line;

    fd.open("./data.csv");
    // 'til the file reading did not reach the end (eof)
    while (!fd.eof())
    {
        fd >> line;
        // Delete the "-" in the date
        std::string date = line.substr(0, 10).erase(4, 1).erase(6, 1);

		// stringstream will allow us to convert value.
    	std::stringstream   converter;

        // Take pos on the first ele of the rate.
        converter << line.substr(11);
		// taux.
    	float	rate = 0.0;
        // It convert the string into a float.
        converter >> rate;
        // Insert (in a map type) : key-value pair.
        // Make_pair create a formal pair for map.
        _data.insert(std::make_pair(date, rate));
    }
    fd.close();
}

int main(int argc, char **argv)
{
    BitcoinExchange btc;

    if (argc == 2)
    {
        try
        {
            btc.initRateFile();
            // Check & init input, display output. 
            btc.initInput(argv[1]);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << std::endl;
        }
    }
    else
    {
        std::cout << "Error: could not open file." << std::endl;
    }
    return (0);
}