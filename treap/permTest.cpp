#include "permTest.h"

permTest::permTest() {}

void permTest::test(iPermutationStruct* object, int number, int rangeBegin, int rangeEnd)
{
    if (number != 0)
    {
        int randValue = rand() % (rangeEnd + 1 - rangeBegin) + rangeBegin; //ѕервое число, которое будет добавлено в структуру
        object->Insert(randValue, 0);

        int arrType[4] = {0};

        for (int i = 1; i < number; i++)
        {
            int randType;
            if (object->getLen() > 2)
                randType = rand() % 4;
            else
                randType = rand() % 2;

            arrType[randType]++;

            if (randType == 0) //Insert
            {
                randValue = rand() % (rangeEnd + 1 - rangeBegin) + rangeBegin;
                int randPos = rand() % object->getLen();
                object->Insert(randValue, randPos);
            }
            else if (randType == 1) //Assign
            {
                randValue = rand() % (rangeEnd + 1 - rangeBegin) + rangeBegin;
                int randPos = rand() % object->getLen();
                object->Assign(randValue, randPos);
            }
            else if (randType == 2) //SubsegmentSum
            {
                int randLeft = rand() % (object->getLen() - 1);
                int randRight = rand() % (object->getLen() - randLeft) + randLeft;
                object->SubsegmentSum (randLeft, randRight);
            }
            else if (randType == 3) //NextPermutaion
            {
                int randLeft = rand() % (object->getLen() - 1);
                int randRight = rand() % (object->getLen() - randLeft) + randLeft;
                object->NextPermutation (randLeft, randRight);
            }
        }
        std::cout << "Insert(): " << arrType[0] << "\nAssign(): " << arrType[1] << "\nSubsegmentSum(): " << arrType[2] << "\nNextPermutation(): " << arrType[3] << std::endl;
    }
}

void permTest::compare(iPermutationStruct* object1, iPermutationStruct* object2, int number, int rangeBegin, int rangeEnd)
{
    if (number != 0)
    {
        int randValue = rand() % (rangeEnd + 1 - rangeBegin) + rangeBegin; //ѕервое число, которое будет добавлено в структуру
        object1->Insert(randValue, 0);
        object2->Insert(randValue, 0);

        int arrType[4] = {0};

        for (int i = 1; i < number; i++)
        {
            int randType;
            if (object1->getLen() > 2)
                randType = rand() % 4;
            else
                randType = rand() % 2;

            arrType[randType]++;

            if (randType == 0) //Insert
            {
                randValue = rand() % (rangeEnd + 1 - rangeBegin) + rangeBegin;
                int randPos = rand() % object1->getLen();
                object1->Insert(randValue, randPos);
                object2->Insert(randValue, randPos);
            }
            else if (randType == 1) //Assign
            {
                randValue = rand() % (rangeEnd + 1 - rangeBegin) + rangeBegin;
                int randPos = rand() % object1->getLen();
                object1->Assign(randValue, randPos);
                object2->Assign(randValue, randPos);
            }
            else if (randType == 2) //SubsegmentSum
            {
                int randLeft = rand() % (object1->getLen() - 1);
                int randRight = rand() % (object1->getLen() - randLeft) + randLeft;
                object1->SubsegmentSum (randLeft, randRight);
                object2->SubsegmentSum (randLeft, randRight);
            }
            else if (randType == 3) //NextPermutaion
            {
                int randLeft = rand() % (object1->getLen() - 1);
                int randRight = rand() % (object1->getLen() - randLeft) + randLeft;
                object1->NextPermutation (randLeft, randRight);
                object2->NextPermutation (randLeft, randRight);
            }
        }
        std::cout << "Insert(): " << arrType[0] << "\nAssign(): " << arrType[1] << "\nSubsegmentSum(): " << arrType[2] << "\nNextPermutation(): " << arrType[3] << std::endl;
    }
}
