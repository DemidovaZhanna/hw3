#ifndef TEST_H
#define TEST_H

#include <sstream>
#include <iostream>
#include <string>
#include <chrono>
#include <functional>
#include <fstream>

#include "3SAT.h"
#include "combined3SAT.h"

template<class T, class U>
void AssertEqual(const T& t, const U& u, const std::string& hint)
{
    if (t != u)
    {
        std::ostringstream os;
        os << "Assertion failed: " << t << " != " << u << " hint: " << hint;
        throw std::runtime_error(os.str());
    }
}

class TestRunner
{
public:
    template <class TestFunc>
    void RunTest(TestFunc func, const std::string& test_name)
    {
        try
        {
            func();
            std::cout << test_name << " OK" << std::endl;
        } catch (std::runtime_error& e)
        {
            ++fail_count;
            std::cout << test_name << " fail: " << e.what() << std::endl;
        }
    }

    ~TestRunner()
    {
        if (fail_count > 0)
        {
            std::cout << fail_count << " unit tests failed. Terminate" << std::endl;
            exit(1);
        }
    }
private:
    int fail_count = 0;
};

template <typename Func, typename... Args>
auto measureExecutionTime(Func&& func, Args&&... args)
{
    auto start = std::chrono::high_resolution_clock::now();
    auto result = std::invoke(std::forward<Func>(func), std::forward<Args>(args)...);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Execution time: " << duration.count() << " microseconds" << std::endl;

    return result;
}

inline void test3SAT()
{
    std::cout << "The formula from test3SAT has solution:" << std::endl;
    Formula formula = {
        {1, -2, 3},   // x1 ∨ !x2 ∨ x3
        {-1, 2, 4}    // !x1 ∨ x2 ∨ x4
    };

    int numVariables = 4;
    Minisat::Solver solver;
    std::vector<int> assignment(numVariables);

    measureExecutionTime(solve3SAT, solver, formula, numVariables, assignment);
    AssertEqual(checkFormula(assignment, formula), 1, "3SAT: Formula is true");

    std::cout << "The formula from test3SAT has no solution:" << std::endl;
    Formula formulaNOT = {
        {1, 2},     // x1 ∨ x2
        {-1, 2},    // !x1 ∨ x2
        {1, -2},    // x1 ∨ !x2
        {-1, -2}    // !x1 ∨ !x2
    };
    Minisat::Solver solverNOT;
    std::vector<int> assignmentNOT(formulaNOT[0].size());

    measureExecutionTime(solve3SAT, solverNOT, formulaNOT, formulaNOT[0].size(), assignmentNOT);
    AssertEqual(checkFormula(assignmentNOT, formulaNOT), 0, "3SAT: Formula is false");
}

inline void testCombined3SAT()
{
    std::cout << "The formula from testCombined3SAT has solution:" << std::endl;
    Formula formula = {
        {1, -2, 3},   // x1 ∨ !x2 ∨ x3
        {-1, 2, 4}    // !x1 ∨ x2 ∨ x4
    };

    int numVariables = 4;
    Minisat::Solver solver;
    std::vector<int> assignment(numVariables);

    measureExecutionTime(solve3SATCombined, formula, numVariables, assignment);
    AssertEqual(checkFormula(assignment, formula), 1, "testCombined3SAT: Formula is true");

    int numVariablesGen = 5;
    int numClausesGen = 10;
    Formula formulaGen = generateRandom3SAT(numVariablesGen, numClausesGen);

    std::vector<int> assignmentGen(numVariablesGen);
    bool solved = solve3SATCombined(formulaGen, numVariablesGen, assignmentGen);

    if (solved) {
        std::cout << "The formula is satisfiable with the following assignment." << std::endl;
        // for (int i = 0; i < numVariablesGen; ++i) {
        //     std::cout << "x" << i + 1 << " = " << (assignmentGen[i] == 1 ? "True" : "False") << std::endl;
        // }
    } else {
        std::cout << "The formula is not satisfiable." << std::endl;
    }
}


#endif //TEST_H
