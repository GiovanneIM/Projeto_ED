#include "AlgoritmosOrdenacao.hpp"
#include <algorithm>
#include <cmath>
#include <cstring>

// ==================== BUBBLE SORT ====================
void AlgoritmosOrdenacao::bubbleSort(std::vector<int> &arr, Metricas &m)
{
    int n = arr.size();
    m.memoriaAuxiliarBytes = 0; // in-place, apenas algumas variáveis locais

    for (int i = 0; i < n - 1; ++i)
    {
        bool trocou = false;

        for (int j = 0; j < n - i - 1; ++j)
        {
            // Contagem de acessos: leitura de arr[j] e arr[j+1]
            m.acessos += 2;
            m.comparacoes++;

            if (arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1], m);
                trocou = true;
            }
        }

        if (!trocou)
            break;
    }
}

// ==================== INSERTION SORT ====================
void AlgoritmosOrdenacao::insertionSort(std::vector<int> &arr, Metricas &m)
{
    int n = arr.size();
    m.memoriaAuxiliarBytes = 0;

    for (int i = 1; i < n; ++i)
    {
        int chave = arr[i];
        m.acessos++; // leitura de arr[i]
        int j = i - 1;

        // Contagem de acessos: leitura de arr[j]
        m.comparacoes++;
        m.acessos++;

        while (j >= 0 && arr[j] > chave)
        {
            // Movimentação: arr[j+1] = arr[j]
            arr[j + 1] = arr[j];
            m.trocas++;
            m.acessos += 2; // leitura de arr[j] e escrita em arr[j+1]

            j--;
            if (j >= 0)
            {
                m.comparacoes++;
                m.acessos++; // leitura de arr[j]
            }
        }

        arr[j + 1] = chave;
        m.trocas++;
        m.acessos++; // escrita em arr[j+1]
    }
}

// ==================== SELECTION SORT ====================
void AlgoritmosOrdenacao::selectionSort(std::vector<int> &arr, Metricas &m)
{
    int n = arr.size();
    m.memoriaAuxiliarBytes = 0;

    for (int i = 0; i < n - 1; ++i)
    {
        int min_idx = i;

        for (int j = i + 1; j < n; ++j)
        {
            m.acessos += 2; // leitura de arr[min_idx] e arr[j]
            m.comparacoes++;

            if (arr[j] < arr[min_idx])
            {
                min_idx = j;
            }
        }

        if (min_idx != i)
        {
            swap(arr[i], arr[min_idx], m);
        }
    }
}

// ==================== MERGE SORT ====================
void AlgoritmosOrdenacao::merge(std::vector<int> &arr, int esq, int meio, int dir, std::vector<int> &aux, Metricas &m)
{
    int i = esq, j = meio + 1, k = esq;

    while (i <= meio && j <= dir)
    {
        m.acessos += 2; // leitura de arr[i] e arr[j]
        m.comparacoes++;

        if (arr[i] <= arr[j])
        {
            aux[k] = arr[i];
            m.acessos += 2; // leitura de arr[i] e escrita em aux[k]
            m.trocas++;     // movimentação
            i++;
        }
        else
        {
            aux[k] = arr[j];
            m.acessos += 2; // leitura de arr[j] e escrita em aux[k]
            m.trocas++;     // movimentação
            j++;
        }
        k++;
    }

    while (i <= meio)
    {
        m.acessos++; // leitura de arr[i]
        aux[k] = arr[i];
        m.acessos++; // escrita em aux[k]
        m.trocas++;
        i++;
        k++;
    }

    while (j <= dir)
    {
        m.acessos++; // leitura de arr[j]
        aux[k] = arr[j];
        m.acessos++; // escrita em aux[k]
        m.trocas++;
        j++;
        k++;
    }

    // Copia de volta para o array original
    for (k = esq; k <= dir; ++k)
    {
        arr[k] = aux[k];
        m.acessos += 2; // leitura de aux[k] e escrita em arr[k]
        m.trocas++;
    }
}

void AlgoritmosOrdenacao::mergeSortRecursivo(std::vector<int> &arr, int esq, int dir, std::vector<int> &aux, Metricas &m, int profundidade)
{
    if (esq >= dir)
        return;

    // Atualiza profundidade máxima
    if (profundidade > m.profundidadeRecursao)
    {
        m.profundidadeRecursao = profundidade;
    }

    int meio = esq + (dir - esq) / 2;

    mergeSortRecursivo(arr, esq, meio, aux, m, profundidade + 1);
    mergeSortRecursivo(arr, meio + 1, dir, aux, m, profundidade + 1);
    merge(arr, esq, meio, dir, aux, m);
}

