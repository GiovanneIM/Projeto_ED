#include "../include/AlgoritmosOrdenacao.hpp"
#include <algorithm>
#include <cmath>
#include <cstring>
#include <random>

// ==================== BUBBLE SORT ====================

void AlgoritmosOrdenacao::bubbleSort(std::vector<int> &arr, Metricas &m)
{
    // OBTER O TAMANHO DO VETOR
    int n = arr.size();

    // LOOP QUE PERCORRE O VETOR
    for (int i = 0; i < n - 1; ++i) {
        // VARIÁVEL PARA INDICAR SE HOUVE TROCA NA ITERAÇÃO
        bool trocou = false;

        // LOOP QUE PERCORRE A PARTE NÃO ORDENADA DO VETOR
        for (int j = 0; j < n - i - 1; ++j) {
            // A CADA LOOP, LÊ 2 VALORES: arr[j] E arr[j+1]
            m.acessos += 2;
            m.comparacoes++;

            // VERIFICA SE DEVE TROCAR OS 2 VALORES VIZINHOS
            if (arr[j] > arr[j + 1]) {
                // REALIZA A TROCA
                swap(arr[j], arr[j + 1], m);
                trocou = true;
            }
        }

        // SE NÃO HOUVER TROCAS, O VETOR ESTÁ ORDENADO
        if (!trocou)
            break;
    }

    // MEMORIA AUXILIAR
    /*
        n       |Tamanho do vetor   | int
        i       |Iterador           | int
        j       |Iterador           | int
        temp    |Auxiliar do swap   | int
        trocou  |Indicador de troca | bool
    */
    m.memoriaAuxiliarBytes = sizeof(int) * 4 + sizeof(bool);
}

// ==================== INSERTION SORT ====================

void AlgoritmosOrdenacao::insertionSort(std::vector<int> &arr, Metricas &m)
{
    // OBTER O TAMANHO DO VETOR
    int n = arr.size();

    // LOOP QUE PERCORRE O VETOR A PARTIR DO SEGUNDO ELEMENTO
    for (int i = 1; i < n; ++i) {
        // ARMAZENA O ELEMENTO ATUAL QUE SERÁ INSERIDO
        int chave = arr[i];

        // LEITURA DE arr[i]
        m.acessos++;

        // ÍNDICE DO ÚLTIMO ELEMENTO DA PARTE ORDENADA
        int j = i - 1;

        // PRIMEIRA COMPARAÇÃO DO WHILE
        m.comparacoes++;

        // LEITURA DE arr[j]
        m.acessos++;

        // PERCORRE A PARTE ORDENADA DO VETOR,
        // DESLOCANDO OS ELEMENTOS MAIORES QUE A CHAVE
        while (j >= 0 && arr[j] > chave) {

            // MOVE O ELEMENTO UMA POSIÇÃO À DIREITA
            arr[j + 1] = arr[j];

            // CONTABILIZA A MOVIMENTAÇÃO
            m.trocas++;

            // LEITURA DE arr[j] E ESCRITA EM arr[j+1]
            m.acessos += 2;

            // AVANÇA PARA O ELEMENTO ANTERIOR
            j--;

            // EVITA ACESSAR POSIÇÃO INVÁLIDA
            if (j >= 0) {

                // NOVA COMPARAÇÃO DO WHILE
                m.comparacoes++;

                // LEITURA DE arr[j]
                m.acessos++;
            }
        }

        // INSERE A CHAVE NA POSIÇÃO CORRETA
        arr[j + 1] = chave;

        // CONTABILIZA A MOVIMENTAÇÃO
        m.trocas++;

        // ESCRITA EM arr[j+1]
        m.acessos++;
    }

    // MEMÓRIA AUXILIAR
    /*
        n       | Tamanho do vetor      | int
        i       | Iterador              | int
        j       | Iterador              | int
        chave   | Elemento temporário   | int
    */
    m.memoriaAuxiliarBytes = sizeof(int) * 4;
}

// ==================== SELECTION SORT ====================

