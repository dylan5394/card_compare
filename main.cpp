

#include "lib/TestHarness.h"
#include "lib/TestResultStdErr.h"


int main()
{   
    TestResultStdErr result;
    TestRegistry::runAllTests(result);
    return (result.getFailureCount());
}

