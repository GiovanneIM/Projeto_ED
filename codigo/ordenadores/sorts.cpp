#include "geradores.h"

// BUBBLE SORT
void bubbleSort(std::vector<int>& v) {
    int n = v.size();

    for (int i = 0; i < n - 1; i++) {
        bool trocou = false;

        for (int j = 0; j < n - i - 1; j++) {
            if (v[j] > v[j + 1]) {
                std::swap(v[j], v[j + 1]);
                trocou = true;
            }
        }

        if (!trocou) break;
    }
}

// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

// INSERTION SORT
void insertionSort(std::vector<int>& v) {
    int n = v.size();

    for (int i = 1; i < n; i++) {
        int chave = v[i];
        int j = i - 1;

        while (j >= 0 && v[j] > chave) {
            v[j + 1] = v[j];
            j--;
        }

        v[j + 1] = chave;
    }
}

// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

// MERGE SORT
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

// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

// QUICK SORT
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


// QUICK SORT RANDOM
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

// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

// HEAP SORT
void heapify(std::vector<int>& v, int n, int i) {
    int maior = i;
    int esq = 2 * i + 1;
    int dir = 2 * i + 2;

    if (esq < n && v[esq] > v[maior])
        maior = esq;

    if (dir < n && v[dir] > v[maior])
        maior = dir;

    if (maior != i) {
        std::swap(v[i], v[maior]);
        heapify(v, n, maior);
    }
}

void heapSort(std::vector<int>& v) {
    int n = v.size();

    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(v, n, i);

    for (int i = n - 1; i > 0; i--) {
        std::swap(v[0], v[i]);
        heapify(v, i, 0);
    }
}

// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

// SHELL SORT
void shellSort(std::vector<int>& v) {
    int n = v.size();

    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = v[i];
            int j;

            for (j = i; j >= gap && v[j - gap] > temp; j -= gap) {
                v[j] = v[j - gap];
            }

            v[j] = temp;
        }
    }
}