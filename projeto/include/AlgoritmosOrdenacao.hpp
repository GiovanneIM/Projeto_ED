#ifndef ALGORITMOS_ORDENACAO_HPP
#define ALGORITMOS_ORDENACAO_HPP

#include "Instrumentacao.hpp"
#include <vector>

class AlgoritmosOrdenacao {
  public:
    // ALGORITMOS OBRIGATÓRIOS

    /**
     * @brief Ordena um vetor usando o algoritmo Bubble Sort e armazena as métrica de execução do
     * algoritmo
     *
     * @param arr Vetor a ser ordenado
     * @param m Instância de strict Metricas para armazanar as métricas de execução do algoritmo
     */
    static void bubbleSort(std::vector<int> &arr, Metricas &m);

    /**
     * @brief Ordena um vetor usando o algoritmo Insertion Sort e armazena as métrica de execução do
     * algoritmo
     *
     * @param arr Vetor a ser ordenado
     * @param m Instância de strict Metricas para armazanar as métricas de execução do algoritmo
     */
    static void insertionSort(std::vector<int> &arr, Metricas &m);

    /**
     * @brief Ordena um vetor usando o algoritmo Selection Sort e armazena as métrica de execução do
     * algoritmo
     *
     * @param arr Vetor a ser ordenado
     * @param m Instância de strict Metricas para armazanar as métricas de execução do algoritmo
     */
    static void selectionSort(std::vector<int> &arr, Metricas &m);

    /**
     * @brief Ordena um vetor usando o algoritmo Merge Sort e armazena as métrica de execução do
     * algoritmo
     *
     * @param arr Vetor a ser ordenado
     * @param m Instância de strict Metricas para armazanar as métricas de execução do algoritmo
     */
    static void mergeSort(std::vector<int> &arr, Metricas &m);

    /**
     * @brief Ordena um vetor usando o algoritmo Quick Sort e armazena as métrica de execução do
     * algoritmo
     *
     * @param arr Vetor a ser ordenado
     * @param m Instância de strict Metricas para armazanar as métricas de execução do algoritmo
     */
    static void quickSort(std::vector<int> &arr, Metricas &m);

    /**
     * @brief Ordena um vetor usando o algoritmo Random Quick Sort e armazena as métrica de execução
     * do algoritmo
     *
     * @param arr Vetor a se ordenado
     * @param m Instância de strict Metricas para armazanar as métricas de execução do algoritmo
     */
    static void quickSortRandomizado(std::vector<int> &arr, Metricas &m);

    /**
     * @brief Ordena um vetor usando o algoritmo Heap Sort e armazena as métrica de execução do
     * algoritmo
     *
     * @param arr Vetor a se ordenado
     * @param m Instância de strict Metricas para armazanar as métricas de execução do algoritmo
     */
    static void heapSort(std::vector<int> &arr, Metricas &m);

    /**
     * @brief Ordena um vetor usando o algoritmo Shell Sort e armazena as métrica de execução do
     * algoritmo
     *
     * @param arr Vetor a se ordenado
     * @param m Instância de strict Metricas para armazanar as métricas de execução do algoritmo
     */
    static void shellSort(std::vector<int> &arr, Metricas &m);

  private:
    // FUNÇÕES AUXILIARES

    /**
     * @brief Aplica o algoritmo Merge Sort recursivamente
     *
     * Divide o vetor em subvetores menores até que cada subvetor
     * possua apenas um elemento e, em seguida, realiza a fusão
     * ordenada entre eles.
     *
     * @param arr Vetor a ser ordenado
     * @param esq Índice inicial do intervalo
     * @param dir Índice final do intervalo
     * @param aux Vetor auxiliar utilizado durante o merge
     * @param m Instância da struct Metricas para armazenar
     * as métricas de execução do algoritmo
     * @param profundidade Profundidade atual da recursão
     */
    static void mergeSortRecursivo(std::vector<int> &arr, int esq, int dir, std::vector<int> &aux,
                                   Metricas &m, int profundidade);

