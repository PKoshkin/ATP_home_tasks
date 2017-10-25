#ifndef BUS_PATH_KOSHKIN_PAVEL_493
#define BUS_PATH_KOSHKIN_PAVEL_493

#include <iostream>

class busPath
{
private:
    int timeIn;
    int timeOut;
    bool isInf;

public:
    busPath(int inTimeIn, int inTimeOut) : timeIn(inTimeIn), timeOut(inTimeOut), isInf(false) {} //  онструктор, задающий все пол€
    busPath(bool inIsInf = false) : isInf(inIsInf) //  онструктор дл€ создани€ пути бесконечной или нулевой длины
    {
        isInf = inIsInf;
        timeIn = 0; // ≈сли isInf == true, то time уже не важны
        timeOut = 0;
    }

    busPath& mergeWith (busPath& inPath)
    {
        if ( (isInf || inPath.isInf) || (timeOut > inPath.timeIn) )
            return *(new busPath(true));
        else
            return *(new busPath(timeIn, inPath.timeOut));
    }

    bool getIsInf ()
    {
        return isInf;
    }

    friend bool operator < (const busPath& inPathLeft, const busPath& inPathRight)
    {
        if (!inPathLeft.isInf && !inPathRight.isInf)
        {
            return (inPathLeft.timeOut < inPathRight.timeOut);
        }
        else if (!inPathLeft.isInf || !inPathRight.isInf)
        {
            if (inPathLeft.isInf)
                return false;
            else
                return true;
        }
    }

    friend std::ostream& operator << (std::ostream& outStream, busPath& inPath)
    {
        if (!inPath.isInf)
            outStream << inPath.timeOut;
        else
            outStream << "inf";
        return outStream;
    }
};

#endif // BUS_PATH_KOSHKIN_PAVEL_493
