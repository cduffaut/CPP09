#include "PmergeMe.hpp"

// Merge-insertion sort or the Ford–Johnson algorithm
template <typename PairContainer, typename Container>
void    merge_insert(int argc, char **argv, PairContainer &vectorContainer, Container &stockOne, Container &stockTwo, int containerType, int is_odd, int last_nbr)
{
    // Creation of 2 structs timeval.
    struct timeval start, end;

    // Recup the start time in start struct.
    gettimeofday(&start, NULL);

    // Go through all of the values of the vector.
    for (int i = 0; i < vectorContainer.size(); i++)
    {
        // Swap the value if they're not sorted.
        if (vectorContainer[i].first > vectorContainer[i].second)
        {
            std::swap(vectorContainer[i].first, vectorContainer[i].second);
        }
    }

    // Push all smallest values in a container One in croissant order
    for (int i = 0; i < vectorContainer.size(); i++)
    {
        stockOne.push_back(vectorContainer[i].first);
    }

    // Push all bigger values in a container Two in croissant order
    for (int i = 0; i < vectorContainer.size(); i++)
    {
        stockTwo.push_back(vectorContainer[i].second);
    }

    // Sort the values in the final container (stock all the result)
    std::sort(stockOne.begin(), stockOne.end());

    // Put all bigger values in order thanks to lower_bound.
    for (int i = 0; i < stockTwo.size(); i++)
    {
        stockOne.insert(std::lower_bound(stockOne.begin(), stockOne.end(), stockTwo[i]), stockTwo[i]);
    }

    // If the list was odd, now it insert the odd value in the order.
    if (is_odd)
    {
        stockOne.insert(std::lower_bound(stockOne.begin(), stockOne.end(), last_nbr), last_nbr);
    }

    gettimeofday(&end, NULL);
    long sec, micro;

    sec = end.tv_sec - start.tv_sec;
    micro = end.tv_usec - start.tv_usec;

    // convert the final result in double type in microsecond
    double final = static_cast<double>(sec) * 1.0e6 + static_cast<double>(micro);

    if (containerType == VECTOR)
    {
        // Print the result.
        std::cout << "After:   ";

        if ((argc - 1) < 6)
        {
            for (int i = 0; i < (argc - 1); i++)
            {
                std::cout << stockOne[i] << " ";
            }
        }
        else
        {
            for (int i = 0; i < 4; i++)
            {
                std::cout << stockOne[i] << " ";
            }
            std::cout << "[...]";
        }
        std::cout << std::endl;
        std::cout << "Time to process a range of " << (argc - 1) << " elements with std::vector : " << final << " us" << std::endl;
    }
    else
    {
        std::cout << "Time to process a range of " << (argc - 1) << " elements with std::deque : " << final << " us" << std::endl;
    }
}

int main(int argc, char **argv)
{
    int     is_odd = 0;
    int     last_nbr = 0;

    if (argc < 2)
    {
        std::cerr << "Error: Wrong number of arguments." << std::endl;
        exit (1);
    }

    // check if the input is odd
    // and if it is in a legit format.
    if ((argc - 1) % 2 != 0)
    {
        is_odd = 1;
        for (int j = 0; argv[argc - 1][j]; j++)
        {
            if (!std::isdigit(argv[argc - 1][j]))
            {
                std::cerr << "Error" << std::endl;
                exit (1);
            }
        }
        last_nbr = std::atoi(argv[argc - 1]);
    }

    int i = 1;

    // check if all the inputs are valid:
    // no other than digit
    while (i < (argc))
    {
        for (int j = 0; argv[i][j]; j++)
        {
            if (!std::isdigit(argv[i][j]))
            {
                std::cerr << "Error" << std::endl;
                exit (1);
            }
        }
        i++;
    }

    // Check if no nbr go out ouf int bounds.
    for (int i = 1; i < argc; i++)
    {
        if (atoll(argv[i]) > INT_MAX)
        {
           std::cerr << "Error: The value is outside integer limits." << std::endl;
           exit(1);
        }
    }

    std::cout << "Before:  ";

    // If five elements or less : u display the fives
    if ((argc - 1) < 6)
    {
        for (int i = 1; i < argc; i++)
        {
            std::cout << argv[i] << " ";
        }
    }
    else
    {
        // If more you display the fourth + [...]
        for (int i = 1; i < 5; i++)
        {
            std::cout << argv[i] << " ";
        }
        std::cout << "[...]";
    }

    std::cout << std::endl;

    // Algorithm use w the first container: Vector.
        // Pair of two int
    std::vector<std::pair<int, int> > vectorContainer;
    // Put each pairs in the fresh new vector container
    for (int i = 1; i + 1 < argc; i += 2)
    {
        vectorContainer.push_back(std::make_pair(std::atoi(argv[i]), std::atoi(argv[i + 1])));
    }

    // Create two new other vectors
    std::vector<int> stockOne, stockTwo;

    // Launch the alorithm to perform the sorting
    merge_insert(argc, argv, vectorContainer, stockOne, stockTwo, VECTOR, is_odd, last_nbr);

    // Algorithm use w the second container: Deque.
        // Pair of two int
    std::deque<std::pair<int, int> > dequeContainer;
    // Put each pairs in the fresh new deque container
    for (int i = 1; i + 1 < argc; i += 2)
    {
        dequeContainer.push_back(std::make_pair(std::atoi(argv[i]), std::atoi(argv[i + 1])));
    }

    // Create two new other deques
    std::deque<int> stockMin, stockMax;

    // Launch the alorithm to perform the sorting
    merge_insert(argc, argv, dequeContainer, stockMin, stockMax, DEQUE, is_odd, last_nbr);
    return (0);
}