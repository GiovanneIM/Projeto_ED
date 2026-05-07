#include "BenchmarkCompleto.hpp"
#include "GeradorVetores.hpp"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <chrono>

// Construtor
BenchmarkCompleto::BenchmarkCompleto(const BenchmarkConfig& config) : config(config) {
    GeradorVetores::setSeed(config.seed);
    srand(config.seed); // Para o quick sort randomizado
}

// Geração de dados por cenário
std::vector<int> BenchmarkCompleto::gerarDados(const std::string& cenario, int tamanho) {
    if (cenario == "Aleatorio") {
        return GeradorVetores::aleatorio(tamanho, 0, tamanho * 10);
    } else if (cenario == "Ordenado") {
        return GeradorVetores::ordenado(tamanho);
    } else if (cenario == "Reverso") {
        return GeradorVetores::reverso(tamanho);
    } else if (cenario == "ParcialmenteOrdenado") {
        return GeradorVetores::parcialmenteOrdenado(tamanho, 0.8);
    } else if (cenario == "AltaRepeticao") {
        return GeradorVetores::altaRepeticao(tamanho, 100);
    } else if (cenario == "QuaseReal") {
        double media = tamanho / 2.0;
        double desvio = tamanho / 6.0;
        return GeradorVetores::quaseRealGaussiano(tamanho, media, desvio);
    }
    return GeradorVetores::aleatorio(tamanho);
}

// Execução de algoritmo de ordenação
ResultadoOrdenacao BenchmarkCompleto::executarOrdenacao(const std::string& algoritmo, std::vector<int>& dados) {
    ResultadoOrdenacao resultado;
    resultado.nomeAlgoritmo = algoritmo;
    Metricas m;
    
    auto inicio = std::chrono::high_resolution_clock::now();
    
    if (algoritmo == "BubbleSort") {
        AlgoritmosOrdenacao::bubbleSort(dados, m);
    } else if (algoritmo == "InsertionSort") {
        AlgoritmosOrdenacao::insertionSort(dados, m);
    } else if (algoritmo == "SelectionSort") {
        AlgoritmosOrdenacao::selectionSort(dados, m);
    } else if (algoritmo == "MergeSort") {
        AlgoritmosOrdenacao::mergeSort(dados, m);
    } else if (algoritmo == "QuickSort") {
        AlgoritmosOrdenacao::quickSort(dados, m);
    } else if (algoritmo == "QuickSortRandomizado") {
        AlgoritmosOrdenacao::quickSortRandomizado(dados, m);
    } else if (algoritmo == "HeapSort") {
        AlgoritmosOrdenacao::heapSort(dados, m);
    } else if (algoritmo == "ShellSort") {
        AlgoritmosOrdenacao::shellSort(dados, m);
    } else {
        std::cerr << "Algoritmo desconhecido: " << algoritmo << std::endl;
    }
    
    auto fim = std::chrono::high_resolution_clock::now();
    m.tempoSegundos = std::chrono::duration<double>(fim - inicio).count();
    
    resultado.fromMetricas(m);
    resultado.ordenadoCorretamente = vetorOrdenado(dados);
    
    return resultado;
}

// Execução de algoritmo de busca
ResultadoBuscaCompleto BenchmarkCompleto::executarBusca(const std::string& algoritmo, const std::vector<int>& dados, int alvo) {
    ResultadoBuscaCompleto resultado;
    resultado.nomeAlgoritmo = algoritmo;
    Metricas m;
    
    auto inicio = std::chrono::high_resolution_clock::now();
    
    if (algoritmo == "BuscaSequencial") {
        resultado.indiceEncontrado = AlgoritmosBusca::buscaSequencial(dados, alvo, m);
    } else if (algoritmo == "BuscaBinaria") {
        resultado.indiceEncontrado = AlgoritmosBusca::buscaBinaria(dados, alvo, m);
    } else if (algoritmo == "BuscaBinariaInstrumentada") {
        MetricasBuscaBinaria mInst;
        resultado.indiceEncontrado = AlgoritmosBusca::buscaBinariaInstrumentada(dados, alvo, mInst);
        resultado.comparacoes = mInst.comparacoes;
        resultado.acessos = mInst.acessos;
        auto fim = std::chrono::high_resolution_clock::now();
        resultado.tempoSegundos = std::chrono::duration<double>(fim - inicio).count();
        resultado.sucesso = (resultado.indiceEncontrado != -1);
        return resultado;
    } else if (algoritmo == "BuscaBinariaRecursiva") {
        resultado.indiceEncontrado = AlgoritmosBusca::buscaBinariaRecursiva(dados, alvo, m);
    }
    
    auto fim = std::chrono::high_resolution_clock::now();
    resultado.tempoSegundos = std::chrono::duration<double>(fim - inicio).count();
    resultado.fromMetricas(m);
    resultado.sucesso = (resultado.indiceEncontrado != -1);
    
    return resultado;
}

