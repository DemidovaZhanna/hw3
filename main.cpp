#include "test.h"

int main()
{
    TestRunner runner;
    runner.RunTest(test3SAT, "test3SAT");
    runner.RunTest(testCombined3SAT, "testCombined3SAT");

    return 0;
}

