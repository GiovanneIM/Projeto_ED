#ifndef BENCHMARK_COMPLETO_HPP
#define BENCHMARK_COMPLETO_HPP

#include "AlgoritmosBusca.hpp"
#include "AlgoritmosOrdenacao.hpp"
#include "Instrumentacao.hpp"
#include <chrono>
#include <map>
#include <string>
#include <vector>

// Estrutura para armazenar resultados de ordenação
struct ResultadoOrdenacao {
    std::string nomeAlgoritmo;
    long long comparacoes = 0;
    long long trocas = 0;
    long long acessos = 0;
    int profundidadeRecursao = 0;
    double tempoSegundos = 0.0;
    size_t memoriaBytes = 0;
    bool ordenadoCorretamente = false;

    void fromMetricas(const Metricas &m)
    {
        comparacoes = m.comparacoes;
        trocas = m.trocas;
        acessos = m.acessos;
        profundidadeRecursao = m.profundidadeRecursao;
        tempoSegundos = m.tempo;
        memoriaBytes = m.memoriaAuxiliarBytes;
    }
};

// Estrutura para armazenar resultados de busca
struct ResultadoBuscaCompleto {
    std::string nomeAlgoritmo;
    long long comparacoes = 0;
    long long acessos = 0;
    int profundidadeRecursao = 0;
    double tempoSegundos = 0.0;
    int indiceEncontrado = -1;
    bool sucesso = false;

    void fromMetricas(const Metricas &m)
    {
        comparacoes = m.comparacoes;
        acessos = m.acessos;
        profundidadeRecursao = m.profundidadeRecursao;
    }
};

// Estatísticas das 30 execuções
template <typename T> struct EstatisticasExecucao {
    T media;
    T desvioPadrao;
    T minimo;
    T maximo;
    T mediana;
    double coeficienteVariacao; // em porcentagem
    double ic95_inferior;
    double ic95_superior;

    void calcular(const std::vector<T> &dados)
    {
        if (dados.empty())
            return;

        // Ordena para mediana e min/max
        std::vector<T> sorted = dados;
        std::sort(sorted.begin(), sorted.end());

        minimo = sorted.front();
        maximo = sorted.back();
        mediana = sorted[sorted.size() / 2];

        // Média
        T soma = T();
        for (const auto &val : dados)
            soma += val;
        media = soma / dados.size();

        // Desvio padrão
        T somaQuad = T();
        for (const auto &val : dados) {
            T diff = val - media;
            somaQuad += diff * diff;
        }
        desvioPadrao = std::sqrt(somaQuad / (dados.size() - 1));

        // Coeficiente de variação (%)
        if (media != T()) {
            coeficienteVariacao = (desvioPadrao / media) * 100.0;
        } else {
            coeficienteVariacao = 0.0;
        }

        // Intervalo de confiança 95% (assumindo distribuição normal)
        double erro = 1.96 * desvioPadrao / std::sqrt(dados.size());
        ic95_inferior = media - erro;
        ic95_superior = media + erro;
    }
};

// Estrutura completa para um cenário de teste
struct CenarioTeste {
    std::string nomeCenario;
    int tamanho;
    std::vector<ResultadoOrdenacao> resultadosOrdenacao;
    std::vector<ResultadoBuscaCompleto> resultadosBusca;
};

// Configuração do benchmark
struct BenchmarkConfig {
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
    std::vector<std::string> algOrdenacao = {"BubbleSort", "InsertionSort", "SelectionSort",
                                             "MergeSort",  "QuickSort",     "QuickSortRandomizado",
                                             "HeapSort",   "ShellSort"};

    // Algoritmos de busca a serem testados
    std::vector<std::string> algBusca = {"BuscaSequencial", "BuscaBinaria",
                                         "BuscaBinariaInstrumentada"};

    // Ativa/desativa verificações
    bool verificarOrdenacao = true;
    bool salvarResultadosEmArquivo = true;
    std::string arquivoResultados = "resultados_benchmark.txt";
};

class BenchmarkCompleto {
  public:
    BenchmarkCompleto(const BenchmarkConfig &config = BenchmarkConfig());

    // Executa o benchmark completo
    void executarBenchmark();

    // Gera relatório completo
    void gerarRelatorio(const std::string &arquivo = "relatorio_benchmark.txt");

    // Exporta dados para CSV (para gráficos)
    void exportarCSV(const std::string &prefixo = "dados");

  private:
    BenchmarkConfig config;

    // Estrutura de dados para armazenar todos os resultados
    // [cenario][algoritmo][tamanho] = vetor de resultados das repetições
    std::map<std::string, std::map<std::string, std::map<int, std::vector<ResultadoOrdenacao>>>>
        resultadosOrdenacao;
    std::map<std::string, std::map<std::string, std::map<int, std::vector<ResultadoBuscaCompleto>>>>
        resultadosBusca;

    // Estatísticas computadas
    std::map<std::string, std::map<std::string, std::map<int, EstatisticasExecucao<double>>>>
        statsTempo;
    std::map<std::string, std::map<std::string, std::map<int, EstatisticasExecucao<long long>>>>
        statsComparacoes;
    std::map<std::string, std::map<std::string, std::map<int, EstatisticasExecucao<long long>>>>
        statsAcessos;

    // Funções de execução dos algoritmos
    ResultadoOrdenacao executarOrdenacao(const std::string &algoritmo, std::vector<int> &dados);
    ResultadoBuscaCompleto executarBusca(const std::string &algoritmo,
                                         const std::vector<int> &dados, int alvo);

    // Geração de dados para cada cenário
    std::vector<int> gerarDados(const std::string &cenario, int tamanho);

    // Funções estatísticas
    template <typename T> EstatisticasExecucao<T> computarEstatisticas(const std::vector<T> &dados);

    template <typename T> T computarMediana(std::vector<T> dados);

    // Verificação de corretude
    bool vetorOrdenado(const std::vector<int> &arr);
    bool vetorIdentico(const std::vector<int> &original, const std::vector<int> &ordenado);

    // Progresso
    void mostrarProgresso(int atual, int total, const std::string &mensagem);

    // Comparação com std::sort
    ResultadoOrdenacao stdSort(std::vector<int> &dados);
    ResultadoOrdenacao stdStableSort(std::vector<int> &dados);
};

#endif