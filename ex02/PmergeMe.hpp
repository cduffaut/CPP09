#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <iostream>

// isdigit func
# include <cctype>
// include for deque vector
# include <vector>
// include for deque container
// Deque will make the move in his side more faster than vector (more efficient) for the actual using
# include <deque>
// include for makepair()
# include <utility>
// include gettimeofday
# include <sys/time.h>

enum container
{
    VECTOR,
    DEQUE,
};

class PmergeMe
{
    private:

    public:
            PmergeMe();
            ~PmergeMe();
            PmergeMe (PmergeMe const &other);
            PmergeMe &operator=(PmergeMe const &other);
};

# endif