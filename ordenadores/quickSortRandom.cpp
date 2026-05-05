#include "geradores.h"

int partition(std::vector<int>& v, int l, int r) {
    int pivo = v[r];
    int i = l - 1;

    for (int j = l; j < r; j++) {
        if (v[j] < pivo) {
            i++;
            std::swap(v[i], v[j]);
        }
    }

    std::swap(v[i + 1], v[r]);
    return i + 1;
}

int partitionRandom(std::vector<int>& v, int l, int r, std::mt19937& gen) {
    std::uniform_int_distribution<> dist(l, r);
    int randomIndex = dist(gen);

    std::swap(v[randomIndex], v[r]);

    return partition(v, l, r);
}

void quickSortRandom(std::vector<int>& v, int l, int r, std::mt19937& gen) {
    if (l < r) {
        int pi = partitionRandom(v, l, r, gen);

        quickSortRandom(v, l, pi - 1, gen);
        quickSortRandom(v, pi + 1, r, gen);
    }
}