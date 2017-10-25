#include "alcsn3.h"

void APLCS (int** resMatrix, std::string str1, size_t begin1, size_t end1, std::string str2, size_t begin2, size_t end2)
{
    int matrix[end1 - begin1 + 2][end2 - begin2 + 2]; // Временная матрица для построения ответа

    for (size_t i = 0; i < begin1; i++) // Заполним нулями начало строки
        resMatrix[begin1][i] = 0;

    // Считаем обычную динамику за O(N^2)
    for (size_t i = 0; i <= end1 - begin1 + 1; i++)
    {
        for (size_t j = 0; j <= end2 - begin2 + 1; j++)
        {
            if ((j == 0) || (i == 0))
                matrix[i][j] = 0;
            else if (str1[begin1 + i - 1] == str2[begin2 + j - 1])
                matrix[i][j] = matrix[i - 1][j - 1] + 1;
            else if (matrix[i - 1][j] > matrix[i][j - 1])
                matrix[i][j] = matrix[i - 1][j];
            else
                matrix[i][j] = matrix[i][j - 1];
        }

        // Последняя строчка динамики - строчка из искомой матрицы
        resMatrix[begin1][i + begin1] = matrix[i][end2 - begin2 + 1];
    }
}

void ALCSP_N3 (int** resMatrix, std::string str1, std::string str2)
{
    // Ответ будем получать построчесно
    for (size_t k = 0; k <= str1.size(); ++k)
        APLCS(resMatrix, str1, k, str1.size() - 1, str2, 0, str2.size() - 1);
}
