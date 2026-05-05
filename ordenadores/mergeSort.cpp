#include "geradores.h"

void merge(std::vector<int>& v, int l, int m, int r) {
    std::vector<int> temp(r - l + 1);

    int i = l, j = m + 1, k = 0;

    while (i <= m && j <= r) {
        if (v[i] <= v[j]) temp[k++] = v[i++];
        else temp[k++] = v[j++];
    }

    while (i <= m) temp[k++] = v[i++];
    while (j <= r) temp[k++] = v[j++];

    for (int i = 0; i < temp.size(); i++) {
        v[l + i] = temp[i];
    }
}

void mergeSort(std::vector<int>& v, int l, int r) {
    if (l >= r) return;

    int m = (l + r) / 2;

    mergeSort(v, l, m);
    mergeSort(v, m + 1, r);
    merge(v, l, m, r);
}