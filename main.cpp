#include <iostream>
#include "3SAT.h"

int main()
{
    SetCoverProblem problem;

    problem.universe = {1, 2, 3};
    problem.subsets = {{1, 2}, {2, 3}, {1, 3}};
    problem.costs = {2, 3, 1};

    solveSetCover(problem);
    return 0;
}

