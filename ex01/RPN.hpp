#ifndef RPN_HPP
# define RPN_HPP

# include <iostream>
# include <string>
// To use our container
// It will help us to stock the operands
// And render the calcul more optimized tho.
#include <stack>

class ReversePolishNotation
{
    public:
        ReversePolishNotation();
        ~ReversePolishNotation();

        void treatment(std::string polishLine);
        long int calculation(int nbr, int nbr2, char ope);

    private:
        std::stack<int> _stack;
        
};

#endif