void AlgoritmosOrdenacao::selectionSort(std::vector<int> &arr, Metricas &m)
{
    // OBTER O TAMANHO DO VETOR
    int n = arr.size();

    // LOOP QUE PERCORRE O VETOR
    for (int i = 0; i < n - 1; ++i) {
        // ÍNDICE DO MENOR ELEMENTO DA PARTE NÃO ORDENADA
        int min_idx = i;

        // LOOP QUE PERCORRE A PARTE NÃO ORDENADA
        for (int j = i + 1; j < n; ++j) {
            // LEITURA DE arr[min_idx] E arr[j]
            m.acessos += 2;

            // COMPARAÇÃO ENTRE OS ELEMENTOS
            m.comparacoes++;

            // VERIFICA SE O ELEMENTO ATUAL É MENOR
            // QUE O MENOR ELEMENTO ENCONTRADO
            if (arr[j] < arr[min_idx]) {
                // ATUALIZA O ÍNDICE DO MENOR ELEMENTO
                min_idx = j;
            }
        }

        // VERIFICA SE O MENOR ELEMENTO JÁ NÃO ESTÁ
        // NA POSIÇÃO CORRETA
        if (min_idx != i) {

            // REALIZA A TROCA DOS ELEMENTOS
            swap(arr[i], arr[min_idx], m);
        }
    }

    // MEMÓRIA AUXILIAR
    /*
        n       | Tamanho do vetor          | int
        i       | Iterador                  | int
        j       | Iterador                  | int
        min_idx | Índice do menor elemento  | int
        temp    | Auxiliar do swap          | int
    */
    m.memoriaAuxiliarBytes = sizeof(int) * 5;
}

// ==================== MERGE SORT ====================

void AlgoritmosOrdenacao::mergeSort(std::vector<int> &arr, Metricas &m)
{
    // OBTER O TAMANHO DO VETOR
    int n = arr.size();

    // CRIANDO VETOR AUXILIAR
    std::vector<int> aux(n);

    // MEMÓRIA AUXILIAR
    // Vetor auxiliar utilizado durante o merge
    m.memoriaAuxiliarBytes = n * sizeof(int);

    // INICIA O MERGE SORT RECURSIVO
    mergeSortRecursivo(arr, 0, n - 1, aux, m, 0);
}

void AlgoritmosOrdenacao::mergeSortRecursivo(std::vector<int> &arr, int esq, int dir,
                                             std::vector<int> &aux, Metricas &m, int profundidade)
{
    // SE O INTERVALO POSSUI 1 OU 0 ELEMENTOS,
    // NÃO É POSSÍVEL DIVIDIR MAIS
    if (esq >= dir)
        return;

    // ATUALIZANDO A PROFUNDIDADE MÁXIMA DE RECURSÃO
    if (profundidade > m.profundidadeRecursao) {
        m.profundidadeRecursao = profundidade;
    }

    // CALCULA O ÍNDICE CENTRAL DO INTERVALO
    int meio = esq + (dir - esq) / 2;

    // APLICA O MERGE SORT NA METADE ESQUERDA
    mergeSortRecursivo(arr, esq, meio, aux, m, profundidade + 1);

    // APLICA O MERGE SORT NA METADE DIREITA
    mergeSortRecursivo(arr, meio + 1, dir, aux, m, profundidade + 1);

    // REALIZA O MERGE ENTRE AS DUAS METADES
    merge(arr, esq, meio, dir, aux, m);
}

