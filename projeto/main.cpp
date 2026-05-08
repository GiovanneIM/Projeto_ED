
#include "./include/AlgoritmosOrdenacao.hpp"
#include "./include/Benchmark.hpp"
#include "./include/GeradorVetores.hpp"
#include "./include/Instrumentacao.hpp"
#include "Estatisticas.hpp"
#include <iomanip>
#include <iostream>

Config Benchmark::config{};

// CÓDIGO DE COMPILAÇÃO
// g++ ./main.cpp ./src/*.cpp -I ./include -o projeto_ED.exe

int teste();
int teste2();
void executarBenchmarkCompleto();

int main()
{
    // CONFIGURANDO A SEED
    GeradorVetores::setSeed(42);

    // Teste
    executarBenchmarkCompleto();
    // auto teste = GeradorVetores::aleatorio(10);
    // for (int i : teste) {
    //     std::cout << "aleatorio= " << i << "\n";
    // }

    // FINALIZANDO PROGRAMA
    return 0;
}

int teste()
{
    // GERANDO VETOR DE TESTE
    std::vector<int> dados = GeradorVetores::reverso(1000);

    // TESTANDO BUBBLE SORT
    Metricas m;                          // INSTÂNCIANDO A CLASSE MÉTRICAS
    std::vector<int> dadosCopia = dados; // CRIANDO UM VETOR COPIA

    // MEDINDO TEMPO DE EXECUÇÃO
    double tempo = Instrumentador::medirTempo([&]() {
        // ORDENANDO O VETOR
        AlgoritmosOrdenacao::heapSort(dadosCopia, m);
    });
    m.tempo = tempo;

    // EXIBINDO RESULTADOS
    std::cout << std::fixed << std::setprecision(6);
    std::cout << "Bubble Sort - 1.000 elementos:\n";
    std::cout << "  Tempo: " << m.tempo << " s\n";
    std::cout << "  Comparações: " << m.comparacoes << "\n";
    std::cout << "  Trocas: " << m.trocas << "\n";
    std::cout << "  Acessos: " << m.acessos << "\n";

    return 0;
}

int teste2()
{
    auto metricas = Benchmark::realizarTeste(
        [] {
            return GeradorVetores::ordenado(1000);
        },
        AlgoritmosOrdenacao::heapSort);

    std::cout << "Execucoes realizadas: " << metricas.size() << "\n";

    for (int i = 0; i < 3 && i < metricas.size(); ++i) {
        std::cout << "Tempo[" << i << "]: " << metricas[i].tempo << " s\n";
    }

    return 0;
}

void executarBenchmarkCompleto()
{
    // Configurações principais
    std::vector<int> tamanhos = Benchmark::config.tamanhos;
    std::vector<std::string> cenarios = {"Ordenado", "Aleatorio", "Reverso"};

    int execucoes = Benchmark::config.repeticoes;
    auto algoritmos = Benchmark::config.algOrdenacao;

    // Loop n × cenário × algoritmo
    for (int n : tamanhos) {

        for (const auto &cenario : cenarios) {

            for (const auto &[nomeAlg, funcAlg] : algoritmos) {
                std::cout << " Tamanho= " << n << " | " << "Cenario= " << cenario << " | "  << " Alg=" << nomeAlg << "\n";

                // === Gerador adaptado por lambda ===
                auto gerador = [cenario, n]() -> std::vector<int> {
                    if (cenario == "Ordenado")
                        return GeradorVetores::ordenado(n);

                    if (cenario == "Aleatorio")
                        return GeradorVetores::aleatorio(n);

                    if (cenario == "Reverso")
                        return GeradorVetores::reverso(n);

                    return GeradorVetores::aleatorio(n);
                };

                // === Executa 30 vezes ===
                std::vector<Metricas> execucoes = Benchmark::realizarTeste(gerador, funcAlg);

                // === Extrai métricas brutas ===
                std::vector<double> tempos;
                std::vector<long long> comparacoes;
                std::vector<long long> acessos;

                for (const auto &m : execucoes) {
                    tempos.push_back(m.tempo);
                    comparacoes.push_back(m.comparacoes);
                    acessos.push_back(m.acessos);
                }

                // === Calcula estatísticas ===

                AnaliseEstatistica tempoStats = Estatisticas::calcularAnaliseEstatistica(tempos);

                AnaliseEstatistica compStats =
                    Estatisticas::calcularAnaliseEstatistica(comparacoes);

                AnaliseEstatistica acessoStats = Estatisticas::calcularAnaliseEstatistica(acessos);

                // === Aqui você salva / imprime / exporta ===
                std::cout << " tempoMedio=" << tempoStats.media << "\n\n";
            }
        }
    }
}