#ifndef PERMTEST_PAVEL_KOSHKIN_493
#define PERMTEST_PAVEL_KOSHKIN_493

#include "iPermutationStruct.h"

#include <stdio.h>      // printf, scanf, puts, NULL
#include <stdlib.h>     // srand, rand
#include <time.h>       // time

#include <iostream>

class permTest
{
public:
    permTest();

    void test (iPermutationStruct* object, int number, int rengeBegin, int rangeEnd);
    void compare (iPermutationStruct* object1, iPermutationStruct* object2, int number, int rengeBegin, int rangeEnd);
};



#endif // PERMTEST_PAVEL_KOSHKIN_493
