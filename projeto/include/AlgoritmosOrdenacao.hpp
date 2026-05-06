#ifndef ALGORITMOS_ORDENACAO_HPP
#define ALGORITMOS_ORDENACAO_HPP

#include <vector>
#include "Instrumentacao.hpp"

class AlgoritmosOrdenacao
{
public:
    // Algoritmos obrigatórios
    static void bubbleSort(std::vector<int> &arr, Metricas &m);
    static void insertionSort(std::vector<int> &arr, Metricas &m);
    static void selectionSort(std::vector<int> &arr, Metricas &m);
    static void mergeSort(std::vector<int> &arr, Metricas &m);
    static void quickSort(std::vector<int> &arr, Metricas &m);
    static void quickSortRandomizado(std::vector<int> &arr, Metricas &m);
    static void heapSort(std::vector<int> &arr, Metricas &m);
    static void shellSort(std::vector<int> &arr, Metricas &m);

    // Algoritmos opcionais (bônus)
    static void countingSort(std::vector<int> &arr, Metricas &m, int maxValor = -1);
    static void radixSort(std::vector<int> &arr, Metricas &m);

private:
    // Funções auxiliares
    static void merge(std::vector<int> &arr, int esq, int meio, int dir, std::vector<int> &aux, Metricas &m);
    static void mergeSortRecursivo(std::vector<int> &arr, int esq, int dir, std::vector<int> &aux, Metricas &m, int profundidade);

    static int partition(std::vector<int> &arr, int baixo, int alto, Metricas &m);
    static int partitionRandomizado(std::vector<int> &arr, int baixo, int alto, Metricas &m);
    static void quickSortRecursivo(std::vector<int> &arr, int baixo, int alto, Metricas &m, int profundidade);

    static void heapify(std::vector<int> &arr, int n, int i, Metricas &m);

    static void countingSortPorDigito(std::vector<int> &arr, int exp, Metricas &m);

    // Utilitários
    static void swap(int &a, int &b, Metricas &m);
};

#endif