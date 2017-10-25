#include "STLPermutation.h"



STLPermutation::STLPermutation ()
{}

STLPermutation::STLPermutation (int* arr, int size)
{
    for (int i = 0; i < size; i++)
        vec.push_back(arr[i]);
}



std::ostream& operator << (std::ostream& out, STLPermutation& inSTLPerm) // Перегрузка оператора для вывода в поток
{
    std::vector<int>::iterator it = inSTLPerm.vec.begin();
    while (it != inSTLPerm.vec.end())
    {
        out << *it << std::endl;
        it++;
    }
    return out;
}



void STLPermutation::Insert (int value, size_t index)
{
    std::vector<int>::iterator pos = vec.begin() + index;
    vec.insert(pos, value);
}



void STLPermutation::Assign (int value, size_t index)
{
    vec[index] = value;
}



long long STLPermutation::SubsegmentSum (size_t left, size_t right)
{
    long long sum = 0;
    for (int i = left; i <= right; i++)
        sum += vec[i];
    return sum;
}



void STLPermutation::NextPermutation (size_t left, size_t right)
{
    std::next_permutation(vec.begin() + left, vec.begin() + right + 1);
}



int STLPermutation::getLen()
{
    return vec.size();
}