void AlgoritmosOrdenacao::mergeSort(std::vector<int> &arr, Metricas &m)
{
    int n = arr.size();
    std::vector<int> aux(n);
    m.memoriaAuxiliarBytes = n * sizeof(int); // vetor auxiliar

    mergeSortRecursivo(arr, 0, n - 1, aux, m, 0);
}

// ==================== QUICK SORT ====================
int AlgoritmosOrdenacao::partition(std::vector<int> &arr, int baixo, int alto, Metricas &m)
{
    int pivo = arr[alto];
    m.acessos++; // leitura do pivô
    int i = baixo - 1;

    for (int j = baixo; j < alto; ++j)
    {
        m.acessos++; // leitura de arr[j]
        m.comparacoes++;

        if (arr[j] <= pivo)
        {
            i++;
            swap(arr[i], arr[j], m);
        }
    }

    swap(arr[i + 1], arr[alto], m);
    return i + 1;
}

int AlgoritmosOrdenacao::partitionRandomizado(std::vector<int> &arr, int baixo, int alto, Metricas &m)
{
    // Escolhe pivô aleatório
    int randomIdx = baixo + rand() % (alto - baixo + 1);
    swap(arr[randomIdx], arr[alto], m);
    return partition(arr, baixo, alto, m);
}

void AlgoritmosOrdenacao::quickSortRecursivo(std::vector<int> &arr, int baixo, int alto, Metricas &m, int profundidade)
{
    if (baixo < alto)
    {
        // Atualiza profundidade máxima
        if (profundidade > m.profundidadeRecursao)
        {
            m.profundidadeRecursao = profundidade;
        }

        int pi = partition(arr, baixo, alto, m);

        quickSortRecursivo(arr, baixo, pi - 1, m, profundidade + 1);
        quickSortRecursivo(arr, pi + 1, alto, m, profundidade + 1);
    }
}

void AlgoritmosOrdenacao::quickSort(std::vector<int> &arr, Metricas &m)
{
    m.memoriaAuxiliarBytes = 0; // in-place
    quickSortRecursivo(arr, 0, arr.size() - 1, m, 0);
}

void AlgoritmosOrdenacao::quickSortRandomizado(std::vector<int> &arr, Metricas &m)
{
    m.memoriaAuxiliarBytes = 0;
    quickSortRecursivo(arr, 0, arr.size() - 1, m, 0);
}

// ==================== HEAP SORT ====================
void AlgoritmosOrdenacao::heapify(std::vector<int> &arr, int n, int i, Metricas &m)
{
    int maior = i;
    int esq = 2 * i + 1;
    int dir = 2 * i + 2;

    if (esq < n)
    {
        m.acessos += 2; // leitura de arr[esq] e arr[maior]
        m.comparacoes++;
        if (arr[esq] > arr[maior])
        {
            maior = esq;
        }
    }

    if (dir < n)
    {
        m.acessos += 2; // leitura de arr[dir] e arr[maior]
        m.comparacoes++;
        if (arr[dir] > arr[maior])
        {
            maior = dir;
        }
    }

    if (maior != i)
    {
        swap(arr[i], arr[maior], m);
        heapify(arr, n, maior, m);
    }
}

void AlgoritmosOrdenacao::heapSort(std::vector<int> &arr, Metricas &m)
{
    int n = arr.size();
    m.memoriaAuxiliarBytes = 0;
    m.profundidadeRecursao = 0; // heapify pode ser recursivo

    // Constrói heap máximo
    for (int i = n / 2 - 1; i >= 0; --i)
    {
        heapify(arr, n, i, m);
    }

    // Extrai elementos do heap
    for (int i = n - 1; i > 0; --i)
    {
        swap(arr[0], arr[i], m);
        heapify(arr, i, 0, m);
    }
}

// ==================== SHELL SORT ====================
void AlgoritmosOrdenacao::shellSort(std::vector<int> &arr, Metricas &m)
{
    int n = arr.size();
    m.memoriaAuxiliarBytes = 0;

    // Sequência de gaps: Knuth (3^k - 1)/2
    int gap = 1;
    while (gap < n / 3)
    {
        gap = 3 * gap + 1;
    }

    while (gap >= 1)
    {
        for (int i = gap; i < n; ++i)
        {
            int temp = arr[i];
            m.acessos++; // leitura de arr[i]
            int j = i;

            m.comparacoes++;
            m.acessos++; // leitura de arr[j - gap]

            while (j >= gap && arr[j - gap] > temp)
            {
                arr[j] = arr[j - gap];
                m.trocas++;
                m.acessos += 2; // leitura de arr[j-gap] e escrita em arr[j]
                j -= gap;

                if (j >= gap)
                {
                    m.comparacoes++;
                    m.acessos++; // leitura de arr[j - gap]
                }
            }

            arr[j] = temp;
            m.trocas++;
            m.acessos++; // escrita em arr[j]
        }
        gap = (gap - 1) / 3;
    }
}

