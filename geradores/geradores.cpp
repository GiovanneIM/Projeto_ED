#include "geradores.h"

// GERADOR
std::mt19937 criarGerador(int seed)
{
    return std::mt19937(seed);
}

// DADOS ALEATÓRIOS
std::vector<int> gerarAleatorio(int n, std::mt19937 &gen)
{
    std::uniform_int_distribution<> dist(0, n);

    std::vector<int> v(n);
    for (int i = 0; i < n; i++)
    {
        v[i] = dist(gen);
    }

    return v;
}

// DADOS ORDENADOS
std::vector<int> gerarOrdenado(int n)
{
    std::vector<int> v(n);

    // Preenchendo o vetor de 0 até n-1 em ordem
    for (int i = 0; i < n; i++)
    {
        v[i] = i;
    }

    return v;
}

// ORDEM REVERSA
std::vector<int> gerarReverso(int n)
{
    std::vector<int> v(n);

    // Preenchendo o vetor de n - 1 até 0 de trás para frente
    for (int i = 0; i < n; i++)
    {
        v[i] = n - 1 - i;
    }

    return v;
}

// PARCIALMENTE ORDENADOS
std::vector<int> gerarParcial(int n, std::mt19937 &gen)
{
    std::vector<int> v = gerarOrdenado(n);

    std::uniform_int_distribution<> dist(0, n - 1);
    int trocas = n * 0.2;

    for (int i = 0; i < trocas; i++)
    {
        int a = dist(gen);
        int b = dist(gen);
        std::swap(v[a], v[b]);
    }

    return v;
}

// ALTA REPETIÇÃO
std::vector<int> gerarRepetidos(int n, std::mt19937 &gen)
{
    std::uniform_int_distribution<> dist(0, 100);

    std::vector<int> v(n);
    for (int i = 0; i < n; i++)
    {
        v[i] = dist(gen);
    }

    return v;
}

// DADOS DISTRIBUIDOS
std::vector<int> gerarGaussiano(int n, std::mt19937 &gen)
{
    std::normal_distribution<> dist(50.0, 15.0); // média 50, desvio 15

    std::vector<int> v(n);
    for (int i = 0; i < n; i++)
    {
        v[i] = (int)dist(gen);
    }

    return v;
}

// FUNÇÃO PARA GERAR UM VETOR
std::vector<int> gerarVetor(std::string tipo, int tamanho, int seed)
{
    std::mt19937 gen = criarGerador(seed);

    if (tipo == "aleatorio")
        return gerarAleatorio(tamanho, gen);

    if (tipo == "ordenado")
        return gerarOrdenado(tamanho);

    if (tipo == "reverso")
        return gerarReverso(tamanho);

    if (tipo == "parcial")
        return gerarParcial(tamanho, gen);

    if (tipo == "repetidos")
        return gerarRepetidos(tamanho, gen);

    if (tipo == "gaussiano")
        return gerarGaussiano(tamanho, gen);
}
