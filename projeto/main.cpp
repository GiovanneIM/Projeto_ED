
#include "./include/AlgoritmosOrdenacao.hpp"
#include "./include/GeradorVetores.hpp"
#include "./include/Instrumentacao.hpp"
#include <iomanip>
#include <iostream>

// CÓDIGO DE COMPILAÇÃO
// g++ main.cpp /include/*.hpp /src/*.cpp -o projeto_ED.exe

int main()
{
    // CONFIGURANDO A SEED
    GeradorVetores::setSeed(42);

    // GERANDO VETOR DE TESTE
    std::vector<int> dados = GeradorVetores::reverso(1000000);

    // TESTANDO BUBBLE SORT
    Metricas m;                          // INSTÂNCIANDO A CLASSE MÉTRICAS
    std::vector<int> dadosCopia = dados; // CRIANDO UM VETOR COPIA

    // MEDINDO TEMPO DE EXECUÇÃO
    double tempo = Instrumentador::medirTempo([&]() {
        // ORDENANDO O VETOR
        AlgoritmosOrdenacao::bubbleSort(dadosCopia, m);
    });
    m.tempoSegundos = tempo;

    // EXIBINDO RESULTADOS
    std::cout << std::fixed << std::setprecision(6);
    std::cout << "Bubble Sort - 1.000.000 elementos:\n";
    std::cout << "  Tempo: " << m.tempoSegundos << " s\n";
    std::cout << "  Comparações: " << m.comparacoes << "\n";
    std::cout << "  Trocas: " << m.trocas << "\n";
    std::cout << "  Acessos: " << m.acessos << "\n";

    // FINALIZANDO PROGRAMA
    return 0;
}