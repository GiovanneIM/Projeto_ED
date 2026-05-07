#ifndef ALGORITMOS_BUSCA_HPP
#define ALGORITMOS_BUSCA_HPP

#include <vector>
#include "Instrumentacao.hpp"

// Estrutura especializada para busca binária instrumentada
struct MetricasBuscaBinaria {
    long long comparacoes = 0;
    long long acessos = 0;
    int iteracoes = 0;
    double tempoSegundos = 0.0;
    
    void reset() {
        comparacoes = 0;
        acessos = 0;
        iteracoes = 0;
        tempoSegundos = 0.0;
    }
};

class AlgoritmosBusca {
public:
    // Busca sequencial (já com instrumentação nas métricas padrão)
    static int buscaSequencial(const std::vector<int>& arr, int alvo, Metricas& m);
    
    // Busca binária clássica (retorna índice, usa métricas padrão)
    static int buscaBinaria(const std::vector<int>& arr, int alvo, Metricas& m);
    
    // Busca binária instrumentada (registra comparações e acessos detalhadamente)
    static int buscaBinariaInstrumentada(const std::vector<int>& arr, int alvo, MetricasBuscaBinaria& m);
    
    // Versão recursiva da busca binária (para análise de profundidade)
    static int buscaBinariaRecursiva(const std::vector<int>& arr, int alvo, Metricas& m);
    
    // Busca sequencial com sentinela (otimização)
    static int buscaSequencialSentinela(std::vector<int>& arr, int alvo, Metricas& m);
    
    // Busca ternária (para comparação)
    static int buscaTernaria(const std::vector<int>& arr, int alvo, Metricas& m);
    
    // Funções auxiliares para testes
    static bool vetorOrdenado(const std::vector<int>& arr);
    static void ordenarVetor(std::vector<int>& arr, Metricas& m); // usando Insertion Sort para pequenos vetores
    
private:
    // Função auxiliar recursiva para busca binária
    static int buscaBinariaRecursivaAux(const std::vector<int>& arr, int esq, int dir, int alvo, Metricas& m, int& profundidade);
};

#endif