// Comparação com std::sort
ResultadoOrdenacao BenchmarkCompleto::stdSort(std::vector<int>& dados) {
    ResultadoOrdenacao resultado;
    resultado.nomeAlgoritmo = "std::sort";
    
    auto inicio = std::chrono::high_resolution_clock::now();
    std::sort(dados.begin(), dados.end());
    auto fim = std::chrono::high_resolution_clock::now();
    
    resultado.tempoSegundos = std::chrono::duration<double>(fim - inicio).count();
    resultado.ordenadoCorretamente = vetorOrdenado(dados);
    
    return resultado;
}

ResultadoOrdenacao BenchmarkCompleto::stdStableSort(std::vector<int>& dados) {
    ResultadoOrdenacao resultado;
    resultado.nomeAlgoritmo = "std::stable_sort";
    
    auto inicio = std::chrono::high_resolution_clock::now();
    std::stable_sort(dados.begin(), dados.end());
    auto fim = std::chrono::high_resolution_clock::now();
    
    resultado.tempoSegundos = std::chrono::duration<double>(fim - inicio).count();
    resultado.ordenadoCorretamente = vetorOrdenado(dados);
    
    return resultado;
}

// Verificações
bool BenchmarkCompleto::vetorOrdenado(const std::vector<int>& arr) {
    for (size_t i = 1; i < arr.size(); ++i) {
        if (arr[i] < arr[i - 1]) return false;
    }
    return true;
}

bool BenchmarkCompleto::vetorIdentico(const std::vector<int>& original, const std::vector<int>& ordenado) {
    if (original.size() != ordenado.size()) return false;
    auto sortedOriginal = original;
    std::sort(sortedOriginal.begin(), sortedOriginal.end());
    return sortedOriginal == ordenado;
}

// Estatísticas
template<typename T>
EstatisticasExecucao<T> BenchmarkCompleto::computarEstatisticas(const std::vector<T>& dados) {
    EstatisticasExecucao<T> stats;
    stats.calcular(dados);
    return stats;
}

template<typename T>
T BenchmarkCompleto::computarMediana(std::vector<T> dados) {
    if (dados.empty()) return T();
    std::sort(dados.begin(), dados.end());
    return dados[dados.size() / 2];
}

// Progresso
void BenchmarkCompleto::mostrarProgresso(int atual, int total, const std::string& mensagem) {
    float percent = (atual * 100.0f) / total;
    std::cout << "\r[" << std::string(percent / 2, '=') << std::string(50 - percent / 2, ' ') << "] ";
    std::cout << std::fixed << std::setprecision(1) << percent << "% - " << mensagem;
    std::cout.flush();
}