void AlgoritmosOrdenacao::merge(std::vector<int> &arr, int esq, int meio, int dir,
                                std::vector<int> &aux, Metricas &m)
{
    // ÍNDICES DOS SUBVETORES
    int i = esq;      // SUBVETOR ESQUERDO
    int j = meio + 1; // SUBVETOR DIREITO
    int k = esq;      // VETOR AUXILIAR

    // ENQUANTO EXISTIREM ELEMENTOS NOS DOIS SUBVETORES
    while (i <= meio && j <= dir) {
        // LEITURA DE arr[i] E arr[j]
        m.acessos += 2;

        // COMPARAÇÃO ENTRE OS ELEMENTOS
        m.comparacoes++;

        // VERIFICA QUAL ELEMENTO É MENOR
        if (arr[i] <= arr[j]) {

            // COPIA O ELEMENTO PARA O VETOR AUXILIAR
            aux[k] = arr[i];

            // LEITURA DE arr[i] E ESCRITA EM aux[k]
            m.acessos += 2;

            // MOVIMENTAÇÃO
            m.trocas++;

            // AVANÇA NO SUBVETOR ESQUERDO
            i++;

        } else {

            // COPIA O ELEMENTO PARA O VETOR AUXILIAR
            aux[k] = arr[j];

            // LEITURA DE arr[j] E ESCRITA EM aux[k]
            m.acessos += 2;

            // MOVIMENTAÇÃO
            m.trocas++;

            // AVANÇA NO SUBVETOR DIREITO
            j++;
        }

        // AVANÇA NO VETOR AUXILIAR
        k++;
    }

    // COPIA OS ELEMENTOS RESTANTES DO SUBVETOR ESQUERDO
    while (i <= meio) {

        // LEITURA DE arr[i]
        m.acessos++;

        // COPIA PARA O VETOR AUXILIAR
        aux[k] = arr[i];

        // ESCRITA EM aux[k]
        m.acessos++;

        // MOVIMENTAÇÃO
        m.trocas++;

        i++;
        k++;
    }

    // COPIA OS ELEMENTOS RESTANTES DO SUBVETOR DIREITO
    while (j <= dir) {

        // LEITURA DE arr[j]
        m.acessos++;

        // COPIA PARA O VETOR AUXILIAR
        aux[k] = arr[j];

        // ESCRITA EM aux[k]
        m.acessos++;

        // MOVIMENTAÇÃO
        m.trocas++;

        j++;
        k++;
    }

    // COPIA O VETOR AUXILIAR DE VOLTA PARA O VETOR ORIGINAL
    for (k = esq; k <= dir; ++k) {

        // ESCRITA NO VETOR ORIGINAL
        arr[k] = aux[k];

        // LEITURA DE aux[k] E ESCRITA EM arr[k]
        m.acessos += 2;

        // MOVIMENTAÇÃO
        m.trocas++;
    }
}

// ==================== QUICK SORT ====================

void AlgoritmosOrdenacao::quickSort(std::vector<int> &arr, Metricas &m)
{
    // INICIANDO O QUICK SORT RECURSIVO
    quickSortRecursivo(arr, 0, arr.size() - 1, m, 0);

    // MEMÓRIA AUXILIAR ESTIMADA:
    // PILHA DE RECURSÃO
    m.memoriaAuxiliarBytes = m.profundidadeRecursao * sizeof(int) * 4;
}

int AlgoritmosOrdenacao::partition(std::vector<int> &arr, int baixo, int alto, Metricas &m)
{
    // DEFINE O ÚLTIMO ELEMENTO COMO PIVÔ
    int pivo = arr[alto];

    // LEITURA DO PIVÔ
    m.acessos++;

    // ÍNDICE DO MENOR ELEMENTO
    int i = baixo - 1;

    // PERCORRE O INTERVALO
    for (int j = baixo; j < alto; ++j) {

        // LEITURA DE arr[j]
        m.acessos++;

        // COMPARAÇÃO COM O PIVÔ
        m.comparacoes++;

        // VERIFICA SE O ELEMENTO É MENOR OU IGUAL AO PIVÔ
        if (arr[j] <= pivo) {

            i++;

            // REALIZA A TROCA DOS ELEMENTOS
            swap(arr[i], arr[j], m);
        }
    }

    // POSICIONA O PIVÔ NA POSIÇÃO CORRETA
    swap(arr[i + 1], arr[alto], m);

    // RETORNA O ÍNDICE DO PIVÔ
    return i + 1;
}

void AlgoritmosOrdenacao::quickSortRecursivo(std::vector<int> &arr, int baixo, int alto,
                                             Metricas &m, int profundidade)
{
    // VERIFICA SE O INTERVALO POSSUI MAIS DE UM ELEMENTO
    if (baixo < alto) {

        // ATUALIZA A PROFUNDIDADE MÁXIMA DA RECURSÃO
        if (profundidade > m.profundidadeRecursao) {
            m.profundidadeRecursao = profundidade;
        }

        // PARTICIONA O VETOR
        int pi = partition(arr, baixo, alto, m);

        // APLICA O QUICK SORT NA METADE ESQUERDA
        quickSortRecursivo(arr, baixo, pi - 1, m, profundidade + 1);

        // APLICA O QUICK SORT NA METADE DIREITA
        quickSortRecursivo(arr, pi + 1, alto, m, profundidade + 1);
    }
}

