#ifndef BENCHMARK_HPP
#define BENCHMARK_HPP

#include <vector>
#include <string>
#include <map>
#include "AlgoritmosBusca.hpp"

struct ResultadoBusca {
    // Para busca sequencial e binária padrão
    long long comparacoes = 0;
    long long acessos = 0;
    int profundidade = 0;
    double tempo = 0.0;
    int indiceEncontrado = -1;
    
    // Para busca binária instrumentada
    long long comparacoesDetalhadas = 0;
    long long acessosDetalhados = 0;
    int iteracoes = 0;
    
    bool sucesso() const { return indiceEncontrado != -1; }
};

class BenchmarkBusca {
public:
    // Configuração do benchmark
    struct Config {
        std::vector<int> tamanhos = {1000, 5000, 10000, 50000, 100000};
        int repeticoes = 30;
        unsigned int seed = 42;
    };
    
    BenchmarkBusca(const Config& config = Config());
    
    // Executa benchmark completo
    void executarBenchmark();
    
    // Gera relatório dos resultados
    void gerarRelatorio(const std::string& arquivo = "resultados_busca.txt");
    
private:
    Config config;
    
    // Estruturas para armazenar resultados
    std::map<std::string, std::map<int, std::vector<ResultadoBusca>>> resultados;
    
    // Executa um cenário específico
    void executarCenario(const std::string& nomeCenario, std::vector<int>& vetor, int alvo);
    
    // Testa busca sequencial
    ResultadoBusca testarBuscaSequencial(const std::vector<int>& vetor, int alvo);
    
    // Testa busca binária (clássica)
    ResultadoBusca testarBuscaBinaria(const std::vector<int>& vetor, int alvo);
    
    // Testa busca binária instrumentada
    ResultadoBusca testarBuscaBinariaInstrumentada(const std::vector<int>& vetor, int alvo);
    
    // Testa busca binária recursiva
    ResultadoBusca testarBuscaBinariaRecursiva(const std::vector<int>& vetor, int alvo);
    
    // Testa busca ternária
    ResultadoBusca testarBuscaTernaria(const std::vector<int>& vetor, int alvo);
    
    // Funções estatísticas
    double calcularMedia(const std::vector<ResultadoBusca>& resultados, 
                        double (ResultadoBusca::*membro)() const);
    double calcularDesvioPadrao(const std::vector<ResultadoBusca>& resultados,
                                double (ResultadoBusca::*membro)() const);
};

#endif