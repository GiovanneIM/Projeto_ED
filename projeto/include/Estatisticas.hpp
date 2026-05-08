#pragma once
#include <vector>
#include <cmath>

/** .
 * @brief Struct para armazenar as estatística de cada experimento
 * 
 */
struct AnaliseEstatistica
{
    double total;
    double media;
    double desvioPadrao;
    double minimo;
    double maximo;
    double mediana;
    double coeficienteVariacao;
    double ic95_inferior;
    double ic95_superior;
};

class Estatisticas
{
public:
    static AnaliseEstatistica calcular(const std::vector<double> &dados);
};