# include "RPN.hpp"

ReversePolishNotation::ReversePolishNotation(){}

ReversePolishNotation::~ReversePolishNotation(){}

ReversePolishNotation::ReversePolishNotation(ReversePolishNotation const &other) {}

ReversePolishNotation &ReversePolishNotation::operator=(ReversePolishNotation const &other)
{
    return (*this);
}

void ReversePolishNotation::treatment(std::string polishLine)
{
    int ope = 0;
    int nbr = 0;
    std::string operands = "+-/*";

    if (polishLine.empty())
    {
        throw std::invalid_argument("Error");
    }
    else if (isdigit(polishLine[0]) && !isdigit(polishLine[2]) || !isdigit(polishLine[0]))
    {
        throw std::invalid_argument("Error: invalid Reverse Polish Notation input.");
    }
    for (int i = 0; i < polishLine.length(); i++)
    {
        if (isdigit(polishLine[i]))
        {
            if (isdigit(polishLine[i - 1]) || isdigit(polishLine[i + 1]))
                throw std::invalid_argument("Error: number is bigger than 10.");
            nbr++;
            // Convert it into a valid int true ascii.
			// Then push it to the stack.
            this->_stack.push(polishLine[i] - '0');
        }

        else if (operands.find(polishLine[i]) != std::string::npos)
        {
            ope++;
            // He takes the nbr on the top of the stack, stock it in an int.
            int nbr1 = this->_stack.top();
            // He take off the number on top.
            this->_stack.pop();
            // He put in the top the calcul of n1, current top nbr, with the operator.
            int tmp = calculation(nbr1, this->_stack.top(), polishLine[i]);
            this->_stack.pop();
            this->_stack.push(tmp);
        }

        else if (polishLine[i] == ' ')
        {
            // If it is a space: iterate.
            continue ;
        }
        else
        {
            throw std::invalid_argument("Error");
        }
    }
    if ((ope + 1) != nbr)
    {
        throw std::invalid_argument("Operator number is not valid.");
    }
    std::cout << this->_stack.top() << std::endl;
}

long int ReversePolishNotation::calculation(int nbr1, int nbr2, char ope)
{
    switch (ope)
    {
        case '+':
            return (nbr1 + nbr2);
        case '-':
        {
            // Reversed because he has been reversed first by stacking.
            return (nbr2 - nbr1);
        }
        case '/':
        {
            if (nbr1 == 0)
            {
                throw std::invalid_argument("Division by zero is not possible.");
            }
            // Reversed because he has been reversed first by stacking.
            return (nbr2 / nbr1);
        }
        case '*':
            return (nbr1 * nbr2);
    }
    return (0);
}