#include "RPN.hpp"

int main(int argc, char **argv)
{
    ReversePolishNotation   Rpn;

    if (argc == 2)
    {
        try
        {
            Rpn.treatment(argv[1]);
        }
        catch(const std::exception &e)
        {
            std::cerr << e.what() << std::endl;
        }
    }
    else
    {
        std::cerr << "Error: Too much arguments in inputs." << std::endl;
        return (1);
    }
    return (0);
}