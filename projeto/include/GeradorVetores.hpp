#pragma once
#include <vector>
#include <random>

class GeradorVetores
{
public:
    /**
     * @brief Define a seed de aleatorização usada por todas as funções da classe.
     *
     * @param seed Seed usada para geração dos valores
     */
    static void setSeed(unsigned seed);

    /**
     * @brief Gera um vetor com valores aleatorizados
     *
     * @param n Tamanho do vetor a ser gerado
     * @param min Valor mínimo possível do vetor
     * @param max Valor máximo possível do vetor
     *
     * @return Vetor de inteiros aleatorizados
     */
    static std::vector<int> aleatorio(size_t n, int min = 0, int max = 1000000);

    /**
     * @brief Gera um vetor com valores ordenados em ordem crescente
     *
     * @param n Tamanho do vetor a ser gerado
     * 
     * @return Vetor de inteiros não negativos ordenados em ordem crescente
     */
    static std::vector<int> ordenado(size_t n);

    /**
     * @brief Gera um vetor com valores ordenados em ordem decrescente
     *
     * @param n Tamanho do vetor a ser gerado
     * 
     * @return Vetor de inteiros não negativos ordenados em ordem decrescente
     */
    static std::vector<int> reverso(size_t n);

    /**
     * @brief Gera um vetor com valores parcialmente ordenados
     *
     * @param n Tamanho do vetor a ser gerado
     * @param fracOrdenado Fração correspondente à parte ordenada do vetor
     * 
     * @return Vetor de inteiros não negativos parcialmente ordenados
     */
    static std::vector<int> parcialmenteOrdenado(size_t n, double fracOrdenado = 0.8);

    /**
     * @brief Gera um vetor com alta repetição de valores
     *
     * @param n Tamanho do vetor a ser gerado
     * @param max Valor máximo dos dados do vetor
     * 
     * @return Vetor de inteiros não negativos com alto índice de repetição
     */
    static std::vector<int> altaRepeticao(size_t n, int max = 100);

    /**
     * @brief Gera um vetor com valores aleatórios seguindo uma distribuição normal (gaussiana).
     *
     * @param n Tamanho do vetor a ser gerado
     * @param media Média da distribuição
     * @param desvio Desvio padrão da distribuição
     *
     * @return Vetor de inteiros não negativos baseados em uma distribuição normal
     */
    static std::vector<int> gaussiano(size_t n, double media = 500000, double desvio = 150000);
};