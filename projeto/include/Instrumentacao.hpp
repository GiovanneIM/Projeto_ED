#pragma once
#include <chrono>
#include <vector>

/**
 * @brief Estrutura para armazenar métricas registradas durante a execução de um algoritmo
 */
struct Metricas {
    /// TOTAL DE COMPARAÇÕES
    long long comparacoes = 0;

    /// TOTAL DE TROCAS OU MOVIMENTAÇÕES
    long long trocas = 0;

    /// NÚMERO DE ACESSOS
    long long acessos = 0;

    /// PROFUNDIADE MÁXIMA DE RECURSÃO
    int profundidadeRecursao = 0;

    /// TEMPO DE EXECUÇÃO (Em segundos)
    double tempoSegundos = 0.0;

    /// QUANTIDADE ESTIMADA DE MEMÓRIA AUXILIAR UTILIZADA (Em bytes)
    size_t memoriaAuxiliarBytes = 0;

    /// REDEFINE OS VALORES DA MÉTRICA
    void reset()
    {
        comparacoes = 0;
        trocas = 0;
        acessos = 0;
        profundidadeRecursao = 0;
        tempoSegundos = 0.0;
        memoriaAuxiliarBytes = 0;
    }
};

class Instrumentador {
  public:
    // Incrementa o valor do número de comparações
    static void registrarComparacao(Metricas &m) { m.comparacoes++; }

    // Incrementa o valor do número de trocas
    static void registrarTroca(Metricas &m) { m.trocas++; }

    // Incrementa o valor do número de acessos
    static void registrarAcesso(Metricas &m) { m.acessos++; }

    // Incrementa o valor do número de acessos
    static void registrarAcessos(Metricas &m, int qtd) { m.acessos += qtd; }

    // Incrementa o valor da profundidade
    static void registrarProfundidade(Metricas &m, int atual) { m.profundidadeRecursao++; };

    /**
     * @brief Realiza a chamada de uma função e retorna o tempo de execução dela
     *
     * @param Func - Função a ter tempo de execução calculado
     *
     * @return Tempo de execução da função
     */
    template <typename Func> static double medirTempo(Func &&func)
    {
        // Obtendo o momento em que a função inicia
        auto inicio = std::chrono::high_resolution_clock::now();

        // Fazendo a chamada à função
        func();

        // Obtendo o momento em que a função finalizou
        auto fim = std::chrono::high_resolution_clock::now();

        // Retornando a diferença entre os tempos
        return std::chrono::duration<double>(fim - inicio).count();
    }

    template <typename Func> static Metricas executarComMetricas(Func &&func)
    {
        Metricas m;
        double tempo = medirTempo([&]() {
            func(m);
        });
        m.tempoSegundos = tempo;
        return m;
    }
};