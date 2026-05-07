#include "AlgoritmosBusca.hpp"
#include <algorithm>
#include <cmath>

// ==================== BUSCA SEQUENCIAL ====================
int AlgoritmosBusca::buscaSequencial(const std::vector<int> &arr, int alvo, Metricas &m)
{
    int n = arr.size();

    for (int i = 0; i < n; ++i) {
        // Conta acesso ao vetor
        m.acessos++;

        // Conta comparação
        m.comparacoes++;

        if (arr[i] == alvo) {
            return i; // elemento encontrado
        }
    }

    return -1; // elemento não encontrado
}

// ==================== BUSCA SEQUENCIAL COM SENTINELA ====================
int AlgoritmosBusca::buscaSequencialSentinela(std::vector<int> &arr, int alvo, Metricas &m)
{
    if (arr.empty())
        return -1;

    int n = arr.size();
    int ultimo = arr[n - 1];

    // Coloca sentinela no final
    m.acessos++; // escrita em arr[n-1]
    arr[n - 1] = alvo;

    int i = 0;
    while (true) {
        m.acessos++; // leitura de arr[i]
        m.comparacoes++;

        if (arr[i] == alvo) {
            break;
        }
        i++;
    }

    // Restaura o último elemento
    m.acessos++; // escrita em arr[n-1]
    arr[n - 1] = ultimo;

    // Verifica se encontrou o elemento real ou a sentinela
    if (i < n - 1 || arr[n - 1] == alvo) {
        return i;
    }

    return -1;
}

// ==================== BUSCA BINÁRIA ITERATIVA ====================
int AlgoritmosBusca::buscaBinaria(const std::vector<int> &arr, int alvo, Metricas &m)
{
    int esq = 0;
    int dir = arr.size() - 1;

    while (esq <= dir) {
        int meio = esq + (dir - esq) / 2;

        // Conta acesso ao vetor
        m.acessos++;

        // Conta comparação
        m.comparacoes++;

        if (arr[meio] == alvo) {
            return meio;
        }

        m.comparacoes++; // segunda comparação para decidir direção
        if (arr[meio] < alvo) {
            esq = meio + 1;
        } else {
            dir = meio - 1;
        }
    }

    return -1;
}

// ==================== BUSCA BINÁRIA INSTRUMENTADA ====================
int AlgoritmosBusca::buscaBinariaInstrumentada(const std::vector<int> &arr, int alvo,
                                               MetricasBuscaBinaria &m)
{
    int esq = 0;
    int dir = arr.size() - 1;
    m.iteracoes = 0;

    while (esq <= dir) {
        m.iteracoes++;
        int meio = esq + (dir - esq) / 2;

        // Registra acesso ao vetor
        m.acessos++;

        // Registra comparação (arr[meio] == alvo)
        m.comparacoes++;

        if (arr[meio] == alvo) {
            return meio;
        }

        // Registra segunda comparação (arr[meio] < alvo)
        m.comparacoes++;

        if (arr[meio] < alvo) {
            esq = meio + 1;
        } else {
            dir = meio - 1;
        }
    }

    return -1;
}

// ==================== BUSCA BINÁRIA RECURSIVA ====================
int AlgoritmosBusca::buscaBinariaRecursivaAux(const std::vector<int> &arr, int esq, int dir,
                                              int alvo, Metricas &m, int &profundidade)
{
    if (esq > dir) {
        return -1;
    }

    // Atualiza profundidade máxima
    static int prof_atual = 0;
    prof_atual++;
    if (prof_atual > m.profundidadeRecursao) {
        m.profundidadeRecursao = prof_atual;
    }

    int meio = esq + (dir - esq) / 2;

    // Conta acesso ao vetor
    m.acessos++;

    // Conta comparação
    m.comparacoes++;

    if (arr[meio] == alvo) {
        prof_atual--;
        return meio;
    }

    m.comparacoes++; // segunda comparação
    int resultado;
    if (arr[meio] < alvo) {
        resultado = buscaBinariaRecursivaAux(arr, meio + 1, dir, alvo, m, profundidade);
    } else {
        resultado = buscaBinariaRecursivaAux(arr, esq, meio - 1, alvo, m, profundidade);
    }

    prof_atual--;
    return resultado;
}

int AlgoritmosBusca::buscaBinariaRecursiva(const std::vector<int> &arr, int alvo, Metricas &m)
{
    int profundidade = 0;
    return buscaBinariaRecursivaAux(arr, 0, arr.size() - 1, alvo, m, profundidade);
}

// ==================== BUSCA TERNÁRIA ====================
int AlgoritmosBusca::buscaTernaria(const std::vector<int> &arr, int alvo, Metricas &m)
{
    int esq = 0;
    int dir = arr.size() - 1;

    while (esq <= dir) {
        int meio1 = esq + (dir - esq) / 3;
        int meio2 = dir - (dir - esq) / 3;

        // Acessos e comparações para meio1
        m.acessos++;
        m.comparacoes++;
        if (arr[meio1] == alvo) {
            return meio1;
        }

        // Acessos e comparações para meio2
        m.acessos++;
        m.comparacoes++;
        if (arr[meio2] == alvo) {
            return meio2;
        }

        // Decisão de qual terço procurar
        m.comparacoes++;
        if (alvo < arr[meio1]) {
            dir = meio1 - 1;
        } else {
            m.comparacoes++;
            if (alvo > arr[meio2]) {
                esq = meio2 + 1;
            } else {
                esq = meio1 + 1;
                dir = meio2 - 1;
            }
        }
    }

    return -1;
}

// ==================== FUNÇÕES AUXILIARES ====================
bool AlgoritmosBusca::vetorOrdenado(const std::vector<int> &arr)
{
    for (size_t i = 1; i < arr.size(); ++i) {
        if (arr[i] < arr[i - 1]) {
            return false;
        }
    }
    return true;
}

void AlgoritmosBusca::ordenarVetor(std::vector<int> &arr, Metricas &m)
{
    // Usa Insertion Sort para ordenar vetores pequenos
    int n = arr.size();
    for (int i = 1; i < n; ++i) {
        int chave = arr[i];
        int j = i - 1;

        m.acessos++;
        m.comparacoes++;

        while (j >= 0 && arr[j] > chave) {
            arr[j + 1] = arr[j];
            m.trocas++;
            m.acessos += 2;
            j--;

            if (j >= 0) {
                m.comparacoes++;
                m.acessos++;
            }
        }

        arr[j + 1] = chave;
        m.trocas++;
        m.acessos++;
    }
}