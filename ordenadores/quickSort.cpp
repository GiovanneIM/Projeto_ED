#include "geradores.h"

int partition(std::vector<int> &v, int l, int r)
{
    int pivo = v[r];
    int i = l - 1;

    for (int j = l; j < r; j++)
    {
        if (v[j] < pivo)
        {
            i++;
            std::swap(v[i], v[j]);
        }
    }

    std::swap(v[i + 1], v[r]);
    return i + 1;
}

void quickSort(std::vector<int> &v, int l, int r)
{
    if (l < r)
    {
        int pi = partition(v, l, r);

        quickSort(v, l, pi - 1);
        quickSort(v, pi + 1, r);
    }
}