    /**
     * @brief Realiza a fusão de duas partes ordenadas de um vetor
     *
     * Intercala os elementos de dois subvetores ordenados em um vetor auxiliar
     * e copia o resultado novamente para o vetor original.
     *
     * Subvetor esquerdo: arr[esq..meio]
     * Subvetor direito: arr[meio+1..dir]
     *
     * @param arr Vetor original contendo os elementos
     * @param esq Índice inicial do subvetor esquerdo
     * @param meio Índice final do subvetor esquerdo
     * @param dir Índice final do subvetor direito
     * @param aux Vetor auxiliar utilizado durante a fusão
     * @param m Instância da struct Metricas para armazenar as métricas de execução do algoritmo
     */
    static void merge(std::vector<int> &arr, int esq, int meio, int dir, std::vector<int> &aux,
                      Metricas &m);

    /**
     * @brief Aplica o algoritmo Quick Sort recursivamente
     *
     * Divide o vetor em subvetores menores utilizando a técnica
     * de particionamento em torno de um pivô até que os intervalos
     * possuam tamanho 0 ou 1.
     *
     * @param arr Vetor a ser ordenado
     * @param baixo Índice inicial do intervalo
     * @param alto Índice final do intervalo
     * @param m Instância da struct Metricas para armazenar
     * as métricas de execução do algoritmo
     * @param profundidade Profundidade atual da recursão
     */
    static void quickSortRecursivo(std::vector<int> &arr, int baixo, int alto, Metricas &m,
                                   int profundidade);

    /**
     * @brief Particiona o vetor em torno de um pivô
     *
     * Utiliza o último elemento do intervalo como pivô e reorganiza
     * o vetor de forma que:
     *
     * - elementos menores ou iguais ao pivô fiquem à esquerda
     * - elementos maiores fiquem à direita
     *
     * Ao final, retorna a posição final do pivô.
     *
     * @param arr Vetor a ser particionado
     * @param baixo Índice inicial do intervalo
     * @param alto Índice final do intervalo
     * @param m Instância da struct Metricas para armazenar
     * as métricas de execução do algoritmo
     *
     * @return Índice final do pivô após a partição
     */
    static int partition(std::vector<int> &arr, int baixo, int alto, Metricas &m);

    /**
     * @brief Aplica o algoritmo Quick Sort Randomizado recursivamente
     *
     * Ordena o vetor utilizando Quick Sort com seleção aleatória
     * do pivô, reduzindo a probabilidade de ocorrência do pior caso.
     *
     * @param arr Vetor a ser ordenado
     * @param baixo Índice inicial do intervalo
     * @param alto Índice final do intervalo
     * @param m Instância da struct Metricas para armazenar
     * as métricas de execução do algoritmo
     * @param profundidade Profundidade atual da recursão
     */
    static void quickSortRecursivoRandomizado(std::vector<int> &arr, int baixo, int alto,
                                              Metricas &m, int profundidade);

    /**
     * @brief Particiona o vetor utilizando um pivô aleatório
     *
     * Seleciona aleatoriamente um elemento do intervalo como pivô,
     * move esse elemento para o final do vetor e aplica o processo
     * de particionamento.
     *
     * @param arr Vetor a ser particionado
     * @param baixo Índice inicial do intervalo
     * @param alto Índice final do intervalo
     * @param m Instância da struct Metricas para armazenar
     * as métricas de execução do algoritmo
     *
     * @return Índice final do pivô após a partição
     */
    static int partitionRandomizado(std::vector<int> &arr, int baixo, int alto, Metricas &m);

    /**
     * @brief Ajusta a propriedade de Max Heap em um subárvore
     *
     * Garante que o elemento na posição i e seus filhos satisfaçam
     * a propriedade de Max Heap, ou seja:
     *
     * - o nó pai deve ser maior ou igual aos seus filhos
     *
     * Caso necessário, realiza trocas entre elementos e aplica
     * o processo recursivamente na subárvore afetada.
     *
     * @param arr Vetor que representa o heap
     * @param n Tamanho atual do heap
     * @param i Índice do nó raiz da subárvore
     * @param m Instância da struct Metricas para armazenar
     * as métricas de execução do algoritmo
     * @param profundidade Profundidade atual da recursão
     */
    static void heapify(std::vector<int> &arr, int n, int i, Metricas &m, int profundidade);

    // UTILITÁRIOS

    /**
     * @brief Realiza a troca de dois valores
     *
     * @param a Referência à primeira variável
     * @param b Referência à segunda variável
     * @param m Instância da struct Metricas que armazena as métricas
     */
    static void swap(int &a, int &b, Metricas &m);
};

#endif