#ifndef SETCOVERPROBLEM_H
#define SETCOVERPROBLEM_H

#include <iostream>
#include <vector>
#include <minisat/core/Solver.h>

typedef std::vector<std::vector<int>> Formula;

inline bool checkFormula(const std::vector<int>& assignment, const Formula& formula) {
    for (const auto& clause : formula) {
        bool clauseSatisfied = false;

        for (int var : clause) {
            int varIndex = abs(var) - 1;
            bool value = (assignment[varIndex] == (var > 0 ? 1 : 0));
            if (value) {
                clauseSatisfied = true;
                break;
            }
        }
        if (!clauseSatisfied) {
            return false;
        }
    }
    return true;
}

inline bool solve3SAT(Minisat::Solver& solver, const Formula& formula, int numVariables, std::vector<int>& assignment) {
    std::vector<Minisat::Var> variables(numVariables);
    for (int i = 0; i < numVariables; ++i) {
        variables[i] = solver.newVar();
    }

    for (const auto& clause : formula) {
        Minisat::vec<Minisat::Lit> literals;
        for (int var : clause) {
            if (var > 0) {
                literals.push(Minisat::mkLit(variables[abs(var) - 1]));
            } else {
                literals.push(~Minisat::mkLit(variables[abs(var) - 1]));
            }
        }
        solver.addClause(literals);
    }

    if (solver.solve()) {
        for (int i = 0; i < numVariables; ++i) {
            assignment[i] = solver.modelValue(variables[i]).isTrue() ? 1 : 0;
            // std::cout << "Variable " << (i + 1) << ": " << (assignment[i] == 1 ? "True" : "False") << std::endl;
        }
        return true;
    } else
        return false;
}

#endif //SETCOVERPROBLEM_H
