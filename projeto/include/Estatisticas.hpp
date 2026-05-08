#ifndef ESTATISTICAS_HPP
#define ESTATISTICAS_HPP

#include <algorithm>
#include <cmath>
#include <numeric>
#include <vector>

/** .
 * @brief Struct para armazenar as estatística de cada experimento
 *
 */
struct AnaliseEstatistica {
    double soma;
    double media;
    double desvioPadrao;
    double minimo;
    double maximo;
    double mediana;
    double coeficienteVariacao;
    double ic95_inferior;
    double ic95_superior;
};

class Estatisticas {
  public:
    static AnaliseEstatistica calcular(const std::vector<double> &dados)
    {
        AnaliseEstatistica r;
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
        for (double val : dados) {
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
    };

    template <typename T> static AnaliseEstatistica calcularAnaliseEstatistica(const std::vector<T> &dados)
    {
        AnaliseEstatistica stats{};
        const size_t n = dados.size();

        if (n == 0)
            return stats;

        // ===== Soma =====
        stats.soma = 0.0;
        for (const auto &v : dados)
            stats.soma += static_cast<double>(v);

        // ===== Média =====
        stats.media = stats.soma / static_cast<double>(n);

        // ===== Ordena para min, max e mediana =====
        std::vector<T> ordenado = dados;
        std::sort(ordenado.begin(), ordenado.end());

        stats.minimo = static_cast<double>(ordenado.front());
        stats.maximo = static_cast<double>(ordenado.back());

        // ===== Mediana =====
        if (n % 2 == 0) {
            stats.mediana =
                (static_cast<double>(ordenado[n / 2 - 1]) + static_cast<double>(ordenado[n / 2])) /
                2.0;
        } else {
            stats.mediana = static_cast<double>(ordenado[n / 2]);
        }

        // ===== Desvio padrão amostral =====
        double somaQuadrados = 0.0;
        for (const auto &v : dados) {
            double diff = static_cast<double>(v) - stats.media;
            somaQuadrados += diff * diff;
        }
        stats.desvioPadrao = std::sqrt(somaQuadrados / (n - 1));

        // ===== Coeficiente de variação (%) =====
        if (stats.media != 0.0) {
            stats.coeficienteVariacao = (stats.desvioPadrao / stats.media) * 100.0;
        } else {
            stats.coeficienteVariacao = 0.0;
        }

        // ===== Intervalo de confiança 95% =====
        double erro = 1.96 * stats.desvioPadrao / std::sqrt(static_cast<double>(n));
        stats.ic95_inferior = stats.media - erro;
        stats.ic95_superior = stats.media + erro;

        return stats;
    }
};

#endif
