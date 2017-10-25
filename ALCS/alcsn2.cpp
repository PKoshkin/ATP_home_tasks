#include "alcsn2.h"
#include <vector>

const size_t INF = 1000000000;

void ALCSP_N2 (int** resMatrix, std::string str1, std::string str2)
{
    size_t n = std::max(str2.size(), str1.size()) + 1;
    std::vector< std::vector<size_t> > ih(n, std::vector<size_t>(n));
    std::vector< std::vector<size_t> > iv(n, std::vector<size_t>(n));
    std::vector<size_t> VG(n);
    std::vector<size_t> DG0(n); // ѕерва€ строчка D

/*
    ih[l][j]:
    1) if exist i: C(l)[i][j] = Cl[i][j - 1] + 1
        ih[l][j] = min i
    2) else ih[l][j] = j

    iv[l][j] = min i: C(l - 1)[i][j] = Cl[i][j] - Ќужен чтобы посчитать ih

    ¬ этих определени€х C(l)[i][j] - самый длинный пусть в графе между вершинами (0, i) и (l, j)

    ih нужен, чтобы посчитать VG и первую строку D
*/

    for (size_t j = 0; j <= str1.size(); ++j)
        ih[0][j] = j;

    for (size_t l = 0; l <= str2.size(); ++l)
        iv[l][0] = 0;

    for (size_t l = 1; l <= str2.size(); ++l)
    {
        for (size_t j = 1; j <= str1.size(); ++j)
        {
            if (str2[l - 1] != str1[j - 1])
            {
                ih[l][j] = std::max(iv[l][j - 1], ih[l - 1][j]);
                iv[l][j] = std::min(iv[l][j - 1], ih[l - 1][j]);
            }
            else
            {
                ih[l][j] = iv[l][j - 1];
                iv[l][j] = ih[l - 1][j];
            }
        }
    }
/*
    VG - массив, где
    1) if exist = a: (a in D[i]) && !(a in D[i - 1])
        ih(i) = a
    2) else VG(i) = inf
*/
    for (size_t j = 1; j <= str1.size(); ++j)
        VG[j] = INF;

    DG0[0] = 0;
    size_t i = 1;
    for (size_t j = 1; j <= str1.size(); ++j)
    {
        if (ih[str2.size()][j] == 0)
        {
            DG0[i] = j;
            ++i;
        }
        else
        {
            VG[ih[str2.size()][j]] = j;
        }
    }

/*
    D - матрица, элементы которой удовлетвор€ют следующим услови€м:
    1) D[i][0] = i
    2) if exist j: (C[i][j] = k) && (C[i][j - 1] = k - 1)
        D[i][k] = j
    3) else D[i][k] = inf
*/

    for (size_t l = i; l <= str2.size(); ++l)
        DG0[l] = INF;
    std::vector<std::vector<size_t> > D(n, std::vector<size_t>(n));
    std::copy(DG0.begin(), DG0.end(), D[0].begin());

    // —читаем D
    for (size_t i = 1; i <= str1.size(); ++i)
    {
        size_t k = 1;
        for (size_t j = 0; j <= str2.size(); ++j)
        {
            size_t current = (k > str2.size() ? INF : D[i - 1][k]);
            if (VG[i] < current)
            {
                D[i][j] = VG[i];
                VG[i] = INF;
            }
            else
            {
                D[i][j] = current;
                ++k;
            }
        }
    }

    // “а сама€ матрица с ответами (по определению - самые длинные пути в графе) восстанавливаетс€ из матрицы D
    std::vector< std::vector< size_t > > C(n, std::vector<size_t>(n, 0));
    for (size_t i = 0; i <= str1.size(); ++i)
    {
        for (size_t j = 0; j <= str2.size(); ++j)
        {
            if (D[i][j] != INF)
            {
                C[i][D[i][j]] = j;
                if (D[i][j] > 0 && j > 0)
                    C[i][D[i][j] - 1] = j - 1;
            }
        }
    }
    for (size_t i = 0; i <= str1.size(); ++i)
        for (size_t j = 1; j <= str1.size(); ++j)
            C[i][j] = std::max(C[i][j], C[i][j - 1]);

    for (size_t i = 0; i <= str1.size(); ++i)
        for (size_t j = 0; j <= str1.size(); ++j)
            resMatrix[i][j] = C[i][j];
}
