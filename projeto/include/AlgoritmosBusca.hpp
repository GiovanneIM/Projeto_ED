#ifndef ALGORITMOS_BUSCA_HPP
#define ALGORITMOS_BUSCA_HPP

#include "Instrumentacao.hpp"
#include <vector>

class AlgoritmosBusca {
  public:
    /**
     * @brief Busca um elemento alvo em um vetor, percorrendo o vetor
     *
     * @param arr Vetor em que o elemento é buscado
     * @param alvo Elemento a ser buscado no vetor
     *
     * @return Índice do elemento alvo dentro do vetor ou -1, caso o elemento não tenha sido
     * encontrado
     */
    static int buscaSequencial(const std::vector<int> &arr, int alvo);

    /**
     * @brief Busca um elemento alvo em um vetor, usando busca binária
     *
     * @param arr Vetor em que o elemento é buscado
     * @param alvo Elemento a ser buscado no vetor
     *
     * @return Índice do elemento alvo dentro do vetor ou -1, caso o elemento não tenha sido
     * encontrado
     * 
     * @note O vetor deve estar ordenado em ordem crescente.
     */
    static int buscaBinaria(const std::vector<int> &arr, int alvo);

    /**
     * @brief Busca um elemento alvo em um vetor, usando busca binária e calcula as métricas de
     * execução
     *
     * @param arr Vetor em que o elemento é buscado
     * @param alvo Elemento a ser buscado no vetor
     * @param m Instância da struct Metricas para armazenar as métricas de execução da busca
     * (acessos e comparações)
     *
     * @return Índice do elemento alvo dentro do vetor ou -1, caso o elemento não tenha sido
     * encontrado
     * 
     * @note O vetor deve estar ordenado em ordem crescente.
     */
    static int buscaBinariaInstrumentada(const std::vector<int> &arr, int alvo, Metricas &m);
};

#endif