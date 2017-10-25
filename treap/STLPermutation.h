#ifndef STLPERMUTATION_KOSHKIN_PAVEL_493
#define STLPERMUTATION_KOSHKIN_PAVEL_493

#include "iPermutationStruct.h"

#include <vector>
#include <algorithm>
#include <iostream>


class STLPermutation : public virtual iPermutationStruct
{
public:
    std::vector<int> vec;

    STLPermutation();
    STLPermutation(int* arr, int size);
    friend std::ostream& operator << (std::ostream& out, STLPermutation& inSTLPerm);

    virtual void Insert (int value, size_t index);
    virtual void Assign (int value, size_t index);
    virtual long long SubsegmentSum (size_t left, size_t right);
    virtual void NextPermutation (size_t left, size_t right);

    virtual int getLen();
};



#endif // STLPERMUTATION_KOSHKIN_PAVEL_493
