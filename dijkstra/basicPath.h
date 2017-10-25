#ifndef BASIC_PATH_KOSHKIN_PAVEL_493
#define BASIC_PATH_KOSHKIN_PAVEL_493

#include <iostream>

template <class T>
class basicPath
{
private:
    T pathLen;
    bool isInf;

public:
    basicPath(T inPathLen) : pathLen(inPathLen), isInf(false) {} // �����������, �������� ��� ����
    basicPath(bool inIsInf = false) : isInf(inIsInf) // ����������� ��� �������� ���� ����������� ��� ������� �����
    {
        isInf = inIsInf;
        pathLen = 0; // ���� isInf == true, �� pathLen ��� �� �����
    }

    basicPath& mergeWith (basicPath& inPath)
    {
        if (isInf || inPath.isInf)
            return *(new basicPath(true));
        else
            return *(new basicPath(pathLen + inPath.pathLen));
    }

    bool getIsInf ()
    {
        return isInf;
    }

    friend bool operator < (const basicPath& inPathLeft, const basicPath& inPathRight)
    {
        if (!inPathLeft.isInf && !inPathRight.isInf)
        {
            return (inPathLeft.pathLen < inPathRight.pathLen);
        }
        else if (!inPathLeft.isInf || !inPathRight.isInf)
        {
            if (inPathLeft.isInf)
                return false;
            else
                return true;
        }
    }

    friend std::ostream& operator << (std::ostream& outStream, basicPath& inPath)
    {
        if (!inPath.isInf)
            outStream << inPath.pathLen;
        else
            outStream << "inf";
        return outStream;
    }
};

#endif // BASIC_PATH_KOSHKIN_PAVEL_493
