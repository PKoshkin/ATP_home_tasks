#include <string>

/*
    All-substrings Longest Common Subsequence Problem by time O(N^3)
    Находит длины всех всех наибольших общах подстрок для строки str2 и всех подстрок str1
    Результат будет записан в матрицу resMatrix:
    Элемент матрицы resMatrix[r][l] - длина НОП для строки str2 и подстроки str1,
    начинающейся с (r + 1)'го символа и заканчивающеся на l'ом символе
*/

void ALCSP_N3 (int** resMatrix, std::string str1, std::string str2);
