#include <string>

/*
    All-substrings Longest Common Subsequence Problem by time O(N^2)
    ������� ����� ���� ���� ���������� ����� �������� ��� ������ str2 � ���� �������� str1
    ��������� ����� ������� � ������� resMatrix:
    ������� ������� resMatrix[r][l] - ����� ��� ��� ������ str2 � ��������� str1,
    ������������ � (r + 1)'�� ������� � �������������� �� l'�� �������
*/

void ALCSP_N2 (int** resMatrix, std::string str1, std::string str2);
