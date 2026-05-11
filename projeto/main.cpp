
#include "AlgoritmosOrdenacao.hpp"
#include "Benchmark.hpp"
#include "Estatisticas.hpp"
#include "GeradorVetores.hpp"
#include "Instrumentacao.hpp"
#include <iomanip>
#include <iostream>

#include <fstream>

Config Benchmark::config{};

// CÓDIGO DE COMPILAÇÃO
// g++ ./main.cpp ./src/*.cpp -I ./include -o main.exe

std::string gerarNomeArquivo();
void cabecalho(std::ofstream &arquivo);
void salvarCSV(std::ofstream &arquivo,
               int tamanho,
               const std::string &cenario,
               const std::string &algoritmo,
               const std::string &dado,
               const AnaliseEstatistica &a);
void executarBenchmark();

int main()
{
    // CONFIGURANDO A SEED
    GeradorVetores::setSeed(42);

    // EXECUTANDO OS TESTES
    executarBenchmark();

    // FINALIZANDO PROGRAMA
    return 0;
}

void executarBenchmark()
{
    // CRIANDO ARQUIVO CSV
    std::ofstream arquivo(gerarNomeArquivo());
    arquivo << std::fixed << std::setprecision(2);

    // ESCREVENDO CABEÇALHO NO ARQUIVO
    cabecalho(arquivo);

    // NÚMERO DE REPETIÇÕES
    int execucoes = Benchmark::config.repeticoes;

    // VETOR DE TAMANHOS
    std::vector<int> tamanhos = Benchmark::config.tamanhos;

    // VETOR DE CENARIOS
    std::vector<std::string> cenarios = Benchmark::config.cenarios;

    // VETOR DE ALGORIMOS DE ORDENAÇÃO
    auto algoritmos = Benchmark::config.algOrdenacao;

    // Loop n × cenário × algoritmo

    // PARA CADA TAMANHO DE VETOR
    for (int n : tamanhos) {

        // PARA CADA CENÁRIO
        for (const auto &cenario : cenarios) {

            // PARA CADA ALGORITMO
            for (const auto &[nomeAlg, funcAlg] : algoritmos) {

                // GERADOR DE DADOS
                auto gerador = [cenario, n]() -> std::vector<int> {
                    if (cenario == "Aleatorio")
                        return GeradorVetores::aleatorio(n);

                    if (cenario == "Ordenado")
                        return GeradorVetores::ordenado(n);

                    if (cenario == "Reverso")
                        return GeradorVetores::reverso(n);

                    if (cenario == "ParcialmenteOrdenado")
                        return GeradorVetores::parcialmenteOrdenado(n);

                    if (cenario == "AltaRepeticao")
                        return GeradorVetores::altaRepeticao(n);

                    return GeradorVetores::gaussiano(n);
                };

                // EXECUTANDO 30 VEZES
                std::vector<Metricas> execucoes = Benchmark::realizarTeste(gerador, funcAlg);

                // EXTRAINDO AS MÉTRICAS
                std::vector<long long> comparacoes;
                std::vector<long long> trocas;
                std::vector<long long> acessos;
                std::vector<int> profundidadesRecursao;
                std::vector<long long> tempos;
                std::vector<size_t> memoriaAux;

                for (const auto &m : execucoes) {
                    comparacoes.push_back(m.comparacoes);
                    trocas.push_back(m.trocas);
                    acessos.push_back(m.acessos);
                    profundidadesRecursao.push_back(m.profundidadeRecursao);
                    tempos.push_back(m.tempo);
                    memoriaAux.push_back(m.memoriaAuxiliarBytes);
                }

                // CALCULANDO AS ESTATISTICAS
                AnaliseEstatistica compStats = Estatisticas::calcularAnaliseEstatistica(comparacoes);
                AnaliseEstatistica trocasStats = Estatisticas::calcularAnaliseEstatistica(trocas);
                AnaliseEstatistica acessoStats = Estatisticas::calcularAnaliseEstatistica(acessos);
                AnaliseEstatistica profRecStats = Estatisticas::calcularAnaliseEstatistica(profundidadesRecursao);
                AnaliseEstatistica tempoStats = Estatisticas::calcularAnaliseEstatistica(tempos);
                AnaliseEstatistica memoriaAuxStats = Estatisticas::calcularAnaliseEstatistica(memoriaAux);

                // EXIBINDO AS ESTATISTICAS
                constexpr int W = 18;

                std::cout << std::fixed << std::setprecision(2);

                std::cout << std::string(W * 9, '=') << '\n';

                // n × cenário × algoritmo
                std::cout << n << " x " << cenario << " x " << nomeAlg << "\n";

                std::cout << std::string(W * 9, '=') << "\n\n";

                // CABEÇALHO
                std::cout
                    << std::left
                    << std::setw(W) << "DADO"

                    << std::right
                    << std::setw(W) << "MEDIA"
                    << std::setw(W) << "DESV_P"
                    << std::setw(W) << "MIN"
                    << std::setw(W) << "MAX"
                    << std::setw(W) << "MEDIANA"
                    << std::setw(W) << "CV"
                    << std::setw(W) << "IC_SUP"
                    << std::setw(W) << "IC_INF"
                    << '\n';
                std::cout << std::string(W * 9, '-') << '\n';

                Estatisticas::exibirAnaliseEstatistica("COMPARACOES", compStats);
                Estatisticas::exibirAnaliseEstatistica("TROCAS", trocasStats);
                Estatisticas::exibirAnaliseEstatistica("ACESSOS", acessoStats);
                Estatisticas::exibirAnaliseEstatistica("PROF_REC", profRecStats);
                Estatisticas::exibirAnaliseEstatistica("TEMPO(ns)", tempoStats);
                Estatisticas::exibirAnaliseEstatistica("MEM_AUX(bytes)", memoriaAuxStats);

                // SALVANDO AS ESTATISTICAS NO ARQUIVO
                salvarCSV(arquivo, n, cenario, nomeAlg, "COMPARACOES", compStats);
                salvarCSV(arquivo, n, cenario, nomeAlg, "TROCAS", trocasStats);
                salvarCSV(arquivo, n, cenario, nomeAlg, "ACESSOS", acessoStats);
                salvarCSV(arquivo, n, cenario, nomeAlg, "PROF_REC", profRecStats);
                salvarCSV(arquivo, n, cenario, nomeAlg, "TEMPO", tempoStats);
                salvarCSV(arquivo, n, cenario, nomeAlg, "MEM_AUX", memoriaAuxStats);

                std::cout << "\n";
            }
        }
    }
}