// Execução principal do benchmark
void BenchmarkCompleto::executarBenchmark() {
    std::cout << "\n========================================\n";
    std::cout << "INICIANDO BENCHMARK COMPLETO\n";
    std::cout << "========================================\n";
    std::cout << "Configuração:\n";
    std::cout << "  Seed: " << config.seed << "\n";
    std::cout << "  Repetições: " << config.repeticoes << "\n";
    std::cout << "  Tamanhos: ";
    for (int n : config.tamanhos) std::cout << n << " ";
    std::cout << "\n  Cenários: ";
    for (const auto& c : config.cenarios) std::cout << c << " ";
    std::cout << "\n  Algs Ordenação: ";
    for (const auto& a : config.algOrdenacao) std::cout << a << " ";
    std::cout << "\n\n";
    
    int totalTestes = config.tamanhos.size() * config.cenarios.size() * 
                      (config.algOrdenacao.size() + config.algBusca.size()) * 
                      config.repeticoes;
    int testeAtual = 0;
    
    // Para cada cenário
    for (const auto& cenario : config.cenarios) {
        std::cout << "\n>>> Processando cenário: " << cenario << "\n";
        
        // Para cada tamanho
        for (int tamanho : config.tamanhos) {
            std::cout << "\n  Tamanho: " << tamanho << "\n";
            
            // Gera dados base para este tamanho e cenário
            std::vector<int> dadosBase = gerarDados(cenario, tamanho);
            
            // === TESTES DE ORDENAÇÃO ===
            for (const auto& algoritmo : config.algOrdenacao) {
                std::vector<ResultadoOrdenacao> resultados;
                
                for (int rep = 0; rep < config.repeticoes; ++rep) {
                    // Cria cópia dos dados para não contaminar
                    std::vector<int> dadosCopia = dadosBase;
                    
                    ResultadoOrdenacao res = executarOrdenacao(algoritmo, dadosCopia);
                    resultados.push_back(res);
                    
                    testeAtual++;
                    mostrarProgresso(testeAtual, totalTestes, 
                        "Ordenacao: " + cenario + "/" + algoritmo + " n=" + std::to_string(tamanho));
                }
                
                // Armazena resultados
                resultadosOrdenacao[cenario][algoritmo][tamanho] = resultados;
            }
            
            // Prepara dados para busca (ordena o vetor para busca binária)
            std::vector<int> dadosOrdenados = dadosBase;
            std::sort(dadosOrdenados.begin(), dadosOrdenados.end());
            
            // Escolhe alvos para busca
            std::vector<int> alvos = {
                dadosBase[0],                                    // primeiro elemento
                dadosBase[tamanho / 2],                          // elemento do meio
                dadosBase[tamanho - 1],                          // último elemento
                tamanho + 1000                                   // elemento inexistente
            };
            std::vector<std::string> descAlvos = {"inicio", "meio", "fim", "inexistente"};
            
            // === TESTES DE BUSCA ===
            for (const auto& algoritmo : config.algBusca) {
                for (size_t a = 0; a < alvos.size(); ++a) {
                    std::vector<ResultadoBuscaCompleto> resultados;
                    
                    for (int rep = 0; rep < config.repeticoes; ++rep) {
                        ResultadoBuscaCompleto res;
                        
                        if (algoritmo == "BuscaSequencial") {
                            res = executarBusca(algoritmo, dadosBase, alvos[a]);
                        } else {
                            // Busca binária requer vetor ordenado
                            res = executarBusca(algoritmo, dadosOrdenados, alvos[a]);
                        }
                        
                        resultados.push_back(res);
                        
                        testeAtual++;
                        mostrarProgresso(testeAtual, totalTestes,
                            "Busca: " + cenario + "/" + algoritmo + "[" + descAlvos[a] + "] n=" + std::to_string(tamanho));
                    }
                    
                    // Armazena com identificador do alvo
                    std::string key = algoritmo + "_" + descAlvos[a];
                    resultadosBusca[cenario][key][tamanho] = resultados;
                }
            }
        }
    }
    
    std::cout << "\n\n✅ Benchmark concluído com sucesso!\n";
    
    // Computa estatísticas
    std::cout << "\nComputando estatísticas...\n";
    
    for (const auto& [cenario, algMap] : resultadosOrdenacao) {
        for (const auto& [algoritmo, sizeMap] : algMap) {
            for (const auto& [tamanho, resultados] : sizeMap) {
                // Extrai tempos
                std::vector<double> tempos;
                std::vector<long long> comparacoes;
                std::vector<long long> acessos;
                
                for (const auto& r : resultados) {
                    tempos.push_back(r.tempoSegundos);
                    comparacoes.push_back(r.comparacoes);
                    acessos.push_back(r.acessos);
                }
                
                statsTempo[cenario][algoritmo][tamanho] = computarEstatisticas(tempos);
                statsComparacoes[cenario][algoritmo][tamanho] = computarEstatisticas(comparacoes);
                statsAcessos[cenario][algoritmo][tamanho] = computarEstatisticas(acessos);
            }
        }
    }
    
    std::cout << "Estatísticas computadas!\n";
}