void AlgoritmosOrdenacao::quickSortRandomizado(std::vector<int> &arr, Metricas &m)
{
    // INICIANDO O QUICK SORT RECURSIVO
    quickSortRecursivoRandomizado(arr, 0, arr.size() - 1, m, 0);

    // MEMÓRIA AUXILIAR ESTIMADA:
    // PILHA DE RECURSÃO
    m.memoriaAuxiliarBytes = m.profundidadeRecursao * sizeof(int) * 5;
}

int AlgoritmosOrdenacao::partitionRandomizado(std::vector<int> &arr, int baixo, int alto,
                                              Metricas &m)
{
    static std::mt19937 gen(42);

    // DISTRIBUIÇÃO NO INTERVALO [baixo, alto]
    std::uniform_int_distribution<int> dist(baixo, alto);

    // ESCOLHE UM PIVÔ ALEATÓRIO
    int randomIdx = dist(gen);

    // MOVE O PIVÔ PARA O FINAL
    swap(arr[randomIdx], arr[alto], m);

    // PARTICIONA O VETOR
    return partition(arr, baixo, alto, m);
}

void AlgoritmosOrdenacao::quickSortRecursivoRandomizado(std::vector<int> &arr, int baixo, int alto,
                                                        Metricas &m, int profundidade)
{
    if (baixo < alto) {

        // ATUALIZA A PROFUNDIDADE MÁXIMA DA RECURSÃO
        if (profundidade > m.profundidadeRecursao) {
            m.profundidadeRecursao = profundidade;
        }

        // PARTICIONA O VETOR
        int pi = partitionRandomizado(arr, baixo, alto, m);

        // APLICA O RANDOM QUICK SORT NA METADE ESQUERDA
        quickSortRecursivoRandomizado(arr, baixo, pi - 1, m, profundidade + 1);

        // APLICA O RANDOM QUICK SORT NA METADE DIREITA
        quickSortRecursivoRandomizado(arr, pi + 1, alto, m, profundidade + 1);
    }
}

// ==================== HEAP SORT ====================

void AlgoritmosOrdenacao::heapSort(std::vector<int> &arr, Metricas &m)
{
    // OBTER O TAMANHO DO VETOR
    int n = arr.size();

    // CONSTRÓI O MAX HEAP A PARTIR DOS ELEMENTOS NÃO-FOLHA
    for (int i = n / 2 - 1; i >= 0; --i) {

        // AJUSTA A PROPRIEDADE DO HEAP
        heapify(arr, n, i, m, 0);
    }

    // REMOVE OS ELEMENTOS DO HEAP UM A UM
    for (int i = n - 1; i > 0; --i) {

        // MOVE O MAIOR ELEMENTO PARA O FINAL DO VETOR
        swap(arr[0], arr[i], m);

        // REORGANIZA O HEAP COM O NOVO TAMANHO
        heapify(arr, i, 0, m, 0);
    }

    // MEMÓRIA AUXILIAR ESTIMADA:
    // PILHA DE RECURSÃO DO HEAPIFY
    m.memoriaAuxiliarBytes = m.profundidadeRecursao * sizeof(int) * 4;
}

