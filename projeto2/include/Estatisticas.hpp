#pragma once
#include <vector>
#include <cmath>

/**
 * 
 */
struct ResumoEstatistico
{
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
    static ResumoEstatistico calcular(const std::vector<double> &dados);
};