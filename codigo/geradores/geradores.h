#ifndef GERADORES_H
#define GERADORES_H

#include <vector>
#include <string>
#include <random>

std::mt19937 criarGerador(int seed);

std::vector<int> gerarAleatorio(int n, std::mt19937 &gen);
std::vector<int> gerarOrdenado(int n);
std::vector<int> gerarReverso(int n);
std::vector<int> gerarParcial(int n, std::mt19937 &gen);
std::vector<int> gerarRepetidos(int n, std::mt19937 &gen);
std::vector<int> gerarGaussiano(int n, std::mt19937 &gen);

std::vector<int> gerarVetor(std::string tipo, int tamanho, int seed = 42);

#endif