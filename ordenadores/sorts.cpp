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

        if (!trocou) break; // otimização
    }
}

// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

// 
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