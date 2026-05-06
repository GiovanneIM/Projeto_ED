#include <iostream>
#include "geradores/geradores.h"

// g++ main.cpp geradores/geradores.cpp ordenadores/*.cpp -o programa

int main()
{
    // SEED FIXA PARA GERAÇÃO DOS DADOS
    int seed = 42;

    // TAMANHOS DOS VETORES
    std::vector<int> tamanhos = {
        1000,
        5000,
        10000,
        50000,
        100000,
        500000,
        1000000};

    // GERANDO UM VETOR
    auto v = gerarVetor("ordenado", tamanhos[0], seed);

    // EXIBINDO O VETOR, ELEMENTO POR ELEMENTO
    for (int i = 0; i < tamanhos[0]; i++)
    {
        std::cout << v[i] << " ";
    }

    return 0;
}