// Geração do relatório
void BenchmarkCompleto::gerarRelatorio(const std::string& arquivo) {
    std::ofstream out(arquivo);
    if (!out.is_open()) {
        std::cerr << "Erro ao criar arquivo: " << arquivo << std::endl;
        return;
    }
    
    out << "================================================================================\n";
    out << "RELATÓRIO DE BENCHMARK - PROJETO ESTRUTURAS DE DADOS\n";
    out << "================================================================================\n\n";
    
    out << "CONFIGURAÇÃO EXPERIMENTAL\n";
    out << "----------------------------------------------------------------------------\n";
    out << "Seed fixa: " << config.seed << " (reprodutibilidade garantida)\n";
    out << "Repetições por configuração: " << config.repeticoes << "\n";
    out << "Tamanhos testados: ";
    for (int n : config.tamanhos) out << n << " ";
    out << "\n\n";
    
    // Relatório de ordenação
    out << "RESULTADOS - ALGORITMOS DE ORDENAÇÃO\n";
    out << "================================================================================\n";
    
    for (const auto& cenario : config.cenarios) {
        out << "\n### CENÁRIO: " << cenario << "\n\n";
        
        // Cabeçalho da tabela
        out << std::left << std::setw(18) << "Algoritmo";
        out << std::right << std::setw(12) << "n";
        out << std::setw(14) << "Tempo (s)";
        out << std::setw(12) << "±";
        out << std::setw(14) << "Comparações";
        out << std::setw(12) << "Acessos";
        out << std::setw(14) << "Memória (KB)";
        out << std::setw(10) << "CV (%)";
        out << "\n";
        out << std::string(110, '-') << "\n";
        
        for (const auto& algoritmo : config.algOrdenacao) {
            for (int tamanho : config.tamanhos) {
                if (statsTempo[cenario].count(algoritmo) == 0) continue;
                if (statsTempo[cenario][algoritmo].count(tamanho) == 0) continue;
                
                auto& statT = statsTempo[cenario][algoritmo][tamanho];
                auto& statC = statsComparacoes[cenario][algoritmo][tamanho];
                auto& statA = statsAcessos[cenario][algoritmo][tamanho];
                
                out << std::left << std::setw(18) << algoritmo;
                out << std::right << std::fixed;
                out << std::setw(12) << tamanho;
                out << std::setprecision(6) << std::setw(14) << statT.media;
                out << std::setw(12) << statT.desvioPadrao;
                out << std::setw(14) << (long long)statC.media;
                out << std::setw(12) << (long long)statA.media;
                out << std::setw(14) << (statT.media == 0 ? 0 : 1); // Placeholder
                out << std::setw(10) << std::setprecision(2) << statT.coeficienteVariacao;
                out << "\n";
            }
        }
        out << "\n";
    }
    
    // Relatório de busca
    out << "\n\nRESULTADOS - ALGORITMOS DE BUSCA\n";
    out << "================================================================================\n";
    
    for (const auto& cenario : config.cenarios) {
        out << "\n### CENÁRIO: " << cenario << "\n\n";
        
        out << std::left << std::setw(25) << "Algoritmo";
        out << std::right << std::setw(12) << "n";
        out << std::setw(14) << "Tempo (s)";
        out << std::setw(14) << "Comparações";
        out << std::setw(14) << "Acessos";
        out << std::setw(10) << "Sucesso";
        out << "\n";
        out << std::string(80, '-') << "\n";
        
        // Para busca, precisamos de uma estrutura diferente
        // Simplificando para este exemplo
        out << "Ver dados exportados em CSV para análise detalhada da busca.\n";
    }
    
    // Análise crítica
    out << "\n\nANÁLISE CRÍTICA\n";
    out << "================================================================================\n\n";
    
    out << "1. Por que Bubble Sort é inviável para grandes volumes?\n";
    out << "   - Complexidade O(n²) resulta em ~10¹² operações para n=1.000.000\n";
    out << "   - Tempo estimado: anos de processamento\n\n";
    
    out << "2. Cenários onde Insertion Sort supera O(n log n):\n";
    out << "   - Vetores pequenos (n < 50)\n";
    out << "   - Dados quase ordenados (melhor caso O(n))\n";
    out << "   - Devido ao baixo overhead constante\n\n";
    
    out << "3. Quick Sort e degradação O(n²):\n";
    out << "   - Ocorre com pivô ruim (ex: dados já ordenados)\n";
    out << "   - Versão randomizada reduz probabilidade para 1/n!\n\n";
    
    out << "4. Heap Sort é estável?\n";
    out << "   - Não. Troca elementos distantes, perdendo ordem relativa\n\n";
    
    out.close();
    
    std::cout << "\n✅ Relatório gerado: " << arquivo << std::endl;
}

