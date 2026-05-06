#include "Estatisticas.hpp"
#include <algorithm>
#include <numeric>

ResumoEstatistico Estatisticas::calcular(const std::vector<double> &dados)
{
    ResumoEstatistico r;
    size_t n = dados.size();
    if (n == 0)
        return r;

    // ordenar para mediana e min/max
    auto sorted = dados;
    std::sort(sorted.begin(), sorted.end());

    r.minimo = sorted.front();
    r.maximo = sorted.back();
    r.mediana = sorted[n / 2];

    // média
    r.media = std::accumulate(dados.begin(), dados.end(), 0.0) / n;

    // desvio padrão amostral
    double somaQuad = 0.0;
    for (double val : dados)
    {
        double diff = val - r.media;
        somaQuad += diff * diff;
    }
    r.desvioPadrao = std::sqrt(somaQuad / (n - 1));

    // CV
    r.coeficienteVariacao = (r.desvioPadrao / r.media) * 100.0;

    // IC95% (aproximação t-Student para n grande → 1.96)
    double erro = 1.96 * r.desvioPadrao / std::sqrt(n);
    r.ic95_inferior = r.media - erro;
    r.ic95_superior = r.media + erro;

    return r;
}