// GeradorVetores.cpp
#include "GeradorVetores.hpp"
#include <algorithm>
#include <random>

static std::mt19937 gen;

void GeradorVetores::setSeed(unsigned seed)
{
    gen.seed(seed);
};

std::vector<int> GeradorVetores::aleatorio(size_t n, int min, int max)
{
    // Definindo a distribuição uniforme de valores entre min e max
    std::uniform_int_distribution<int> dist(min, max);

    // Criando vetor com tamanho n
    std::vector<int> v(n);

    // Preenchendo o vetor com valores aleatórios da distribuição
    for (auto &x : v)
        x = dist(gen);

    // Retornando o vetor aleatório
    return v;
};

std::vector<int> GeradorVetores::ordenado(size_t n)
{
    // Criando vetor com tamanho n
    std::vector<int> v(n);

    // Preenchendo o vetor com os valores de 0 a n-1 em ordem crescente
    for (size_t i = 0; i < n; ++i)
        v[i] = i;

    // Retornando o vetor ordenado
    return v;
};

std::vector<int> GeradorVetores::reverso(size_t n)
{
    // Criando um vetor ordenado
    std::vector<int> v = ordenado(n);

    // Invertendo o vetor
    std::reverse(v.begin(), v.end());

    // Retornando o vetor em ordem decrescente
    return v;
};

std::vector<int> GeradorVetores::parcialmenteOrdenado(size_t n, double fracOrdenado)
{
    // Criando um vetor ordenado
    std::vector<int> v = ordenado(n);

    // Calculando número de trocas
    size_t trocas = static_cast<size_t>(n * (1.0 - fracOrdenado));

    // Definindo a distribuição uniforme de valores para os indices do vetor
    std::uniform_int_distribution<size_t> idx(0, n - 1);

    // Realizando trocas aleatórias para desordenar parcialmente o vetor
    for (size_t i = 0; i < trocas; ++i)
    {
        std::swap(v[idx(gen)], v[idx(gen)]);
    }

    // Retornando o vetor parcialmente ordenado
    return v;
};

std::vector<int> GeradorVetores::altaRepeticao(size_t n, int max)
{
    // Definindo a distribuição uniforme de valores entre 0 e max
    std::uniform_int_distribution<int> dist(0, max);

    // Criando vetor de tamanho n
    std::vector<int> v(n);

    // Preenchendo aleatoriamente o vetor com valores dentro da distribuição
    for (auto &x : v)
        x = dist(gen);

    // Retornando o vetor com alta repetição
    return v;
}

std::vector<int> GeradorVetores::gaussiano(size_t n, double media, double desvio)
{
    // Definindo a distribuição normal (gaussiana) de valores
    std::normal_distribution<double> dist(media, desvio);

    // Criando vetor de tamanho n
    std::vector<int> v(n);

    // Preenchendo o vetor com valores gerados pela distribuição,
    // arredondados para inteiro e limitados a valores não negativos
    for (auto &x : v)
    {
        int val = static_cast<int>(std::round(dist(gen)));
        x = std::max(0, val);
    }

    // Retornando o vetor com valores baseados em uma distribuição normal
    return v;
};