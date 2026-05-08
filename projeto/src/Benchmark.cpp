#include "Benchmarck.hpp"
#include "GeradorVetores.hpp"
#include "Instrumentacao.hpp"
#include <algorithm>
#include <chrono>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <random>

BenchmarkBusca::BenchmarkBusca(const Config &config) : config(config)
{
    GeradorVetores::setSeed(config.seed);
}

ResultadoBusca BenchmarkBusca::testarBuscaSequencial(const std::vector<int> &vetor, int alvo)
{
    ResultadoBusca resultado;
    Metricas m;

    auto inicio = std::chrono::high_resolution_clock::now();
    int idx = AlgoritmosBusca::buscaSequencial(vetor, alvo);
    auto fim = std::chrono::high_resolution_clock::now();

    resultado.tempo = std::chrono::duration<double>(fim - inicio).count();
    resultado.comparacoes = m.comparacoes;
    resultado.acessos = m.acessos;
    resultado.indiceEncontrado = idx;

    return resultado;
}

ResultadoBusca BenchmarkBusca::testarBuscaBinaria(const std::vector<int> &vetor, int alvo)
{
    ResultadoBusca resultado;
    Metricas m;

    auto inicio = std::chrono::high_resolution_clock::now();
    int idx = AlgoritmosBusca::buscaBinaria(vetor, alvo);
    auto fim = std::chrono::high_resolution_clock::now();

    resultado.tempo = std::chrono::duration<double>(fim - inicio).count();
    resultado.comparacoes = m.comparacoes;
    resultado.acessos = m.acessos;
    resultado.indiceEncontrado = idx;

    return resultado;
}

ResultadoBusca BenchmarkBusca::testarBuscaBinariaInstrumentada(const std::vector<int> &vetor,
                                                               int alvo)
{
    ResultadoBusca resultado;
    MetricasBuscaBinaria m;

    auto inicio = std::chrono::high_resolution_clock::now();
    int idx = AlgoritmosBusca::buscaBinariaInstrumentada(vetor, alvo, m);
    auto fim = std::chrono::high_resolution_clock::now();

    resultado.tempo = std::chrono::duration<double>(fim - inicio).count();
    resultado.comparacoesDetalhadas = m.comparacoes;
    resultado.acessosDetalhados = m.acessos;
    resultado.iteracoes = m.iteracoes;
    resultado.indiceEncontrado = idx;

    return resultado;
}

void BenchmarkBusca::executarCenario(const std::string &nomeCenario, std::vector<int> &vetor,
                                     int alvo)
{
    std::cout << "Executando cenário: " << nomeCenario << " (n=" << vetor.size() << ")"
              << std::endl;

    for (int i = 0; i < config.repeticoes; ++i) {
        // Testa cada algoritmo
        auto resSeq = testarBuscaSequencial(vetor, alvo);
        auto resBin = testarBuscaBinaria(vetor, alvo);
        auto resBinInst = testarBuscaBinariaInstrumentada(vetor, alvo);
        auto resBinRec = testarBuscaBinariaRecursiva(vetor, alvo);
        auto resTer = testarBuscaTernaria(vetor, alvo);

        // Armazena resultados
        resultados["sequencial"][vetor.size()].push_back(resSeq);
        resultados["binaria"][vetor.size()].push_back(resBin);
        resultados["binaria_instrumentada"][vetor.size()].push_back(resBinInst);
        resultados["binaria_recursiva"][vetor.size()].push_back(resBinRec);
        resultados["ternaria"][vetor.size()].push_back(resTer);

        // Progresso
        if ((i + 1) % 10 == 0) {
            std::cout << "  Progresso: " << (i + 1) << "/" << config.repeticoes << std::endl;
        }
    }
}

void BenchmarkBusca::executarBenchmark()
{
    std::cout << "\n=== INICIANDO BENCHMARK DE BUSCA ===\n";
    std::cout << "Tamanhos: ";
    for (int n : config.tamanhos)
        std::cout << n << " ";
    std::cout << "\nRepetições por configuração: " << config.repeticoes << "\n\n";

    for (int n : config.tamanhos) {
        // Gera vetor ordenado (busca binária requer ordenação)
        std::vector<int> vetor = GeradorVetores::ordenado(n);

        // Escolhe alvos para teste:
        // 1. Elemento no início
        // 2. Elemento no meio
        // 3. Elemento no fim
        // 4. Elemento inexistente

        std::vector<int> alvos = {vetor[0], vetor[n / 2], vetor[n - 1], n + 1000};
        std::vector<std::string> descricoes = {"inicio", "meio", "fim", "inexistente"};

        for (size_t i = 0; i < alvos.size(); ++i) {
            std::string cenario = "n=" + std::to_string(n) + "_alvo=" + descricoes[i];
            executarCenario(cenario, vetor, alvos[i]);
        }
    }

    std::cout << "\n=== BENCHMARK CONCLUÍDO ===\n";
}

double BenchmarkBusca::calcularMedia(const std::vector<ResultadoBusca> &resultados,
                                     double (ResultadoBusca::*membro)() const)
{
    if (resultados.empty())
        return 0.0;
    double soma = 0.0;
    for (const auto &r : resultados) {
        soma += (r.*membro)();
    }
    return soma / resultados.size();
}

double BenchmarkBusca::calcularDesvioPadrao(const std::vector<ResultadoBusca> &resultados,
                                            double (ResultadoBusca::*membro)() const)
{
    if (resultados.size() < 2)
        return 0.0;
    double media = calcularMedia(resultados, membro);
    double somaQuad = 0.0;
    for (const auto &r : resultados) {
        double diff = (r.*membro)() - media;
        somaQuad += diff * diff;
    }
    return std::sqrt(somaQuad / (resultados.size() - 1));
}

