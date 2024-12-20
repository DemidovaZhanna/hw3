#ifndef COMBINED3SAT_H
#define COMBINED3SAT_H

#include <vector>
#include <cmath>
#include <cstdlib>
#include <random>

typedef std::vector<std::vector<int>> Formula;

inline int fitness(const Formula& formula, const std::vector<int>& assignment) {
    int satisfied = 0;
    for (const auto& clause : formula) {
        for (int var : clause) {
            int index = abs(var) - 1;
            if ((var > 0 && assignment[index] == 1) || (var < 0 && assignment[index] == 0)) {
                satisfied++;
                break;
            }
        }
    }
    return satisfied;
}

inline void greedyInitialization(const Formula& formula, int numVariables, std::vector<int>& assignment, std::mt19937& gen) {
    assignment.resize(numVariables);
    std::uniform_int_distribution<> dist(0, 1);
    for (int i = 0; i < numVariables; ++i) {
        assignment[i] = dist(gen);
    }
    for (const auto& clause : formula) {
        for (int var : clause) {
            int index = abs(var) - 1;
            if ((var > 0 && assignment[index] == 0) || (var < 0 && assignment[index] == 1)) {
                assignment[index] = (var > 0 ? 1 : 0);
                break;
            }
        }
    }
}

inline void localSearch(const Formula& formula, int numVariables, std::vector<int>& assignment) {
    bool improved = true;
    while (improved) {
        improved = false;
        int currentFitness = fitness(formula, assignment);
        for (int i = 0; i < numVariables; ++i) {
            assignment[i] = 1 - assignment[i];
            int newFitness = fitness(formula, assignment);
            if (newFitness > currentFitness) {
                improved = true;
                currentFitness = newFitness;
            } else {
                assignment[i] = 1 - assignment[i];
            }
        }
    }
}

inline void monteCarlo(int numVariables, std::vector<int>& assignment, int iterations,
                       double probability, std::mt19937& gen) {
    std::uniform_int_distribution<> dist(0, numVariables - 1);
    std::uniform_real_distribution<> probDist(0.0, 1.0);

    for (int it = 0; it < iterations; ++it) {
        if (probDist(gen) < probability) {
            int varToFlip = dist(gen);
            assignment[varToFlip] = 1 - assignment[varToFlip];
        }
    }
}

inline void simulatedAnnealing(const Formula& formula, int numVariables, std::vector<int>& assignment,
                               int iterations, double initialTemp, double coolingRate, std::mt19937& gen) {
    std::uniform_int_distribution<> dist(0, numVariables - 1);
    std::uniform_real_distribution<> probDist(0.0, 1.0);

    double temperature = initialTemp;
    int currentFitness = fitness(formula, assignment);

    for (int it = 0; it < iterations; ++it) {
        int varToFlip = dist(gen);
        assignment[varToFlip] = 1 - assignment[varToFlip];
        int newFitness = fitness(formula, assignment);

        if (newFitness >= currentFitness || exp((newFitness - currentFitness) / temperature) > probDist(gen)) {
            currentFitness = newFitness;
        } else {
            assignment[varToFlip] = 1 - assignment[varToFlip];
        }

        temperature *= coolingRate;
    }
}

inline bool solve3SATCombined(const Formula& formula, int numVariables, std::vector<int>& assignment) {
    std::random_device rd;
    std::mt19937 gen(rd());

    greedyInitialization(formula, numVariables, assignment, gen);
    localSearch(formula, numVariables, assignment);
    monteCarlo(numVariables, assignment, 100, 0.1, gen);
    simulatedAnnealing(formula, numVariables, assignment, 500, 100.0, 0.95, gen);

    return fitness(formula, assignment) == formula.size();
}

inline Formula generateRandom3SAT(int numVariables, int numClauses) {
    Formula formula;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, numVariables);
    std::uniform_int_distribution<> signDist(0, 1);

    for (int i = 0; i < numClauses; ++i) {
        std::vector<int> clause;
        for (int j = 0; j < 3; ++j) {
            int var = dist(gen);
            if (signDist(gen) == 0) var = -var;
            clause.push_back(var);
        }
        formula.push_back(clause);
    }
    return formula;
}

#endif //COMBINED3SAT_H
