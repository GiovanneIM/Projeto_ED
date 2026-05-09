#ifndef BENCHMARK_HPP
#define BENCHMARK_HPP

#include "AlgoritmosBusca.hpp"
#include "Estatisticas.hpp"
#include "Instrumentacao.hpp"
#include <map>
#include <string>
#include <vector>

// Configurações dos Testes
struct Config {
    // Seed fixa para reprodutibilidade
    unsigned int seed = 42;

    // Número de repetições por configuração
    int repeticoes = 30;

    // Tamanhos dos vetores (escala obrigatória)
    std::vector<int> tamanhos = {1000, 5000, 10000, 50000, 100000, 500000, 1000000};

    // Cenários de dados
    std::vector<std::string> cenarios = {
        "Aleatorio", "Ordenado", "Reverso", "ParcialmenteOrdenado", "AltaRepeticao", "QuaseReal"};

    // Algoritmos de ordenação a serem testados
    std::map<std::string, void (*)(std::vector<int> &, Metricas &)> algOrdenacao = {
        {"BubbleSort", AlgoritmosOrdenacao::bubbleSort},
        {"InsertionSort", AlgoritmosOrdenacao::insertionSort},
        {"SelectionSort", AlgoritmosOrdenacao::selectionSort},
        {"MergeSort", AlgoritmosOrdenacao::mergeSort},
        {"QuickSort", AlgoritmosOrdenacao::quickSort},
        {"QuickSortRandomizado", AlgoritmosOrdenacao::quickSortRandomizado},
        {"HeapSort", AlgoritmosOrdenacao::heapSort},
        {"ShellSort", AlgoritmosOrdenacao::shellSort}};

    // Algoritmos de busca a serem testados
    std::vector<std::string> algBusca = {"BuscaSequencial", "BuscaBinaria",
                                         "BuscaBinariaInstrumentada"};
};

class Benchmark {
  public:
    static Config config;

    template <typename Gerador, typename Algoritmo>
    static std::vector<Metricas> realizarTeste(Gerador &&gerarCenario, Algoritmo &&algoritmo)
    {
        // VETOR PARA ARMAZENAR AS MÉTRICAS DE EXECUÇÃO DE CADA TESTE
        std::vector<Metricas> metricasExecucoes;
        metricasExecucoes.reserve(config.repeticoes);

        // REALIZANDO OS TESTES
        for (int i = 0; i < config.repeticoes; ++i) {
            // GERA UM NOVO VETOR PARA CADA EXECUÇÃO
            std::vector<int> vetor = gerarCenario();

            // MÉTRICAS PARA A EXECUÇÃO
            Metricas m{};

            // MEDE O TEMPO DO ALGORITMO
            m.tempo = Instrumentador::medirTempo([&] {
                algoritmo(vetor, m);
            });

            // GUARDANDO AS INFORMAÇÕES
            metricasExecucoes.push_back(m);
        }

        return metricasExecucoes;
    };
};
#endif