void BenchmarkBusca::gerarRelatorio(const std::string &arquivo)
{
    std::ofstream out(arquivo);
    if (!out.is_open()) {
        std::cerr << "Erro ao abrir arquivo: " << arquivo << std::endl;
        return;
    }

    out << "========================================\n";
    out << "RELATÓRIO DE BENCHMARK - ALGORITMOS DE BUSCA\n";
    out << "========================================\n\n";

    out << "CONFIGURAÇÃO:\n";
    out << "  Seed: " << config.seed << "\n";
    out << "  Repetições: " << config.repeticoes << "\n";
    out << "  Tamanhos: ";
    for (int n : config.tamanhos)
        out << n << " ";
    out << "\n\n";

    // Tabela comparativa
    out << "RESULTADOS COMPARATIVOS (média ± desvio padrão):\n\n";

    for (int n : config.tamanhos) {
        out << "Tamanho do vetor: " << n << "\n";
        out << std::string(80, '-') << "\n";
        out << std::left << std::setw(25) << "Algoritmo" << std::right << std::setw(15)
            << "Tempo (s)" << std::setw(15) << "Comparações" << std::setw(15) << "Acessos"
            << std::setw(12) << "Profundidade" << "\n";
        out << std::string(80, '-') << "\n";

        // Pega uma amostra (primeiro cenário)
        auto &resSeq = resultados["sequencial"][n];
        auto &resBin = resultados["binaria"][n];
        auto &resBinInst = resultados["binaria_instrumentada"][n];
        auto &resBinRec = resultados["binaria_recursiva"][n];
        auto &resTer = resultados["ternaria"][n];

        if (!resSeq.empty()) {
            out << std::left << std::setw(25) << "Busca Sequencial" << std::right << std::fixed
                << std::setprecision(8) << std::setw(15)
                << calcularMedia(resSeq, &ResultadoBusca::tempo) << std::setw(15)
                << (long long)calcularMedia(resSeq, &ResultadoBusca::comparacoes) << std::setw(15)
                << (long long)calcularMedia(resSeq, &ResultadoBusca::acessos) << std::setw(12)
                << "-" << "\n";
        }

        if (!resBin.empty()) {
            out << std::left << std::setw(25) << "Busca Binária" << std::right << std::fixed
                << std::setprecision(8) << std::setw(15)
                << calcularMedia(resBin, &ResultadoBusca::tempo) << std::setw(15)
                << (long long)calcularMedia(resBin, &ResultadoBusca::comparacoes) << std::setw(15)
                << (long long)calcularMedia(resBin, &ResultadoBusca::acessos) << std::setw(12)
                << "-" << "\n";
        }

        if (!resBinInst.empty()) {
            out << std::left << std::setw(25) << "Busca Binária Instr." << std::right << std::fixed
                << std::setprecision(8) << std::setw(15)
                << calcularMedia(resBinInst, &ResultadoBusca::tempo) << std::setw(15)
                << (long long)calcularMedia(resBinInst, &ResultadoBusca::comparacoesDetalhadas)
                << std::setw(15)
                << (long long)calcularMedia(resBinInst, &ResultadoBusca::acessosDetalhados)
                << std::setw(12) << "-" << "\n";
        }

        if (!resBinRec.empty()) {
            out << std::left << std::setw(25) << "Busca Binária Recurs." << std::right << std::fixed
                << std::setprecision(8) << std::setw(15)
                << calcularMedia(resBinRec, &ResultadoBusca::tempo) << std::setw(15)
                << (long long)calcularMedia(resBinRec, &ResultadoBusca::comparacoes)
                << std::setw(15) << (long long)calcularMedia(resBinRec, &ResultadoBusca::acessos)
                << std::setw(12)
                << (long long)calcularMedia(resBinRec, &ResultadoBusca::profundidade) << "\n";
        }

        if (!resTer.empty()) {
            out << std::left << std::setw(25) << "Busca Ternária" << std::right << std::fixed
                << std::setprecision(8) << std::setw(15)
                << calcularMedia(resTer, &ResultadoBusca::tempo) << std::setw(15)
                << (long long)calcularMedia(resTer, &ResultadoBusca::comparacoes) << std::setw(15)
                << (long long)calcularMedia(resTer, &ResultadoBusca::acessos) << std::setw(12)
                << "-" << "\n";
        }

        out << "\n";
    }

    // Análise de eficiência
    out << "\nANÁLISE DE EFICIÊNCIA:\n";
    out << "========================================\n";
    out << "A busca binária (O(log n)) é significativamente mais eficiente que\n";
    out << "a busca sequencial (O(n)) para vetores grandes.\n\n";

    out << "Busca Binária Instrumentada:\n";
    out << "  - Registra número exato de comparações e acessos por iteração\n";
    out << "  - Número de iterações ≈ log2(n)\n";
    out << "  - Para n=1.000.000, log2(1.000.000) ≈ 20 iterações\n\n";

    out << "Busca Binária Recursiva:\n";
    out << "  - Profundidade máxima de recursão ≈ log2(n)\n";
    out << "  - Risco de stack overflow para n muito grande (ex: > 10^6)\n\n";

    out << "Recomendações:\n";
    out << "  ✓ Use busca binária iterativa para melhor performance\n";
    out << "  ✓ A versão instrumentada é útil para debugging/educação\n";
    out << "  ✓ Evite recursão para vetores muito grandes (> 10^6)\n";
    out << "  ✓ Garanta que o vetor esteja ordenado antes da busca binária\n";

    out.close();

    std::cout << "Relatório gerado: " << arquivo << std::endl;
}