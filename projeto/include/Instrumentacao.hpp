#pragma once
#include <chrono>
#include <vector>

/**
 * @brief Estrutura para armazenar métricas registradas durante a execução de um algoritmo
 */
struct Metricas
{
    /// Número total de comparações realizadas pelo algoritmo
    long long comparacoes = 0;

    /// Número total de trocas ou movimentações de elementos
    long long trocas = 0;

    /// Número de acessos ao vetor de dados
    long long acessos = 0;

    /// Profundidade máxima atingida pela recursão (quando houver)
    int profundidadeRecursao = 0;

    /// Tempo total de execução do algoritmo, em segundos
    double tempoSegundos = 0.0;

    /// Quantidade estimada de memória auxiliar utilizada, em bytes
    size_t memoriaAuxiliarBytes = 0;

    /// Redefine os valores das métricas
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

class Instrumentador
{
public:
    static void registrarComparacao(Metricas &m) { m.comparacoes++; }
    static void registrarTroca(Metricas &m) { m.trocas++; }
    static void registrarAcesso(Metricas &m) { m.acessos++; }
    static void registrarAcessos(Metricas &m, int qtd) { m.acessos += qtd; }
    static void registrarProfundidade(Metricas &m, int atual) { m.profundidadeRecursao++; };

    template <typename Func>
    static double medirTempo(Func &&func)
    {
        auto inicio = std::chrono::high_resolution_clock::now();
        func();
        auto fim = std::chrono::high_resolution_clock::now();
        return std::chrono::duration<double>(fim - inicio).count();
    }

    template <typename Func>
    static Metricas executarComMetricas(Func &&func)
    {
        Metricas m;
        double tempo = medirTempo([&]()
                                  { func(m); });
        m.tempoSegundos = tempo;
        return m;
    }
};