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
};

class Instrumentador
{
public:
    static void reset(Metricas &m);
    static void registrarComparacao(Metricas &m);
    static void registrarTroca(Metricas &m);
    static void registrarAcesso(Metricas &m);
    static void registrarProfundidade(Metricas &m, int atual);

    template <typename Func>
    static double medirTempo(Func &&func)
    {
        auto inicio = std::chrono::high_resolution_clock::now();
        func();
        auto fim = std::chrono::high_resolution_clock::now();
        return std::chrono::duration<double>(fim - inicio).count();
    }
};