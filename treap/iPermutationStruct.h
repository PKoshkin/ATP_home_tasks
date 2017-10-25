#ifndef IPERMUTATIONSTRUCT_PAVEL_KOSHKIN_493
#define IPERMUTATIONSTRUCT_PAVEL_KOSHKIN_493

#include <stdlib.h> // Äëÿ size_t



class iPermutationStruct
{
public:
    virtual void Insert (int value, size_t index) = 0;
    virtual void Assign (int value, size_t index) = 0;
    virtual long long SubsegmentSum (size_t left, size_t right) = 0;
    virtual void NextPermutation (size_t left, size_t right) = 0;

    virtual int getLen() = 0;
};



#endif // IPERMUTATIONSTRUCT_PAVEL_KOSHKIN_493
