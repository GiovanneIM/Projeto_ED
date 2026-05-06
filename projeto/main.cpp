
#include "./include/AlgoritmosOrdenacao.hpp"
#include "./include/GeradorVetores.hpp"
#include "./include/Instrumentacao.hpp"
#include <iostream>
#include <iomanip>

// CÓDIGO DE COMPILAÇÃO
// g++ main.cpp include/*.cpp src/*.cpp -o projeto_ED

int main()
{
    // Configura seed fixa
    GeradorVetores::setSeed(42);

    // Gera vetor de teste
    std::vector<int> dados = GeradorVetores::ordenado(10000);

    // Testa Bubble Sort
    Metricas m;
    auto dadosCopia = dados; // copia para não afetar outros testes

    double tempo = Instrumentador::medirTempo([&]()
                                              { AlgoritmosOrdenacao::bubbleSort(dadosCopia, m); });
    m.tempoSegundos = tempo;

    // Exibe resultados
    std::cout << std::fixed << std::setprecision(6);
    std::cout << "Bubble Sort - 10.000 elementos:\n";
    std::cout << "  Tempo: " << m.tempoSegundos << " s\n";
    std::cout << "  Comparações: " << m.comparacoes << "\n";
    std::cout << "  Trocas: " << m.trocas << "\n";
    std::cout << "  Acessos: " << m.acessos << "\n";

    return 0;
}