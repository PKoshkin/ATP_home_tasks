#include <iostream>
#include <stdlib.h>
#include "alcsn2.h"
#include "alcsn3.h"

bool test (int** matrix1, int** matrix2, int size) // Сравниваем две матрицы. Одинаковые ли они.
{
    for (int i = 0; i < size + 1; i++)
        for (int j = 0; j < size + 1; j++)
            if (matrix2[i][j] != matrix1[i][j]) // Просто проверям все элементы в матрицах
                return false;

    return true;
}

int main ()
{
/*
    std::string str1 = "yxxyzyzx";
    std::string str2 = "yxxyzxyzxyxzx";

    int size = str2.size();

    int** resMatrix = new int*[size + 1];
    for (int i = 0; i < size + 1 + 1; i++)
        resMatrix[i] = new int [size + 1];

    ALCSP_N2 (resMatrix, str2, str1);

    for (int i = 0; i < size + 1; i++)
    {
        for (int j = 0; j < size + 1; j++)
            std::cout << resMatrix[i][j] << " ";
        std::cout << std::endl;
    }
    return 0;
*/
    for (int alphabetSize = 2; alphabetSize <= 130; (alphabetSize < 10) ? (++alphabetSize) : (alphabetSize += 20)) // Протестируем с алфавитом разного размера
    {
        std::cout << "test with alphabet size " << alphabetSize;
        for (int i = 0; i < 1000; i++)
        {
            // Сделаем 2 строки с рандомными размерами
            int size1 = rand() % 100;
            int size2 = rand() % 100;
            std::string str1, str2;

            // Понатыкаем в них случайных символов из алфавита
            for (int n = 0; n < size1; n++)
                str1.push_back(rand() % alphabetSize);
            for (int m = 0; m < size2; m++)
                str2.push_back(rand() % alphabetSize);

            // Выделяем память под ответы
            int** resMatrix1 = new int*[size1 + 1];
            int** resMatrix2 = new int*[size1 + 1];
            for (int i = 0; i < size1 + 1; i++)
            {
                resMatrix1[i] = new int [size1 + 1];
                resMatrix2[i] = new int [size1 + 1];
            }

            // Ищем ALCS за O(N^2) и за O(N^3)
            ALCSP_N3 (resMatrix1, str1, str2);
            ALCSP_N2 (resMatrix2, str1, str2);

            // Собственно - тест. Сравниваем матрицы, полученные за O(N^2) и за O(N^3)
            if (!test(resMatrix1, resMatrix2, size1))
            {
                // Если что-то плохо, говорим об этом
                std::cout << "NOT PASSED WITH \"" << str1 << "\" AND \"" << str2 << std::endl;
                return 0;
            }

            // Очищаем память
            for (int i = 0; i < size1 + 1; i++)
            {
                delete[] resMatrix1[i];
                delete[] resMatrix2[i];
            }
            delete[] resMatrix1;
            delete[] resMatrix2;
        }
        std::cout << " has been passed" << std::endl;
    }
    std::cout << "ALL TESTS HAVE BEEN PASSED" << std::endl;
    return 0;
}