// Exportação para CSV
void BenchmarkCompleto::exportarCSV(const std::string& prefixo) {
    // Exporta dados de ordenação
    std::ofstream outOrd(prefixo + "_ordenacao.csv");
    if (outOrd.is_open()) {
        outOrd << "Cenario,Algoritmo,Tamanho,Repeticao,Tempo,Comparacoes,Acessos,Profundidade\n";
        
        for (const auto& [cenario, algMap] : resultadosOrdenacao) {
            for (const auto& [algoritmo, sizeMap] : algMap) {
                for (const auto& [tamanho, resultados] : sizeMap) {
                    for (size_t i = 0; i < resultados.size(); ++i) {
                        const auto& r = resultados[i];
                        outOrd << cenario << "," << algoritmo << "," << tamanho << "," << i << ","
                               << r.tempoSegundos << "," << r.comparacoes << "," << r.acessos << ","
                               << r.profundidadeRecursao << "\n";
                    }
                }
            }
        }
        outOrd.close();
        std::cout << "✅ Dados de ordenação exportados: " << prefixo << "_ordenacao.csv\n";
    }
    
    // Exporta dados de busca
    std::ofstream outBus(prefixo + "_busca.csv");
    if (outBus.is_open()) {
        outBus << "Cenario,Algoritmo,Tamanho,Repeticao,Tempo,Comparacoes,Acessos,Encontrado\n";
        
        for (const auto& [cenario, algMap] : resultadosBusca) {
            for (const auto& [algoritmo, sizeMap] : algMap) {
                for (const auto& [tamanho, resultados] : sizeMap) {
                    for (size_t i = 0; i < resultados.size(); ++i) {
                        const auto& r = resultados[i];
                        outBus << cenario << "," << algoritmo << "," << tamanho << "," << i << ","
                               << r.tempoSegundos << "," << r.comparacoes << "," << r.acessos << ","
                               << (r.sucesso ? 1 : 0) << "\n";
                    }
                }
            }
        }
        outBus.close();
        std::cout << "✅ Dados de busca exportados: " << prefixo << "_busca.csv\n";
    }
}

// ==================== MAIN COMPLETO ====================
#include <iostream>

int main() {
    std::cout << "=== PROJETO ESTRUTURAS DE DADOS - BENCHMARK COMPLETO ===\n";
    std::cout << "Prof. Israel Florentino\n\n";
    
    BenchmarkConfig config;
    
    // Ajusta para teste rápido (descomente para teste completo)
    // config.tamanhos = {1000, 5000, 10000, 50000, 100000};  // Remove 500k e 1M para teste
    // config.repeticoes = 10;  // Menos repetições para teste rápido
    
    BenchmarkCompleto benchmark(config);
    
    std::cout << "Pressione ENTER para iniciar o benchmark...";
    std::cin.get();
    
    benchmark.executarBenchmark();
    benchmark.gerarRelatorio("relatorio_completo.txt");
    benchmark.exportarCSV("benchmark_dados");
    
    std::cout << "\n=== BENCHMARK CONCLUÍDO ===\n";
    std::cout << "Arquivos gerados:\n";
    std::cout << "  - relatorio_completo.txt\n";
    std::cout << "  - benchmark_dado