void AlgoritmosOrdenacao::heapify(std::vector<int> &arr, int n, int i, Metricas &m,
                                  int profundidade)
{
    // ATUALIZA A PROFUNDIDADE MÁXIMA
    if (profundidade > m.profundidadeRecursao) {
        m.profundidadeRecursao = profundidade;
    }

    // ÍNDICE DO MAIOR ELEMENTO
    int maior = i;

    // ÍNDICE DO FILHO ESQUERDO
    int esq = 2 * i + 1;

    // ÍNDICE DO FILHO DIREITO
    int dir = 2 * i + 2;

    // VERIFICA SE O FILHO ESQUERDO EXISTE
    if (esq < n) {

        // LEITURA DE arr[esq] E arr[maior]
        m.acessos += 2;

        // COMPARAÇÃO ENTRE OS ELEMENTOS
        m.comparacoes++;

        // VERIFICA SE O FILHO ESQUERDO É MAIOR
        if (arr[esq] > arr[maior]) {
            maior = esq;
        }
    }

    // VERIFICA SE O FILHO DIREITO EXISTE
    if (dir < n) {

        // LEITURA DE arr[dir] E arr[maior]
        m.acessos += 2;

        // COMPARAÇÃO ENTRE OS ELEMENTOS
        m.comparacoes++;

        // VERIFICA SE O FILHO DIREITO É MAIOR
        if (arr[dir] > arr[maior]) {
            maior = dir;
        }
    }

    // VERIFICA SE O MAIOR ELEMENTO NÃO É A RAIZ
    if (maior != i) {

        // TROCA A RAIZ PELO MAIOR ELEMENTO
        swap(arr[i], arr[maior], m);

        // REORGANIZA O HEAP RECURSIVAMENTE
        heapify(arr, n, maior, m);
    }
}

// ==================== SHELL SORT ====================

void AlgoritmosOrdenacao::shellSort(std::vector<int> &arr, Metricas &m)
{
    // OBTER O TAMANHO DO VETOR
    int n = arr.size();

    // INICIALIZA O GAP UTILIZANDO A SEQUÊNCIA DE KNUTH
    // gap = (3^k - 1) / 2
    int gap = 1;

    // CALCULA O MAIOR GAP POSSÍVEL
    while (gap < n / 3) {
        gap = 3 * gap + 1;
    }

    // ENQUANTO EXISTIREM GAPS VÁLIDOS
    while (gap >= 1) {

        // PERCORRE O VETOR A PARTIR DO GAP
        for (int i = gap; i < n; ++i) {

            // ARMAZENA O ELEMENTO ATUAL
            int temp = arr[i];

            // LEITURA DE arr[i]
            m.acessos++;

            // ÍNDICE DA POSIÇÃO ATUAL
            int j = i;

            // PRIMEIRA COMPARAÇÃO DO WHILE
            m.comparacoes++;

            // LEITURA DE arr[j-gap]
            m.acessos++;

            // REALIZA O INSERTION SORT COM DISTÂNCIA gap
            while (j >= gap && arr[j - gap] > temp) {

                // MOVE O ELEMENTO PARA A DIREITA
                arr[j] = arr[j - gap];

                // CONTABILIZA A MOVIMENTAÇÃO
                m.trocas++;

                // LEITURA DE arr[j-gap]
                // ESCRITA EM arr[j]
                m.acessos += 2;

                // AVANÇA PARA A POSIÇÃO ANTERIOR
                j -= gap;

                // EVITA ACESSAR POSIÇÃO INVÁLIDA
                if (j >= gap) {

                    // NOVA COMPARAÇÃO DO WHILE
                    m.comparacoes++;

                    // LEITURA DE arr[j-gap]
                    m.acessos++;
                }
            }

            // INSERE O ELEMENTO NA POSIÇÃO CORRETA
            arr[j] = temp;

            // CONTABILIZA A MOVIMENTAÇÃO
            m.trocas++;

            // ESCRITA EM arr[j]
            m.acessos++;
        }

        // CALCULA O PRÓXIMO GAP DA SEQUÊNCIA DE KNUTH
        gap = (gap - 1) / 3;
    }

    // MEMÓRIA AUXILIAR
    /*
        n       | Tamanho do vetor      | int
        gap     | Intervalo atual       | int
        i       | Iterador externo      | int
        j       | Iterador interno      | int
        temp    | Elemento temporário   | int
    */
    m.memoriaAuxiliarBytes = sizeof(int) * 5;
}

// ==================== UTILITÁRIOS ====================

void AlgoritmosOrdenacao::swap(int &a, int &b, Metricas &m)
{
    // VÁRIAVEL TEMPORARIA
    int temp = a;

    // TROCANDO OS VALORES
    a = b;
    b = temp;

    // INCREMENTANDO O NÚMERO DE TROCAS
    m.trocas++;

    // FORAM REALIZADOS 4 ACESSOS AO VETOR - 2 leituras e 2 escritas
    m.acessos += 4;
}