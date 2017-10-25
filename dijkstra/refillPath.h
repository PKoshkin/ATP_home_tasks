#ifndef REFILL_PATH_KOSHKIN_PAVEL_493
#define REFILL_PATH_KOSHKIN_PAVEL_493

#include <iostream>

class refillPath
{
private:
    int cost;
    bool isInf;

public:
    refillPath(int inCost) : cost(inCost), isInf(false) {} //  онструктор, задающий все пол€
    refillPath(bool inIsInf = false) : isInf(inIsInf) //  онструктор дл€ создани€ пути бесконечной или нулевой длины
    {
        isInf = inIsInf;
        cost = 0; // ≈сли isInf == true, то pathLen уже не важна
    }

    refillPath& mergeWith (refillPath& inPath)
    {
        if (isInf || inPath.isInf)
            return *(new refillPath(true));
        else
            return *(new refillPath(cost + inPath.cost));
    }

    bool getIsInf ()
    {
        return isInf;
    }

    friend bool operator < (const refillPath& inPathLeft, const refillPath& inPathRight)
    {
        if (!inPathLeft.isInf && !inPathRight.isInf)
        {
            return (inPathLeft.cost < inPathRight.cost);
        }
        else if (!inPathLeft.isInf || !inPathRight.isInf)
        {
            if (inPathLeft.isInf)
                return false;
            else
                return true;
        }
    }

    friend std::ostream& operator << (std::ostream& outStream, refillPath& inPath)
    {
        if (!inPath.isInf)
            outStream << inPath.cost;
        else
            outStream << "inf";
        return outStream;
    }
};

#endif // REFILL_PATH_KOSHKIN_PAVEL_493