// ==================== COUNTING SORT (opcional) ====================
void AlgoritmosOrdenacao::countingSort(std::vector<int> &arr, Metricas &m, int maxValor)
{
    if (arr.empty())
        return;

    // Encontra o valor máximo se não foi fornecido
    if (maxValor == -1)
    {
        maxValor = arr[0];
        for (size_t i = 1; i < arr.size(); ++i)
        {
            m.acessos++;
            m.comparacoes++;
            if (arr[i] > maxValor)
            {
                maxValor = arr[i];
            }
        }
    }

    // Vetor de contagem
    std::vector<int> contagem(maxValor + 1, 0);
    m.memoriaAuxiliarBytes = (maxValor + 1) * sizeof(int);

    // Conta ocorrências
    for (size_t i = 0; i < arr.size(); ++i)
    {
        m.acessos++; // leitura de arr[i]
        contagem[arr[i]]++;
        m.acessos++; // escrita em contagem
        m.trocas++;
    }

    // Soma acumulada
    for (int i = 1; i <= maxValor; ++i)
    {
        contagem[i] += contagem[i - 1];
        m.acessos += 2; // leitura/escrita em contagem
    }

    // Vetor de saída
    std::vector<int> saida(arr.size());
    m.memoriaAuxiliarBytes += arr.size() * sizeof(int);

    // Constrói array ordenado (estável - percorrendo do fim)
    for (int i = arr.size() - 1; i >= 0; --i)
    {
        m.acessos++; // leitura de arr[i]
        int val = arr[i];
        int pos = contagem[val] - 1;
        saida[pos] = val;
        m.acessos += 2; // leitura de contagem e escrita em saida
        m.trocas++;
        contagem[val]--;
        m.acessos++; // escrita em contagem
    }

    // Copia de volta
    for (size_t i = 0; i < arr.size(); ++i)
    {
        arr[i] = saida[i];
        m.acessos += 2; // leitura de saida e escrita em arr
        m.trocas++;
    }
}

// ==================== RADIX SORT (opcional) ====================
void AlgoritmosOrdenacao::countingSortPorDigito(std::vector<int> &arr, int exp, Metricas &m)
{
    int n = arr.size();
    std::vector<int> saida(n);
    int contagem[10] = {0};
    m.memoriaAuxiliarBytes = n * sizeof(int) + 10 * sizeof(int);

    // Conta dígitos
    for (int i = 0; i < n; ++i)
    {
        m.acessos++; // leitura de arr[i]
        int digito = (arr[i] / exp) % 10;
        contagem[digito]++;
        m.acessos++; // escrita em contagem
        m.trocas++;
    }

    // Soma acumulada
    for (int i = 1; i < 10; ++i)
    {
        contagem[i] += contagem[i - 1];
        m.acessos += 2;
    }

    // Constrói array ordenado
    for (int i = n - 1; i >= 0; --i)
    {
        m.acessos++; // leitura de arr[i]
        int digito = (arr[i] / exp) % 10;
        int pos = contagem[digito] - 1;
        saida[pos] = arr[i];
        m.acessos += 2;
        m.trocas++;
        contagem[digito]--;
        m.acessos++;
    }

    // Copia de volta
    for (int i = 0; i < n; ++i)
    {
        arr[i] = saida[i];
        m.acessos += 2;
        m.trocas++;
    }
}

void AlgoritmosOrdenacao::radixSort(std::vector<int> &arr, Metricas &m)
{
    if (arr.empty())
        return;

    // Encontra o valor máximo
    int maxValor = arr[0];
    for (size_t i = 1; i < arr.size(); ++i)
    {
        m.acessos++;
        if (arr[i] > maxValor)
        {
            maxValor = arr[i];
        }
    }

    // Aplica counting sort para cada dígito
    for (int exp = 1; maxValor / exp > 0; exp *= 10)
    {
        countingSortPorDigito(arr, exp, m);
    }
}

// ==================== UTILITÁRIOS ====================
void AlgoritmosOrdenacao::swap(int &a, int &b, Metricas &m)
{
    int temp = a;
    a = b;
    b = temp;
    m.trocas++;
    m.acessos += 4; // 2 leituras e 2 escritas
}