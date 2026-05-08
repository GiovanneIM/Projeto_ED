#include "AlgoritmosBusca.hpp"
#include <algorithm>
#include <cmath>

// ==================== BUSCA SEQUENCIAL ====================

int AlgoritmosBusca::buscaSequencial(const std::vector<int> &arr, int alvo)
{
    // OBTER O TAMANHO DO VETOR
    int n = arr.size();

    // LOOP QUE PERCORRE O VETOR
    for (int i = 0; i < n; ++i) {
        // SE O ELEMENTO FOR IGUAL AO BUSCADO, RETORNA O ÍNDICE
        if (arr[i] == alvo) {
            return i;
        }
    }

    // RETORNA -1 SE O ELEMENTO NÃO TIVER SIDO ENCONTRADO
    return -1;
}

// ==================== BUSCA BINÁRIA  ====================

int AlgoritmosBusca::buscaBinaria(const std::vector<int> &arr, int alvo)
{
    // ÍNDICE DOS LIMITES DO INTERVALO
    // À ESQUERDA
    int esq = 0;
    // À DIREITA
    int dir = arr.size() - 1;

    // ENQUANTO FOR POSSÍVEL DIVIDIR O INTERVALO
    while (esq <= dir) {
        // CALCULAR O ÍNDICE DO ELEMENTO CENTRAL DO INTERVALO
        int meio = esq + (dir - esq) / 2;

        // SE O ELEMENTO FOR IGUAL AO BUSCADO, RETORNA O ÍNDICE
        if (arr[meio] == alvo) {
            return meio;
        }

        // VERIFICANDO SE O ALVO É MAIOR OU MENOR QUE O ELEMENTO CENTRAL
        if (arr[meio] < alvo) {
            esq = meio + 1;
        } else {
            dir = meio - 1;
        }
    }

    // RETORNA -1 SE O ELEMENTO NÃO TIVER SIDO ENCONTRADO
    return -1;
}

// ==================== BUSCA BINÁRIA INSTRUMENTADA ====================

int AlgoritmosBusca::buscaBinariaInstrumentada(const std::vector<int> &arr, int alvo, Metricas &m)
{
    // ÍNDICE DOS LIMITES DO INTERVALO
    // À ESQUERDA
    int esq = 0;
    // À DIREITA
    int dir = arr.size() - 1;

    while (esq <= dir) {
        // INCREMENTA O NÚMERO DE ITERAÇÕES
        m.iteracoes++;

        // CALCULAR O ÍNDICE DO ELEMENTO CENTRAL DO INTERVALO
        int meio = esq + (dir - esq) / 2;

        // INCREMENTA O NÚMERO DE ACESSOES
        m.acessos++;
        int valorMeio = arr[meio];

        // INCREMENTA O NÚMERO DE COMPARAÇÕES
        m.comparacoes++;

        // SE O ELEMENTO FOR IGUAL AO BUSCADO, RETORNA O ÍNDICE
        if (arr[meio] == alvo) {
            return meio;
        }
        // INCREMENTA O NÚMERO DE COMPARAÇÕES
        m.comparacoes++;

        // VERIFICANDO SE O ALVO É MAIOR OU MENOR QUE O ELEMENTO CENTRAL
        if (arr[meio] < alvo) {
            esq = meio + 1;
        } else {
            dir = meio - 1;
        }
    }

    // RETORNA -1 SE O ELEMENTO NÃO TIVER SIDO ENCONTRADO
    return -1;
}
