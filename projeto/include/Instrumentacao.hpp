#ifndef INSTRUMENTACAO_HPP
#define INSTRUMENTACAO_HPP

#include <chrono>
#include <vector>

/**
 * @brief Estrutura para armazenar métricas registradas durante a execução de um algoritmo
 */
struct Metricas {
    long long comparacoes = 0;
    long long trocas = 0;
    long long acessos = 0;
    int iteracoes = 0;
    int profundidadeRecursao = 0;
    long long tempo = 0.0;
    size_t memoriaAuxiliarBytes = 0;

    /// REDEFINE OS VALORES DA MÉTRICA
    void reset()
    {
        comparacoes = 0;
        trocas = 0;
        acessos = 0;
        profundidadeRecursao = 0;
        tempo = 0.0;
        memoriaAuxiliarBytes = 0;
    }
};

class Instrumentador {
  public:
    /**
     * @brief Realiza a chamada de uma função e retorna o tempo de execução dela
     *
     * @param Func - Função a ter tempo de execução calculado
     *
     * @return Tempo de execução da função
     */
    template <typename Func> static long long medirTempo(Func &&func)
    {
        // Obtendo o momento em que a função inicia
        auto inicio = std::chrono::high_resolution_clock::now();

        // Fazendo a chamada à função
        func();

        // Obtendo o momento em que a função finalizou
        auto fim = std::chrono::high_resolution_clock::now();

        auto duracao = fim - inicio;
        auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(duracao);

        // Retornando a diferença entre os tempos
        // return std::chrono::duration<double>(fim - inicio).count();
        return ns.count();
    }
};

#endif
