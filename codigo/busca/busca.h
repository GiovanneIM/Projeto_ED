#ifndef BUSCA_H
#define BUSCA_H

#include <vector>
#include <string>
#include <random>

void bubbleSort(std::vector<int>& v);
void insertionSort(std::vector<int>& v);
void selectionSort(std::vector<int>& v);
void mergeSort(std::vector<int>& v);
void quickSort(std::vector<int>& v);
void quickSortRandom(std::vector<int>& v);
void heapSort(std::vector<int>& v);
void shellSort(std::vector<int>& v);

#endif