/**
 * @brief Gera um nome para um arquivo CSV baseado no dia e hora atuais
 */
std::string gerarNomeArquivo()
{
    auto agora = std::chrono::system_clock::now();

    std::time_t tempo = std::chrono::system_clock::to_time_t(agora);

    std::tm local = *std::localtime(&tempo);

    std::ostringstream oss;

    oss << "./CSV/benchmark_"
        << std::put_time(&local, "%Y-%m-%d_%H-%M-%S")
        << ".csv";

    return oss.str();
}

/**
 * @brief Função para adicionar um cabeçalho ao arquivo
 *
 * @param arquivo - Arquivo onde o cabeçalho será adicionado
 */
void cabecalho(std::ofstream &arquivo)
{
    arquivo
        << "Tamanho;"
        << "Cenario;"
        << "Algoritmo;"
        << "Dado;"
        << "Media;"
        << "DesvioPadrao;"
        << "Minimo;"
        << "Maximo;"
        << "Mediana;"
        << "CV;"
        << "IC95_Superior;"
        << "IC95_Inferior\n";
}

/**
 * @brief Função para salvar os dados de um teste no arquivo CSV
 *
 * @param arquivo - Arquivo onde os dados serão salvos
 * @param tamanho - Tamanho dos vetores no teste
 * @param algoritmo - Algorimo usado no teste
 * @param dado - Titulo do dado Ex: Tempo, Minimo etc
 * @param a - Instância da Struct AnaliseEstatistica que guarda as informações obtidas
 */
void salvarCSV(
    std::ofstream &arquivo,
    int tamanho,
    const std::string &cenario,
    const std::string &algoritmo,
    const std::string &dado,
    const AnaliseEstatistica &a)
{
    arquivo
        << tamanho << ";"
        << cenario << ";"
        << algoritmo << ";"
        << dado << ";"
        << a.media << ";"
        << a.desvioPadrao << ";"
        << a.minimo << ";"
        << a.maximo << ";"
        << a.mediana << ";"
        << a.coeficienteVariacao << ";"
        << a.ic95_superior << ";"
        << a.ic95_inferior
        << "\n";
}
